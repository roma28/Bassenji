cmake_minimum_required(VERSION 3.20)
project(Bassenji)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(pegtl CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)
find_package(Taskflow CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(MDConfGen
        src/main.cpp
        src/molecular/Atom.cpp
        src/molecular/Molecule.cpp
        src/molecular/Residiue.cpp
        src/molecular/Frame.cpp
        src/molecular/Trajectory.cpp
        src/molecular/TrajectoryBuilder.cpp
        src/calculations/RMSDTrajectoryProcessor.cpp
        src/IO/readers/XYZFileReader.cpp
        src/IO/writers/XYZFileWriter.cpp
        src/IO/ReaderFactory.cpp
        src/IO/WriterFactory.cpp)

target_link_libraries(MDConfGen PRIVATE fmt::fmt)
target_link_libraries(MDConfGen PRIVATE spdlog::spdlog)
target_link_libraries(MDConfGen PRIVATE Eigen3::Eigen)
target_link_libraries(MDConfGen PRIVATE cxxopts::cxxopts)
target_link_libraries(MDConfGen PRIVATE Taskflow::Taskflow)
