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

#ifndef BASSENJI_SRC_MOLECULE_H_
#define BASSENJI_SRC_MOLECULE_H_

#include <vector>

#include "Eigen/Core"

#include "Atom.h"

class Molecule {
    Eigen::Vector3d _centroid;
    bool recalc_centroid = true;

public:
    Molecule() = default;

    ~Molecule();

    std::vector<Atom*> atoms;

    Eigen::Vector3d Centroid();
};

#endif //BASSENJI_SRC_MOLECULE_H_