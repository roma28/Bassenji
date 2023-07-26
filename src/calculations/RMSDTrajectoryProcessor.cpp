// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
//

#include "RMSDTrajectoryProcessor.h"

#include <Eigen/SVD>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <numeric>
#include <tuple>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <taskflow/taskflow.hpp>
#include <taskflow/algorithm/reduce.hpp>
#include <taskflow/algorithm/transform.hpp>

#include <molecular/TrajectoryBuilder.h>

RMSDTrajectoryProcessor::RMSDTrajectoryProcessor(double threshold)
{

    this->logger = spdlog::stdout_color_st("RMSDTrajectoryProcessor");
    this->logger->debug("RMSDTrajectoryProcessor with threshold {0}", threshold);
    this->rmsd_threshold = threshold;
}

void RMSDTrajectoryProcessor::Process(const Trajectory* trajectory)
{

    size_t frames_processed = 1;
    for (const auto f : trajectory->frames) {
        this->logger->trace("Processing frame {0} out of {1}", frames_processed, trajectory->frames.size());
        for (const auto m : f->molecules) {

            size_t n_uniques = this->uniques.size();
            std::vector<bool> is_unique(n_uniques, true);

            tf::Taskflow tf;
            tf::Executor e;
            bool res = true;
            auto reduce_task = tf.reduce(is_unique.begin(), is_unique.end(), res, [](bool r, bool l)
            { return l && r; });

            // testing against all the uniques
            for (size_t i = 0; i < n_uniques; ++i) {
                tf.emplace([&]()
                           {
                               is_unique[i] = rmsd(m, uniques[i].first) < rmsd_threshold;
                           }).precede(reduce_task);
            }
            e.run(tf).wait();
            if (res) {
                uniques.emplace_back(m, 1);
            }
        }
        frames_processed++;
    }
}

double RMSDTrajectoryProcessor::rmsd(const Molecule* A, const Molecule* B) const
{

    if (A->atoms.size() != B->atoms.size()) {
        this->logger
            ->error("The number of atoms in molecules is not equal: {0} and {1}", A->atoms.size(), B->atoms.size());
        throw std::invalid_argument("The number of atoms in molecules is not equal");
    }

    Eigen::MatrixX3d P(A->atoms.size(), 3);
    Eigen::MatrixX3d Q(B->atoms.size(), 3);

    const Eigen::Vector3d centroidA = A->GetCentroid();
    const Eigen::Vector3d centroidB = B->GetCentroid();

    for (size_t i = 0; i < A->atoms.size(); ++i) {
        P.row(i) = A->atoms[i]->coordinates - centroidA;
        Q.row(i) = B->atoms[i]->coordinates - centroidB;
    }

    const Eigen::Matrix3d R = optimal_rotation_matrix(P, Q);
    return _rmsd(P, Q * R);
}

Eigen::Matrix3d RMSDTrajectoryProcessor::optimal_rotation_matrix(const Eigen::MatrixX3d& P, const Eigen::MatrixX3d& Q)
{

    const auto H = P.transpose() * Q;

    //    Eigen::JacobiSVD<Eigen::MatrixX3d> svd;
    Eigen::BDCSVD<Eigen::MatrixX3d> svd;
    svd.compute(H, Eigen::ComputeFullU | Eigen::ComputeFullV);

    int8_t d = (svd.matrixV() * svd.matrixU()).determinant() > 0 ? 1 : -1;

    return svd.matrixV() * Eigen::DiagonalMatrix<double, 3>(1, 1, d) * svd.matrixU().transpose();
}

double RMSDTrajectoryProcessor::_rmsd(const Eigen::MatrixX3d& P, const Eigen::MatrixX3d& Q) const
{

    double rmsd = sqrt((P - Q).squaredNorm() / P.rows());
    this->logger->trace("RMSD = {0:.4f}", rmsd);
    return rmsd;
}

std::vector<std::pair<Molecule*, double>> RMSDTrajectoryProcessor::GetUniques() const
{

    std::vector<std::pair<Molecule*, double>> u;

    double
        population_sum = std::accumulate(this->uniques.begin(), this->uniques.end(), 0.0, [](double previous, auto item)
    { return previous + item.second; });

    for (const auto p : this->uniques) {
        Molecule* m = new Molecule(*p.first);
        const Eigen::Vector3d mCentroid = m->GetCentroid();
        for (const auto a : m->atoms) {
            a->coordinates -= mCentroid;
        }
        u.emplace_back(p.first, p.second / population_sum);
    } //-V773

    return u;
}

void RMSDTrajectoryProcessor::ProcessParallel(const Trajectory* trajectory, size_t n_jobs)
{

    tf::Taskflow tf;
    tf::Executor e(n_jobs);

    Trajectory t = balance_trajectory(trajectory);

    auto uop = [this](Frame* f)
    {
        std::vector<std::pair<Molecule*, size_t>> local_uniques;
        for (auto m1 : f->molecules) {
            bool is_unique = true;
            for (auto& p : local_uniques) {
                if (rmsd(p.first, m1) < rmsd_threshold) {
                    is_unique = false;
                    p.second++;
                    break;
                }
            }
            if (is_unique) {
                local_uniques.emplace_back(m1, 1);
            }
        }
        return local_uniques;
    };

    auto bop = [this](std::vector<std::pair<Molecule*, size_t>> l, std::vector<std::pair<Molecule*, size_t>> r)
    {
        for (auto& p1 : l) {
            bool is_unique = true;
            for (auto p2 : r) {
                if (rmsd(p2.first, p1.first) < rmsd_threshold) {
                    is_unique = false;
                    p2.second += p1.second;
                    break;
                }
            }
            if (is_unique) {
                r.emplace_back(p1.first, p1.second);
            }
        }
        return r;
    };

    std::vector<std::pair<Molecule*, size_t>> u;
    tf.transform_reduce(t.frames.begin(), t.frames.end(), u, bop, uop);

    e.run(tf).wait();

    this->uniques = u;

    auto a = 1;
}

Trajectory RMSDTrajectoryProcessor::balance_trajectory(const Trajectory* trajectory)
{

    int total_molecules = 0;
    std::vector<Molecule*> all_molecules;

    for (const auto f : trajectory->frames) {
        total_molecules += f->n_mol();
        for (auto m : f->molecules) {
            all_molecules.push_back(m);
        }
    }

    int mol_per_frame = sqrt(total_molecules) + 1;

    Trajectory t;

    int i = 0;
    while (i < total_molecules) {
        Frame* current_frame;
        if (i % mol_per_frame == 0) {
            current_frame = new Frame();
            t.frames.push_back(current_frame);
        }
        current_frame->molecules.push_back(all_molecules.at(i));
        ++i;
    }
    return t;
}
