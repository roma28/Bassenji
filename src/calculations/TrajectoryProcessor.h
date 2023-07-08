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

#ifndef BASSENJI_TRAJECTORYPROCESSOR_H
#define BASSENJI_TRAJECTORYPROCESSOR_H

#include "../molecular/include/Trajectory.h"
class TrajectoryProcessor {

public:
    virtual void Process(const Trajectory* trajectory) = 0;

    virtual std::vector<std::pair<Molecule*, double>> GetUniques() const = 0;
};

#endif //BASSENJI_TRAJECTORYPROCESSOR_H
