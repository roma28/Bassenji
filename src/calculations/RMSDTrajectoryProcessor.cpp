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

void RMSDTrajectoryProcessor::Process(const Trajectory& trajectory)
{
    for (auto f : trajectory.frames) {
        for (auto m : f->molecules) {
            if (this->uniques.empty()) {
                this->uniques.emplace_back(m, 1);
                continue;
            }
            for (size_t i = 0; i<this->uniques.size(); ++i) {
                if (rmsd(*m, *(this->uniques[i].first))<rmsd_threshold) {
                    this->uniques[i].second++;
                }
                else {
                    this->uniques.emplace_back(m, 1);
                }
            }
        }
    }
}

double RMSDTrajectoryProcessor::rmsd(const Molecule& A, const Molecule& B)
{
    if (A.atoms.size()!=B.atoms.size()) {
        spdlog::error("The number of atoms in molecules is not equal: {0} and {1}", A.atoms.size(), B.atoms.size());
        throw std::invalid_argument("The number of atoms in molecules is not equal");
    }

    Eigen::MatrixX3d P(A.atoms.size(), 3);
    Eigen::MatrixX3d Q(B.atoms.size(), 3);

    Eigen::Vector3d centroidA = A.Centroid();
    Eigen::Vector3d centroidB = B.Centroid();

    for (size_t i = 0; i<A.atoms.size(); ++i) {
        P.row(i) = A.atoms[i]->coordinates-centroidA;
        Q.row(i) = B.atoms[i]->coordinates-centroidB;
    }

    Eigen::Matrix3d R = optimal_rotation_matrix(P, Q);
    return _rmsd(P, Q*R);
}

Eigen::Matrix3d RMSDTrajectoryProcessor::optimal_rotation_matrix(const Eigen::MatrixX3d& P,
        const Eigen::MatrixX3d& Q)
{
    auto H = P.transpose()*Q;

    Eigen::JacobiSVD<Eigen::MatrixX3d, Eigen::ComputeFullU | Eigen::ComputeFullV> svd(H);

    int8_t d = svd.matrixV().determinant()*svd.matrixU().determinant()>0 ? 1 : -1;

    return svd.matrixV()*
            Eigen::DiagonalMatrix<double, 3>(1, 1, d)
            *svd.matrixU().transpose();
}

double RMSDTrajectoryProcessor::_rmsd(const Eigen::MatrixX3d& P, const Eigen::MatrixX3d& Q)
{
    return sqrt((P-Q).squaredNorm()/P.rows());
}

RMSDTrajectoryProcessor::RMSDTrajectoryProcessor(double threshold)
{
    this->rmsd_threshold = threshold;
}

std::vector<std::pair<Molecule*, double>> RMSDTrajectoryProcessor::GetUniques() const
{
    std::vector<std::pair<Molecule*, double>> u;

    double population_sum = std::accumulate(this->uniques.begin(), this->uniques.end(), 0.0,
            [](double previous, auto item) { return previous+item.second; });

    for (auto p : this->uniques) {
        Molecule* m = new Molecule(*p.first);
        Eigen::Vector3d mCentroid = m->Centroid();
        for (auto a : m->atoms) {
            a->coordinates -= mCentroid;
        }
        u.emplace_back(p.first, p.second/population_sum);
    }

    return u;
}
