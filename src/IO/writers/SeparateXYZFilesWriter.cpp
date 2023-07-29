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


#include "SeparateXYZFilesWriter.h"

void SeparateXYZFilesWriter::WriteFile(const std::vector<std::pair<Molecule, double>>& ensemble,
                                       const std::string& fname) const
{
    int i = 0;
    auto populations = std::ofstream(fmt::format(fname, "population"));
    for (const auto& p : ensemble) {
        auto out = std::ofstream(fmt::format(fname, i) + ".xyz");
        out << fmt::format("{}\n", p.first.n_atom());
        out << "\n";
        out << XYZFileWriter::formatMolecule(p.first);
        ++i;
    }
}
