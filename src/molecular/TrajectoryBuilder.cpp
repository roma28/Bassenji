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

#include "include/TrajectoryBuilder.h"
#include <spdlog/sinks/stdout_color_sinks.h>

TrajectoryBuilder::TrajectoryBuilder()
{
    this->logger = spdlog::stdout_color_st("TrajectoryBuilder");
    this->logger->debug("Trajectory builder started");
    this->trajectory = new Trajectory();
}

Trajectory* TrajectoryBuilder::GetTrajectory()
{
    return this->trajectory;
}

void TrajectoryBuilder::NewFrame()
{
    this->logger->trace("New frame");
    auto f = new Frame();
    this->trajectory->frames.push_back(f);
    this->current_frame = f;
}

void TrajectoryBuilder::NewMolecule()
{
    this->logger->trace("New molecule");
    auto m = new Molecule();
    this->current_frame->molecules.push_back(m);
    if (current_molecule) {
        current_molecule->CalculateCentroid();
    }
    this->current_molecule = m;
}

void TrajectoryBuilder::NewAtom()
{
    this->logger->trace("New atom");
    auto a = new Atom();
    this->current_molecule->atoms.push_back(a);
    this->current_atom = a;
    this->current_coordinate = 0;
}

void TrajectoryBuilder::SetCurrentAtom(const std::string& s)
{
    this->logger->trace("Setting current atom to {0}", s);
    this->current_atom->set_symbol(s);
}

void TrajectoryBuilder::SetCurrentCoordinate(double c)
{
    this->logger->trace("Setting current coordinate {0} to {1}", current_coordinate, c);
    this->current_atom->coordinates[this->current_coordinate] = c;
    this->current_coordinate++;
}

