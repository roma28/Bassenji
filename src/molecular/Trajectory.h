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

#ifndef BASSENJI_SRC_MOLECULAR_TRAJECTORY_H_
#define BASSENJI_SRC_MOLECULAR_TRAJECTORY_H_

#include <vector>

#include "Frame.h"

class Trajectory
{
public:
    std::vector<Frame*> frames;

    Trajectory() = default;

    ~Trajectory();

    size_t n_frames() const;

};

#endif //BASSENJI_SRC_MOLECULAR_TRAJECTORY_H_
