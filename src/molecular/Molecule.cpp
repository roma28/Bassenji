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
Eigen::Vector3d Molecule::Centroid() const
{
    Eigen::Matrix<double, Eigen::Dynamic, 3> m(this->atoms.size(), 3);
    double total_mass = 0;
    for (size_t i = 0; i<this->atoms.size(); ++i) {
        m.row(i) = this->atoms[i]->coordinates*this->atoms[i]->getMass();
        total_mass += this->atoms[i]->getMass();
    }
    return m.colwise().sum()/total_mass;
}

Molecule::~Molecule()
{
    for (auto a : this->atoms) {
        delete a;
    }
}

