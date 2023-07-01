// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// This is a personal academic project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#ifndef BASSENJI_SRC_PARSER_H_
#define BASSENJI_SRC_PARSER_H_

#include <fstream>

#include "../molecular/Trajectory.h"

namespace parsers {

class Parser {
public:
    Parser() = default;
    virtual Trajectory* parse(std::string file);
};

} // parsers

#endif //BASSENJI_SRC_PARSER_H_
