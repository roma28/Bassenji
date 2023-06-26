#ifndef BASSENJI_SRC_MOLECULE_H_
#define BASSENJI_SRC_MOLECULE_H_

#include <vector>

#include <Eigen/Core>

#include "Atom.h"

class Molecule {
 public:
  Molecule(std::vector<Atom> atoms);

  std::vector<Atom> atoms;

  Eigen::Vector3d centerOfMass();
};

#endif //BASSENJI_SRC_MOLECULE_H_
