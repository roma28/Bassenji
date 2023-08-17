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
#include <IO/WriterFactory.h>
#include <IO/writers/XYZFileWriter.h>
#include <IO/writers/SeparateXYZFilesWriter.h>

TEST(WriterFactoryTests, XYZFileWriter)
{
    auto writer = WriterFactory::GetWriter("test.xyz");
    ASSERT_EQ(typeid(*writer), typeid(XYZFileWriter));
}

TEST(WriterFactoryTests, SeparateXYZFilesWriter)
{
    auto writer = WriterFactory::GetWriter("test{}.xyz");
    ASSERT_EQ(typeid(*writer), typeid(SeparateXYZFilesWriter));
}

