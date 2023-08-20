// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#ifndef BASSENJI_MISC_GRAMMAR_H
#define BASSENJI_MISC_GRAMMAR_H

#include <tao/pegtl.hpp>

#define DIGIT_SEQUENCE pegtl::plus<pegtl::digit>
#define MANTISSA pegtl::sor<pegtl::ascii::string<'e'>, pegtl::ascii::string<'E'>>, pegtl::opt<pegtl::string<'-'>, DIGIT_SEQUENCE>

namespace pegtl = tao::pegtl;

struct atom_symbol : pegtl::rep_min_max<1, 2, pegtl::alpha>
{
};

struct num_int : pegtl::seq<
    pegtl::opt<pegtl::one<'-'>>,
    DIGIT_SEQUENCE,
    pegtl::opt<MANTISSA>>
{
};

struct num_float : pegtl::seq<
    pegtl::opt<pegtl::one<'-'>>,
    DIGIT_SEQUENCE,
    pegtl::one<'.'>,
    DIGIT_SEQUENCE,
    pegtl::opt<MANTISSA>>
{
};

struct coordinate : pegtl::sor<num_float, num_int>
{
};
#endif //BASSENJI_MISC_GRAMMAR_H
