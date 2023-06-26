#include "Molecule.h"
Molecule::Molecule(std::vector<Atom> atoms) {

}

Eigen::Vector3d Molecule::centerOfMass() {
  Eigen::Vector3d c = {0, 0, 0};
  float total_mass = 0;

  for (Atom a : this->atoms) {
    c += a.coordinates * a.getMass();
    total_mass += a.getMass();
  }

  return c;
}