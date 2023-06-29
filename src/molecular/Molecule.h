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

#ifndef BASSENJI_SRC_MOLECULE_H_
#define BASSENJI_SRC_MOLECULE_H_

#include <vector>

#include "Eigen/Core"

#include "Atom.h"

class Molecule {
 public:
  Molecule() = default;

  std::vector<Atom*> atoms;

  Eigen::Vector3d centerOfMass();
};

#endif //BASSENJI_SRC_MOLECULE_H_
