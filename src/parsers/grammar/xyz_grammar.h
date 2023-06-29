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

#ifndef BASSENJI_SRC_XYZ_GRAMMAR_H_
#define BASSENJI_SRC_XYZ_GRAMMAR_H_
#include <tao/pegtl.hpp>
#include <spdlog/spdlog.h>

#include "../../molecular/TrajectoryBuilder.h"

namespace grammar {
namespace pegtl = tao::pegtl;

struct atom_symbol : pegtl::rep_min_max<1, 2, pegtl::alpha> {};

struct coordinate : pegtl::seq<
    pegtl::opt<pegtl::one<'-'>>,
    pegtl::plus<pegtl::digit>,
    pegtl::one<'.'>,
    pegtl::plus<pegtl::digit>> {
};

struct xyz_line : pegtl::seq<
    atom_symbol,
    pegtl::plus<pegtl::blank>,
    pegtl::rep<2, pegtl::seq<coordinate, pegtl::plus<pegtl::blank>>>,
    coordinate,
    pegtl::eol
> {
};

struct xyz_frame : pegtl::seq<
    pegtl::plus<pegtl::digit>,
    pegtl::eol,
    pegtl::star<pegtl::alpha>,
    pegtl::eol,
    pegtl::plus<xyz_line>,
    pegtl::star<pegtl::eol>
> {
};

struct xyz_file : pegtl::must<pegtl::seq<
    pegtl::bof,
    pegtl::plus<xyz_frame>,
    pegtl::eof
>> {
};

template<typename Rule>
struct xyz_action
    : tao::pegtl::nothing<Rule> {
};

template<>
struct xyz_action<xyz_frame> {
  template<typename ActionInput>
  static void apply(const ActionInput &in, TrajectoryBuilder &tb) {
    tb.NewFrame();
  }
};

template<>
struct xyz_action<xyz_line> {
  template<typename ActionInput>
  static void apply(const ActionInput &in, TrajectoryBuilder &tb) {
    tb.NewAtom();
  }
};

template<>
struct xyz_action<atom_symbol> {
  template<typename ActionInput>
  static void apply(const ActionInput &in, TrajectoryBuilder &tb) {
    spdlog::trace("Setting atom symbol {0}", in.string());
    tb.SetCurrentAtom(in.string());
  }
};

template<>
struct xyz_action<coordinate> {
  template<typename ActionInput>
  static void apply(const ActionInput &in, TrajectoryBuilder &tb) {
    spdlog::trace("Setting atom coordinate {0}", in.string());
    tb.SetCurrentCoordinate(std::stod(in.string()));
  }
};






}
#endif //BASSENJI_SRC_XYZ_GRAMMAR_H_
