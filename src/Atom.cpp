#include "Atom.h"

Atom::Atom(std::string s, double x, double y, double z) {
  this->atom_symbol = s;
  try {
    this->atom_number = atom_utilities::name_to_number.at(s);
  }
  catch (std::out_of_range &e) {
    spdlog::error("Unsupported atom symbol {0}", s);
  }
  this->atom_mass = atom_utilities::number_to_mass.at(this->atom_number);
  coordinates = {x, y, z};
};