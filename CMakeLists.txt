cmake_minimum_required(VERSION 3.24)
project(Bassenji)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -O0")

include_directories(thirdparty/spdlog/include)
include_directories(thirdparty/cxxoptions/include)
include_directories(thirdparty/eigen)
include_directories(thirdparty/PEGTL-3.2.7/include)

add_executable(MDConfGen src/main.cpp src/molecular/Atom.cpp src/molecular/Molecule.cpp src/molecular/Residiue.cpp
        src/molecular/Trajectory.cpp src/molecular/Frame.cpp src/molecular/TrajectoryBuilder.cpp)
