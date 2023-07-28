// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
//

#ifndef BASSENJI_MISC_GRAMMAR_H
#define BASSENJI_MISC_GRAMMAR_H

#include <tao/pegtl.hpp>

namespace pegtl = tao::pegtl;


struct atom_symbol : pegtl::rep_min_max<1, 2, pegtl::alpha>
{
};

struct coord_int : pegtl::seq<pegtl::opt<pegtl::one<'-'>>, pegtl::plus<pegtl::digit>>
{
};

struct coord_float : pegtl::seq<pegtl::opt<pegtl::one<'-'>>,
                                pegtl::plus<pegtl::digit>,
                                pegtl::one<'.'>,
                                pegtl::plus<pegtl::digit>,
                                pegtl::opt<pegtl::ascii::string<'e'>, coord_int>>
{
};

struct coordinate : pegtl::sor<coord_float, coord_int>
{
};
#endif //BASSENJI_MISC_GRAMMAR_H
