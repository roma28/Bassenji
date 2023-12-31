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
#include <molecular/Atom.h>

class AtomTests : public ::testing::Test
{
protected:
    void SetUp() override
    {};

    void TearDown() override
    {};
};

TEST_F(AtomTests, ConstructionFromSymbol)
{
    for (auto p : atom_utilities::name_to_number) {
        Atom a(p.first);
        ASSERT_EQ(a.Number(), p.second);
        ASSERT_FLOAT_EQ(a.Mass(), atom_utilities::number_to_mass.at(p.second));
    }
}

TEST_F(AtomTests, ConstructionFromUnsupportedSymbol)
{
    ASSERT_ANY_THROW(Atom a("A"));
    ASSERT_ANY_THROW(Atom a("E"));
}

TEST_F(AtomTests, ConstructionFromSymbolAndCoordinates)
{
    for (auto p : atom_utilities::name_to_number) {
        Atom a(p.first, 1, 2, 3);
        ASSERT_EQ(a.Number(), p.second);
        ASSERT_FLOAT_EQ(a.Mass(), atom_utilities::number_to_mass.at(p.second));
        ASSERT_DOUBLE_EQ(a.coordinates.x(), 1);
        ASSERT_DOUBLE_EQ(a.coordinates.y(), 2);
        ASSERT_DOUBLE_EQ(a.coordinates.z(), 3);
    }
}

TEST_F(AtomTests, SetSymbol)
{
    for (auto p : atom_utilities::name_to_number) {
        Atom a;
        a.SetSymbol(p.first);
        ASSERT_EQ(a.Number(), p.second);
        ASSERT_FLOAT_EQ(a.Mass(), atom_utilities::number_to_mass.at(p.second));
    }
}

