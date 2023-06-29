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

#ifndef BASSENJI_SRC_MOLECULAR_FRAME_H_
#define BASSENJI_SRC_MOLECULAR_FRAME_H_

#include <vector>

#include "Molecule.h"

class Frame {
 public:
  std::vector<Molecule*> molecules;
  Frame() = default;
};

#endif //BASSENJI_SRC_MOLECULAR_FRAME_H_
