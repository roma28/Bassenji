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

TrajectoryBuilder::TrajectoryBuilder()
{
    spdlog::trace("Starting trajectory builder");
    this->trajectory = new Trajectory();
//  this->NewFrame();
}
Trajectory* TrajectoryBuilder::GetTrajectory()
{
    return this->trajectory;
}

void TrajectoryBuilder::NewFrame()
{
    spdlog::trace("trajectory builder new frame");
    auto f = new Frame();
    this->trajectory->frames.push_back(f);
    this->current_frame = f;
//  this->NewMolecule();
}

void TrajectoryBuilder::NewMolecule()
{
    spdlog::trace("trajectory builder new molecule");
    auto m = new Molecule();
    this->current_frame->molecules.push_back(m);
    this->current_molecule = m;
//  NewAtom();
}

void TrajectoryBuilder::NewAtom()
{
    spdlog::trace("trajectory builder new atom");
    auto a = new Atom();
    this->current_molecule->atoms.push_back(a);
    this->current_atom = a;
    this->current_coordinate = 0;
}

void TrajectoryBuilder::SetCurrentAtom(const std::string& s)
{
    this->current_atom->set_symbol(s);
}

void TrajectoryBuilder::SetCurrentCoordinate(double c)
{
    this->current_atom->coordinates[this->current_coordinate] = c;
    this->current_coordinate++;
}

