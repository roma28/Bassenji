// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// This is a personal academic project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "XYZparser.h"
#include "grammar/xyz_grammar.h"
#include "tao/pegtl/contrib/parse_tree.hpp"

namespace parsers {
Trajectory * XYZparser::parse(std::string fname) {
  auto in = tao::pegtl::file_input<>(fname);
  auto root = tao::pegtl::parse_tree::parse<grammar::xyz_file>(in);
  spdlog::debug("Parsing done");

//  root->children.
  return NULL;
}
}

