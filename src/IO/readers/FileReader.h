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

#ifndef BASSENJI_SRC_PARSER_H_
#define BASSENJI_SRC_PARSER_H_

#include <molecular/Trajectory.h>

class FileReader
{
public:
    FileReader() = default;
    virtual Trajectory ReadFile(const std::string& fname) = 0;
};

#endif //BASSENJI_SRC_PARSER_H_
