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

#ifndef BASSENJI_SRC_CALCULATIONS_RMSDTRAJECTORYPROCEESSOR_H_
#define BASSENJI_SRC_CALCULATIONS_RMSDTRAJECTORYPROCEESSOR_H_
#include "molecular/Trajectory.h"
#include "TrajectoryProcessor.h"

class RMSDTrajectoryProcessor : TrajectoryProcessor
{
protected:
    static double rmsd(const Molecule* A, const Molecule* B);
    static double _rmsd(const Eigen::MatrixX3d& P, const Eigen::MatrixX3d& Q);
    static Eigen::Matrix3d optimal_rotation_matrix(const Eigen::MatrixX3d& P, const Eigen::MatrixX3d& Q);
    static Trajectory rebalance_trajectory(const Trajectory* trajectory);

    double rmsd_threshold;
    std::vector<std::pair<Molecule*, size_t>> uniques;
    std::shared_ptr<spdlog::logger> logger;

public:
    RMSDTrajectoryProcessor(double threshold);

    void Process(const Trajectory* trajectory, size_t n_jobs = 4) override;

    std::vector<std::pair<Molecule*, double>> GetUniques() const override;
};

#endif //BASSENJI_SRC_CALCULATIONS_RMSDTRAJECTORYPROCEESSOR_H_
