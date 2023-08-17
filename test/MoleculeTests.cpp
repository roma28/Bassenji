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
#include <molecular/Molecule.h>

class MoleculeTests : public ::testing::Test
{
protected:
    Molecule m;

    void SetUp() override
    {};

    void TearDown() override
    {};
};


TEST_F(MoleculeTests, Construction)
{
    ASSERT_EQ(m.NAtom(), 0);
    ASSERT_ANY_THROW(m.Centroid());
}

TEST_F(MoleculeTests, Atoms)
{
    m.atoms.emplace_back("C");
    m.atoms.emplace_back("H");

    ASSERT_EQ(m.NAtom(), 2);
    ASSERT_EQ(m.atoms[0].Symbol(), "C");
    ASSERT_EQ(m.atoms[1].Symbol(), "H");
}

TEST_F(MoleculeTests, Centroid)
{
    m.atoms.emplace_back("C", 1.0, 2.0, 3.0);
    m.atoms.emplace_back("C", 3.0, 4.0, 5.0);
    m.UpdateCentroid();

    ASSERT_DOUBLE_EQ((1 + 3) / 2, m.Centroid().x());
    ASSERT_DOUBLE_EQ((2 + 4) / 2, m.Centroid().y());
    ASSERT_DOUBLE_EQ((3 + 5) / 2, m.Centroid().z());
}
