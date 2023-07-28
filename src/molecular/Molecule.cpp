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

void Molecule::UpdateCentroid()
{
    Eigen::Matrix<double, Eigen::Dynamic, 3> m(n_atom(), 3);
    double total_mass = 0;
    for (size_t i = 0; i < n_atom(); ++i) {
        m.row(i) = atoms[i].coordinates * atoms[i].GetMass();
        total_mass += atoms[i].GetMass();
    }
    _centroid = m.colwise().sum() / total_mass;
}

Eigen::Vector3d Molecule::GetCentroid() const
{
    return _centroid;
}

