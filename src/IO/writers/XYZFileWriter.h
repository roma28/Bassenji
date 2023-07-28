// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#ifndef BASSENJI_XYZFILEWRITER_H
#define BASSENJI_XYZFILEWRITER_H

#include "FileWriter.h"

class XYZFileWriter : public FileWriter
{
    static std::string formatMolecule(const Molecule& m);
    static std::string formatAtom(const Atom& a);
public:
    void WriteFile(const std::vector<std::pair<Molecule, double>>& ensemble, const std::string& fname) const override;
};

#endif //BASSENJI_XYZFILEWRITER_H
