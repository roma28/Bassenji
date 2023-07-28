// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#ifndef BASSENJI_SRC_XYZPARSER_H_
#define BASSENJI_SRC_XYZPARSER_H_

#include "FileReader.h"

class XYZFileReader final : public FileReader
{
public:
    XYZFileReader() = default;
    Trajectory ReadFile(const std::string& fname) override;
};

#endif //BASSENJI_SRC_XYZPARSER_H_
