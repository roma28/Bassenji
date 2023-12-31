// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#ifndef SEPARATEXYZFILESWRITER_H
#define SEPARATEXYZFILESWRITER_H

#include "XYZFileWriter.h"

class SeparateXYZFilesWriter : public XYZFileWriter
{
public:
    SeparateXYZFilesWriter() = default;
    void WriteFile(const std::vector<std::pair<Molecule, double>>& ensemble, const std::string& fname) const override;
};


#endif //SEPARATEXYZFILESWRITER_H
