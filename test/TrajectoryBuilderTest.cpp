// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>
#include <molecular/TrajectoryBuilder.h>

class TrajectoryBuilderTests : public ::testing::Test
{
protected:
    TrajectoryBuilder tb;

    void SetUp() override
    {
        tb.NewFrame();
        tb.NewMolecule();
        tb.NewAtom();
    };

    void TearDown() override
    {};
};

TEST_F(TrajectoryBuilderTests, NewFrame)
{
    tb.NewFrame();
    ASSERT_EQ(tb.GetTrajectory().NFrames(), 2);
}

TEST_F(TrajectoryBuilderTests, NewMolecule)
{
    tb.NewMolecule();
    ASSERT_EQ(tb.GetTrajectory().frames.back().NMol(), 2);
}

TEST_F(TrajectoryBuilderTests, NewAtom)
{
    tb.NewAtom();
    ASSERT_EQ(tb.GetTrajectory().frames.back().molecules.back().NAtom(), 2);
}

TEST_F(TrajectoryBuilderTests, NewAtomFullConstructor)
{
    tb.NewAtom("C", 1, 2, 3);
    auto current_atom = tb.GetTrajectory().frames.back().molecules.back().atoms.back();
    ASSERT_EQ(current_atom.Symbol(), "C");
    ASSERT_EQ(current_atom.Number(), atom_utilities::name_to_number.at("C"));
    ASSERT_EQ(current_atom.Mass(), atom_utilities::number_to_mass.at(atom_utilities::name_to_number.at("C")));
    ASSERT_DOUBLE_EQ(current_atom.coordinates.x(), 1);
    ASSERT_DOUBLE_EQ(current_atom.coordinates.y(), 2);
    ASSERT_DOUBLE_EQ(current_atom.coordinates.z(), 3);
}

TEST_F(TrajectoryBuilderTests, SetCurrentAtom)
{
    tb.SetCurrentAtom("C");
    auto current_atom = tb.GetTrajectory().frames.back().molecules.back().atoms.back();
    ASSERT_EQ(current_atom.Symbol(), "C");
    ASSERT_EQ(current_atom.Number(), atom_utilities::name_to_number.at("C"));
    ASSERT_EQ(current_atom.Mass(), atom_utilities::number_to_mass.at(atom_utilities::name_to_number.at("C")));
}

TEST_F(TrajectoryBuilderTests, SetCurrentCoordinate)
{
    tb.SetCurrentCoordinate(1);
    tb.SetCurrentCoordinate(2);
    tb.SetCurrentCoordinate(3);
    auto current_atom = tb.GetTrajectory().frames.back().molecules.back().atoms.back();
    ASSERT_DOUBLE_EQ(current_atom.coordinates.x(), 1);
    ASSERT_DOUBLE_EQ(current_atom.coordinates.y(), 2);
    ASSERT_DOUBLE_EQ(current_atom.coordinates.z(), 3);
}

TEST_F(TrajectoryBuilderTests, CentroidUpdate)
{
    ASSERT_NO_THROW(tb.GetTrajectory().frames.back().molecules.back().Centroid());
}