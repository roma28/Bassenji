// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#ifndef BASSENJI_WRITERFACTORY_H
#define BASSENJI_WRITERFACTORY_H

#include <IO/writers/FileWriter.h>

class WriterFactory
{
public:
    WriterFactory() = delete;
    static std::unique_ptr<FileWriter> GetWriter(const std::string& specifier);
};

#endif //BASSENJI_WRITERFACTORY_H
