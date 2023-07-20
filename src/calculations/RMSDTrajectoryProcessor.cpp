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
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <omp.h>

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
            this->logger->trace("Comparing against {0} uniques using {1} threads", n_uniques, omp_get_num_threads());
            bool is_unique = true;

            // testing against all the uniques
#pragma omp parallel for default(none) shared(n_uniques) shared(m) reduction(&&:is_unique)
            for (size_t i = 0; i<n_uniques; ++i) {
                if (rmsd(m, uniques[i].first)<rmsd_threshold) {
                    uniques[i].second++;
                    is_unique = false;
                }
            }
            if (is_unique) {
                uniques.emplace_back(m, 1);
            }
        }
        frames_processed++;
    }
}

double RMSDTrajectoryProcessor::rmsd(const Molecule* A, const Molecule* B) const
{
    if (A->atoms.size()!=B->atoms.size()) {
        this->logger
                ->error("The number of atoms in molecules is not equal: {0} and {1}", A->atoms.size(), B->atoms.size());
        throw std::invalid_argument("The number of atoms in molecules is not equal");
    }

    Eigen::MatrixX3d P(A->atoms.size(), 3);
    Eigen::MatrixX3d Q(B->atoms.size(), 3);

    const Eigen::Vector3d centroidA = A->GetCentroid();
    const Eigen::Vector3d centroidB = B->GetCentroid();

    for (size_t i = 0; i<A->atoms.size(); ++i) {
        P.row(i) = A->atoms[i]->coordinates-centroidA;
        Q.row(i) = B->atoms[i]->coordinates-centroidB;
    }

    const Eigen::Matrix3d R = optimal_rotation_matrix(P, Q);
    return _rmsd(P, Q*R);
}

Eigen::Matrix3d RMSDTrajectoryProcessor::optimal_rotation_matrix(const Eigen::MatrixX3d& P,
        const Eigen::MatrixX3d& Q) const
{
    const auto H = P.transpose()*Q;

//    Eigen::JacobiSVD<Eigen::MatrixX3d> svd;
    Eigen::BDCSVD<Eigen::MatrixX3d> svd;
    svd.compute(H, Eigen::ComputeFullU | Eigen::ComputeFullV);

    int8_t d = (svd.matrixV()*svd.matrixU()).determinant()>0 ? 1 : -1;

    return svd.matrixV()*
            Eigen::DiagonalMatrix<double, 3>(1, 1, d)
            *svd.matrixU().transpose();
}

double RMSDTrajectoryProcessor::_rmsd(const Eigen::MatrixX3d& P, const Eigen::MatrixX3d& Q) const
{
    double rmsd = sqrt((P-Q).squaredNorm()/P.rows());
    this->logger->trace("RMSD = {0:.4f}", rmsd);
    return rmsd;
}

std::vector<std::pair<Molecule*, double>> RMSDTrajectoryProcessor::GetUniques() const
{
    std::vector<std::pair<Molecule*, double>> u;

    double population_sum = std::accumulate(this->uniques.begin(), this->uniques.end(), 0.0,
            [](double previous, auto item) { return previous+item.second; });

    for (const auto p : this->uniques) {
        Molecule* m = new Molecule(*p.first);
        const Eigen::Vector3d mCentroid = m->GetCentroid();
        for (const auto a : m->atoms) {
            a->coordinates -= mCentroid;
        }
        u.emplace_back(p.first, p.second/population_sum);
    } //-V773

    return u;
}
