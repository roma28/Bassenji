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

#include "WriterFactory.h"
#include <IO/writers/XYZFileWriter.h>

FileWriter* WriterFactory::GetWriter(const std::string& specifier)
{
    return new XYZFileWriter();
}
