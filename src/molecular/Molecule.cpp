// This is a personal academic project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
//

#include "Molecule.h"
Eigen::Vector3d Molecule::centerOfMass() {
  Eigen::Vector3d c = {0, 0, 0};
  float total_mass = 0;

  for (Atom *a : this->atoms) {
    c += a->coordinates * a->getMass();
    total_mass += a->getMass();
  }

  return c/total_mass;
}