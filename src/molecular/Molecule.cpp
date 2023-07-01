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

#include "Molecule.h"
Eigen::Vector3d Molecule::Centroid()
{
    if (this->recalc_centroid) {
        Eigen::Vector3d c = {0, 0, 0};
        float total_mass = 0;
        for (Atom* a : this->atoms) {
            c += a->coordinates*a->getMass();
            total_mass += a->getMass();
        }
        this->_centroid = c/total_mass;
        this->recalc_centroid = false;
    }
    return this->_centroid;
}
Molecule::~Molecule()
{
    for (auto a : this->atoms) {
        delete a;
    }
}

