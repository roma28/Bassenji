#ifndef BASSENJI_MISC_GRAMMAR_H
#define BASSENJI_MISC_GRAMMAR_H

#include <tao/pegtl.hpp>

namespace pegtl = tao::pegtl;


struct atom_symbol : pegtl::rep_min_max<1, 2, pegtl::alpha> { };

struct coord_float : pegtl::seq<
        pegtl::opt<pegtl::one<'-'>>,
        pegtl::plus<pegtl::digit>,
        pegtl::one<'.'>,
        pegtl::plus<pegtl::digit>> {
};

struct coord_int : pegtl::seq<
        pegtl::opt<pegtl::one<'-'>>,
        pegtl::plus<pegtl::digit>> {
};

struct coordinate : pegtl::sor<coord_float, coord_int> {
};
#endif //BASSENJI_MISC_GRAMMAR_H
