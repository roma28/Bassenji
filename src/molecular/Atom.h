// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#ifndef BASSENJI_SRC_ATOM_H_
#define BASSENJI_SRC_ATOM_H_

#include <unordered_map>

#include "Eigen/Core"
#include <spdlog/spdlog.h>

namespace atom_utilities
{
const static std::unordered_map<uint8_t, float> number_to_mass =
    {{1, 1.00797}, {2, 4.00260}, {3, 6.941}, {4, 9.01218}, {5, 10.81}, {6, 12.011}, {7, 14.0067}, {8, 15.9994},
     {9, 18.998403}, {10, 20.179}, {11, 22.98977}, {12, 24.305}, {13, 26.98154}, {14, 28.0855}, {15, 30.97376},
     {16, 32.06}, {17, 35.453}, {19, 39.0983}, {18, 39.948}, {20, 40.08}, {21, 44.9559}, {22, 47.90}, {23, 50.9415},
     {24, 51.996}, {25, 54.9380}, {26, 55.847}, {28, 58.70}, {27, 58.9332}, {29, 63.546}, {30, 65.38}, {31, 69.72},
     {32, 72.59}, {33, 74.9216}, {34, 78.96}, {35, 79.904}, {36, 83.80}, {37, 85.4678}, {38, 87.62}, {39, 88.9059},
     {40, 91.22}, {41, 92.9064}, {42, 95.94}, {43, 98}, {44, 101.07}, {45, 102.9055}, {46, 106.4}, {47, 107.868},
     {48, 112.41}, {49, 114.82}, {50, 118.69}, {51, 121.75}, {53, 126.9045}, {52, 127.60}, {54, 131.30}, {55, 132.9054},
     {56, 137.33}, {57, 138.9055}, {58, 140.12}, {59, 140.9077}, {60, 144.24}, {61, 145}, {62, 150.4}, {63, 151.96},
     {64, 157.25}, {65, 158.9254}, {66, 162.50}, {67, 164.9304}, {68, 167.26}, {69, 168.9342}, {70, 173.04},
     {71, 174.967}, {72, 178.49}, {73, 180.9479}, {74, 183.85}, {75, 186.207}, {76, 190.2}, {77, 192.22}, {78, 195.09},
     {79, 196.9665}, {80, 200.59}, {81, 204.37}, {82, 207.2}, {83, 208.9804}, {84, 209}, {85, 210}, {86, 222},
     {87, 223}, {88, 226.0254}, {89, 227.0278}, {90, 232.0381},};

const static std::unordered_map<uint8_t, std::string> number_to_name =
    {{1, "H"}, {2, "He"}, {3, "Li"}, {4, "Be"}, {5, "B"}, {6, "C"}, {7, "N"}, {8, "O"}, {9, "F"}, {10, "Ne"},
     {11, "Na"}, {12, "Mg"}, {13, "Al"}, {14, "Si"}, {15, "P"}, {16, "S"}, {17, "Cl"}, {18, "Ar"}, {19, "K"},
     {20, "Ca"}, {21, "Sc"}, {22, "Ti"}, {23, "V"}, {24, "Cr"}, {25, "Mn"}, {26, "Fe"}, {27, "Co"}, {28, "Ni"},
     {29, "Cu"}, {30, "Zn"}, {31, "Ga"}, {32, "Ge"}, {33, "As"}, {34, "Se"}, {35, "Br"}, {36, "Kr"}, {37, "Rb"},
     {38, "Sr"}, {39, "Y"}, {40, "Zr"}, {41, "Nb"}, {42, "Mo"}, {43, "Tc"}, {44, "Ru"}, {45, "Rh"}, {46, "Pd"},
     {47, "Ag"}, {48, "Cd"}, {49, "In"}, {50, "Sn"}, {51, "Sb"}, {52, "Te"}, {53, "I"}, {54, "Xe"}, {55, "Cs"},
     {56, "Ba"}, {57, "La"}, {58, "Ce"}, {59, "Pr"}, {60, "Nd"}, {61, "Pm"}, {62, "Sm"}, {63, "Eu"}, {64, "Gd"},
     {65, "Tb"}, {66, "Dy"}, {67, "Ho"}, {68, "Er"}, {69, "Tm"}, {70, "Yb"}, {71, "Lu"}, {72, "Hf"}, {73, "Ta"},
     {74, "W"}, {75, "Re"}, {76, "Os"}, {77, "Ir"}, {78, "Pt"}, {79, "Au"}, {80, "Hg"}, {81, "Tl"}, {82, "Pb"},
     {83, "Bi"}, {84, "Po"}, {85, "At"}, {86, "Rn"}, {87, "Fr"}, {88, "Ra"}, {89, "Ac"}, {90, "Th"}};

const static std::unordered_map<std::string, uint8_t> name_to_number =
    {{"H", 1}, {"He", 2}, {"Li", 3}, {"Be", 4}, {"B", 5}, {"C", 6}, {"N", 7}, {"O", 8}, {"F", 9}, {"Ne", 10},
     {"Na", 11}, {"Mg", 12}, {"Al", 13}, {"Si", 14}, {"P", 15}, {"S", 16}, {"Cl", 17}, {"Ar", 18}, {"K", 19},
     {"Ca", 20}, {"Sc", 21}, {"Ti", 22}, {"V", 23}, {"Cr", 24}, {"Mn", 25}, {"Fe", 26}, {"Co", 27}, {"Ni", 28},
     {"Cu", 29}, {"Zn", 30}, {"Ga", 31}, {"Ge", 32}, {"As", 33}, {"Se", 34}, {"Br", 35}, {"Kr", 36}, {"Rb", 37},
     {"Sr", 38}, {"Y", 39}, {"Zr", 40}, {"Nb", 41}, {"Mo", 42}, {"Tc", 43}, {"Ru", 44}, {"Rh", 45}, {"Pd", 46},
     {"Ag", 47}, {"Cd", 48}, {"In", 49}, {"Sn", 50}, {"Sb", 51}, {"Te", 52}, {"I", 53}, {"Xe", 54}, {"Cs", 55},
     {"Ba", 56}, {"La", 57}, {"Ce", 58}, {"Pr", 59}, {"Nd", 60}, {"Pm", 61}, {"Sm", 62}, {"Eu", 63}, {"Gd", 64},
     {"Tb", 65}, {"Dy", 66}, {"Ho", 67}, {"Er", 68}, {"Tm", 69}, {"Yb", 70}, {"Lu", 71}, {"Hf", 72}, {"Ta", 73},
     {"W", 74}, {"Re", 75}, {"Os", 76}, {"Ir", 77}, {"Pt", 78}, {"Au", 79}, {"Hg", 80}, {"Tl", 81}, {"Pb", 82},
     {"Bi", 83}, {"Po", 84}, {"At", 85}, {"Rn", 86}, {"Fr", 87}, {"Ra", 88}, {"Ac", 89}, {"Th", 90}};
}

class Atom
{
    uint8_t atom_number;
    float atom_mass;
    std::string atom_symbol;

public:
    Atom() = default;

    Atom(const Atom& a) = default;

    Atom(const std::string& symbol);

    Atom(const std::string& symbol, double x, double y, double z);

    Eigen::Vector3d coordinates;

    float Mass() const
    {
        return this->atom_mass;
    }

    uint8_t Number() const
    {
        return this->atom_number;
    }

    std::string Symbol() const
    {
        return this->atom_symbol;
    }

    void SetSymbol(const std::string& s);
};

#endif //BASSENJI_SRC_ATOM_H_
