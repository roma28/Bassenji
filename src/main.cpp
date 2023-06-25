// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// This is a personal academic project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>

#include <Eigen/Core>
#include <cxxopts.hpp>
#include <spdlog/spdlog.h>

#include "xyz_grammar.h"
#include <tao/pegtl/contrib/analyze.hpp>
#include <tao/pegtl.hpp>

int main(int argc, char *argv[]) {
  cxxopts::Options opt("Bassenji", "A MD-based conformer generator");
  opt.allow_unrecognised_options();
  opt.add_options()
      ("i,input", "Input file", cxxopts::value<std::string>())
      ("o,output", "Output file", cxxopts::value<std::string>())
      ("v,verbose", "Logging level", cxxopts::value<int>()->default_value("2"));

  cxxopts::ParseResult options = opt.parse(argc, argv);

  spdlog::info("Bassenji started");
  spdlog::set_level(static_cast<spdlog::level::level_enum>(options["verbose"].as<int>()));

  for (auto const &arg : options.arguments()) {
    spdlog::debug("Argument \"{0}\" with value \"{1}\" received", arg.key(), arg.value());
  }
  for (auto unknown_arg : options.unmatched()) {
    spdlog::warn("Unknown argument received {}", unknown_arg);
  }

  using grammar = tao::pegtl::must<xyz_file>;

  if( pegtl::analyze< grammar >() != 0 ) {
     spdlog::error("cycles without progress detected!");
    return 1;
  }
}
