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

#include "include/Molecule.h"
void Molecule::CalculateCentroid()
{
        Eigen::Matrix<double, Eigen::Dynamic, 3> m(this->atoms.size(), 3);
        double total_mass = 0;
        for (size_t i = 0; i<this->atoms.size(); ++i) {
            m.row(i) = this->atoms[i]->coordinates*this->atoms[i]->GetMass();
            total_mass += this->atoms[i]->GetMass();
        }
        _centroid = m.colwise().sum()/total_mass;
}

Molecule::~Molecule()
{
    for (auto a : this->atoms) {
        delete a;
    }
}
Molecule::Molecule(const Molecule& m)
{
    for (auto a : m.atoms) {
        this->atoms.push_back(new Atom(*a));
    }
}
Eigen::Vector3d Molecule::GetCentroid() const
{
    return _centroid;
}

