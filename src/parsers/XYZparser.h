// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
//
// This is a personal academic project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#ifndef BASSENJI_SRC_XYZPARSER_H_
#define BASSENJI_SRC_XYZPARSER_H_

#include "Parser.h"
namespace parsers {
class XYZparser : Parser {
    XYZparser() = default;
    Trajectory* parse(std::string fname);
};
}
#endif //BASSENJI_SRC_XYZPARSER_H_
