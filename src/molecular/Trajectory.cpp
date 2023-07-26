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

#include "Trajectory.h"

Trajectory::~Trajectory()
{
    for (auto f : this->frames) {
//        delete f;
    }
}

size_t Trajectory::n_frames() const
{
    return frames.size();
}
