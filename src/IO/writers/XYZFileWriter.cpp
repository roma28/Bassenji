// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <fstream>

#include "XYZFileWriter.h"

void XYZFileWriter::WriteFile(const std::vector<std::pair<Molecule, double>>& ensemble, const std::string& fname) const
{
    auto out = std::ofstream(fname);
    for (const auto& c : ensemble) {
        out << fmt::format("{}\n", c.first.n_atom());
        out << fmt::format("{:.4f}\n", c.second);
        out << formatMolecule(c.first);
    }
}

std::string XYZFileWriter::formatMolecule(const Molecule& m)
{
    std::string s;
    for (const auto& a : m.atoms) {
        s += formatAtom(a);
    }
    return s;
}

std::string XYZFileWriter::formatAtom(const Atom& a)
{
    return fmt::format("{0}\t{1:.6f}\t{2:.6f}\t{3:.6f}\n",
                       a.GetSymbol(),
                       a.coordinates.x(),
                       a.coordinates.y(),
                       a.coordinates.z());
}
