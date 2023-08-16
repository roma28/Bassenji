// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

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

double RMSDTrajectoryProcessor::rmsd(const Molecule& A, const Molecule& B)
{
    if (A.n_atom() != B.n_atom()) {
        throw std::runtime_error(fmt::format("The number of atoms in molecules is not equal: {0} and {1}",
                                             A.n_atom(),
                                             B.n_atom()));
    }

    Eigen::MatrixX3d P(A.n_atom(), 3);
    Eigen::MatrixX3d Q(B.n_atom(), 3);

    const Eigen::Vector3d centroidA = A.Centroid();
    const Eigen::Vector3d centroidB = B.Centroid();

    for (size_t i = 0; i < A.n_atom(); ++i) {
        P.row(i) = A.atoms[i].coordinates - centroidA;
        Q.row(i) = B.atoms[i].coordinates - centroidB;
    }

    const Eigen::Matrix3d R = optimal_rotation_matrix(P, Q);
    return _rmsd(P, Q * R);
}

Eigen::Matrix3d RMSDTrajectoryProcessor::optimal_rotation_matrix(const Eigen::MatrixX3d& P, const Eigen::MatrixX3d& Q)
{
    const auto H = P.transpose() * Q;
    Eigen::BDCSVD<Eigen::MatrixX3d> svd;
    svd.compute(H, Eigen::ComputeFullU | Eigen::ComputeFullV);
    int8_t d = (svd.matrixV() * svd.matrixU()).determinant() > 0 ? 1 : -1;

    return std::move(svd.matrixV() * Eigen::DiagonalMatrix<double, 3>(1, 1, d) * svd.matrixU().transpose());
}

double RMSDTrajectoryProcessor::_rmsd(const Eigen::MatrixX3d& P, const Eigen::MatrixX3d& Q)
{
    return sqrt((P - Q).squaredNorm() / P.rows());
}

std::vector<std::pair<Molecule, double>> RMSDTrajectoryProcessor::GetUniques() const
{
    std::vector<std::pair<Molecule, double>> u;

    double
        population_sum = std::accumulate(this->uniques.begin(), this->uniques.end(), 0.0, [](double previous, auto item)
    { return previous + item.second; });

    for (const auto p : this->uniques) {
        auto m = p.first;
        const Eigen::Vector3d mCentroid = m.Centroid();
        for (auto a : m.atoms) {
            a.coordinates -= mCentroid;
        }
        u.emplace_back(m, p.second / population_sum);
    }

    return std::move(u);
}

void RMSDTrajectoryProcessor::Process(const Trajectory& trajectory, size_t n_jobs)
{
    tf::Taskflow tf;
    tf::Executor e(n_jobs);

    Trajectory t = rebalance_trajectory(trajectory);
    const double threshold = this->rmsd_threshold;

    auto uop = [threshold](const Frame& f)
    {
        std::vector<std::pair<Molecule, size_t>> frame_uniques;
        for (const auto& m1 : f.molecules) {
            bool is_unique = true;
            for (auto& p : frame_uniques) {
                if (rmsd(p.first, m1) < threshold) {
                    is_unique = false;
                    p.second++;
                    break;
                }
            }
            if (is_unique) {
                frame_uniques.emplace_back(m1, 1);
            }
        }
        return std::move(frame_uniques);
    };

    auto
        bop = [threshold](const std::vector<std::pair<Molecule, size_t>>& l, std::vector<std::pair<Molecule, size_t>> r)
    {
        for (const auto& p1 : l) {
            bool is_unique = true;
            for (auto& p2 : r) {
                if (rmsd(p2.first, p1.first) < threshold) {
                    is_unique = false;
                    p2.second += p1.second;
                    break;
                }
            }
            if (is_unique) {
                r.emplace_back(p1.first, p1.second);
            }
        }
        return std::move(r);
    };

    tf.transform_reduce(t.frames.begin(), t.frames.end(), this->uniques, bop, uop);
    e.run(tf).wait();
}

Trajectory RMSDTrajectoryProcessor::rebalance_trajectory(const Trajectory& trajectory)
{

    int total_molecules = 0;
    std::vector<Molecule> all_molecules;

    for (const auto& f : trajectory.frames) {
        total_molecules += f.n_mol();
        all_molecules.insert(all_molecules.end(), f.molecules.begin(), f.molecules.end());
    }

    const int mol_per_frame = sqrt(total_molecules) + 1;

    Trajectory t;

    int i = 0;
    while (i < total_molecules) {
        if (i % mol_per_frame == 0) {
            t.frames.emplace_back();
        }
        t.frames.back().molecules.push_back(all_molecules[i]);
        ++i;
    }
    return std::move(t);
}
