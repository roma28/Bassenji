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

#ifndef BASSENJI_SRC_MOLECULAR_TRAJECTORYBUILDER_H_
#define BASSENJI_SRC_MOLECULAR_TRAJECTORYBUILDER_H_

#include "Trajectory.h"
class TrajectoryBuilder {

  Trajectory *trajectory;
  Molecule *current_molecule;
  Frame *current_frame;
  Atom *current_atom;
  uint8_t current_coordinate = 0;

 public:

  TrajectoryBuilder();

  Trajectory *GetTrajectory();

  void NewFrame();

  void NewMolecule();

  void NewAtom();

  void SetCurrentCoordinate(double c);

  void SetCurrentAtom(const std::string s);
};

#endif //BASSENJI_SRC_MOLECULAR_TRAJECTORYBUILDER_H_
