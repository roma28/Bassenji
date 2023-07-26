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

#ifndef BASSENJI_READERFACTORY_H
#define BASSENJI_READERFACTORY_H

#include <IO/readers/FileReader.h>

class ReaderFactory
{
public:
    ReaderFactory() = delete;
    static FileReader* GetReader(const std::string& specifier);
};

#endif //BASSENJI_READERFACTORY_H
