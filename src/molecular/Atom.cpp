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

#include "Atom.h"

Atom::Atom(std::string s) {
  this->set_symbol(s);
}

Atom::Atom(std::string s, double x, double y, double z) {
  this->set_symbol(s);
  this->coordinates = {x, y, z};
}

void Atom::set_symbol(const std::string &s) {
  this->atom_symbol = s;
  try {
    this->atom_number = atom_utilities::name_to_number.at(s);
  }
  catch (std::out_of_range &e) {
    spdlog::error("Unsupported atom symbol {0}", s);
  }
  this->atom_mass = atom_utilities::number_to_mass.at(this->atom_number);

};