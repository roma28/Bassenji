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

#include "XYZFileReader.h"
#include "grammar/xyz_grammar.h"

Trajectory XYZFileReader::ReadFile(const std::string& fname)
{
    auto in = tao::pegtl::file_input<>(fname);
    TrajectoryBuilder tb = TrajectoryBuilder();
    spdlog::debug("Starting to parse XYZ file {0}", fname);
    tao::pegtl::parse<xyz_file, xyz_action>(in, tb);
    spdlog::debug("Parsing done");

    return tb.GetTrajectory();
}

