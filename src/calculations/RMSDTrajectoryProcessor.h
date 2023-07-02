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
#include "../molecular/include/Trajectory.h"
#include "TrajectoryProcessor.h"

class RMSDTrajectoryProcessor : TrajectoryProcessor {
    static double rmsd(const Molecule& A, const Molecule& B);
    static double _rmsd(const Eigen::MatrixX3d& P, const Eigen::MatrixX3d& Q);
    static Eigen::Matrix3d optimal_rotation_matrix(const Eigen::MatrixX3d& P, const Eigen::MatrixX3d& Q);

    double rmsd_threshold;
    std::vector<std::pair<Molecule*, uint32_t>> uniques;

public:
    RMSDTrajectoryProcessor(double threshold);

    void Process(const Trajectory& trajectory);

    std::vector<std::pair<Molecule*, double>> GetUniques() const;
};

#endif //BASSENJI_SRC_CALCULATIONS_RMSDTRAJECTORYPROCEESSOR_H_
