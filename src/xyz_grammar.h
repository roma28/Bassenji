#ifndef BASSENJI_SRC_XYZ_GRAMMAR_H_
#define BASSENJI_SRC_XYZ_GRAMMAR_H_
#include <tao/pegtl.hpp>

namespace pegtl = tao::pegtl;

struct atom_symbol : pegtl::rep_min_max<1, 2, pegtl::alpha> {
};


struct coordinate : pegtl::seq<
    pegtl::opt<pegtl::one<'-'>>,
    pegtl::plus<pegtl::digit>,
    pegtl::one<'.'>,
    pegtl::plus<pegtl::digit>> {
};


struct xyz_line : pegtl::seq<
    atom_symbol,
    pegtl::blank,
    pegtl::rep<2, pegtl::seq<coordinate, pegtl::blank>>,
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

struct xyz_file : pegtl::seq<
    pegtl::bof,
    pegtl::plus<xyz_frame>,
    pegtl::eof
>{};
#endif //BASSENJI_SRC_XYZ_GRAMMAR_H_
