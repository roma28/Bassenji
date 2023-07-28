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

#ifndef BASSENJI_SRC_MOLECULAR_TRAJECTORYBUILDER_H_
#define BASSENJI_SRC_MOLECULAR_TRAJECTORYBUILDER_H_

#include <molecular/Trajectory.h>

class TrajectoryBuilder
{

    Trajectory trajectory;
    uint8_t current_coordinate = 0;

    std::shared_ptr<spdlog::logger> _logger;

public:

    TrajectoryBuilder();

    Trajectory GetTrajectory();

    void NewFrame();

    void NewMolecule();

    void NewAtom();

    void SetCurrentCoordinate(double c);

    void SetCurrentAtom(const std::string& s);

    void NewAtom(const std::string& s, double x, double y, double z);
};

#endif //BASSENJI_SRC_MOLECULAR_TRAJECTORYBUILDER_H_
