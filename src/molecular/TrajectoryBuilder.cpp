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

#include "TrajectoryBuilder.h"
#include <spdlog/sinks/stdout_color_sinks.h>

TrajectoryBuilder::TrajectoryBuilder()
{
    _logger = spdlog::stdout_color_st("TrajectoryBuilder");
    _logger->debug("Trajectory builder started");
}

Trajectory TrajectoryBuilder::GetTrajectory()
{
    for (auto& f : trajectory.frames) {
        for (auto& m : f.molecules) {
            m.UpdateCentroid();
        }
    }
    return trajectory;
}

void TrajectoryBuilder::NewFrame()
{
    _logger->trace("New frame");
    trajectory.frames.emplace_back();
}

void TrajectoryBuilder::NewMolecule()
{
    _logger->trace("New molecule");
    trajectory.frames.back().molecules.emplace_back();
}

void TrajectoryBuilder::NewAtom()
{
    _logger->trace("New atom");
    trajectory.frames.back().molecules.back().atoms.emplace_back();
    current_coordinate = 0;
}

void TrajectoryBuilder::NewAtom(const std::string& s, double x, double y, double z)
{
    _logger->trace("New atom");
    trajectory.frames.back().molecules.back().atoms.emplace_back(s, x, y, z);
    current_coordinate = 0;
}

void TrajectoryBuilder::SetCurrentAtom(const std::string& s)
{
    _logger->trace("Setting current atom to {0}", s);
    trajectory.frames.back().molecules.back().atoms.back().set_symbol(s);
}

void TrajectoryBuilder::SetCurrentCoordinate(double c)
{
    _logger->trace("Setting current coordinate {0} to {1}", current_coordinate, c);
    trajectory.frames.back().molecules.back().atoms.back().coordinates[this->current_coordinate] = c;
    current_coordinate++;
}

