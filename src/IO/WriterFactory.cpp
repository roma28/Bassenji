// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include "WriterFactory.h"
#include <IO/writers/XYZFileWriter.h>
#include <IO/writers/SeparateXYZFilesWriter.h>

std::unique_ptr<FileWriter> WriterFactory::GetWriter(const std::string& specifier)
{
    if (specifier.find('{') != std::string::npos) {
        return std::move(std::make_unique<SeparateXYZFilesWriter>());
    }
    return std::move(std::make_unique<XYZFileWriter>());
}
