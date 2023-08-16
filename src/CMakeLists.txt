find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(pegtl CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)
find_package(Taskflow CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(MDConfGen
        main.cpp)

add_library(MDConfGenLib STATIC
        molecular/Atom.cpp
        molecular/Molecule.cpp
        molecular/Residiue.cpp
        molecular/Frame.cpp
        molecular/Trajectory.cpp
        molecular/TrajectoryBuilder.cpp
        calculations/RMSDTrajectoryProcessor.cpp
        IO/readers/XYZFileReader.cpp
        IO/writers/XYZFileWriter.cpp
        IO/ReaderFactory.cpp
        IO/WriterFactory.cpp
        IO/writers/SeparateXYZFilesWriter.cpp
)

target_link_libraries(MDConfGenLib PUBLIC fmt::fmt)
target_link_libraries(MDConfGenLib PUBLIC spdlog::spdlog)
target_link_libraries(MDConfGenLib PUBLIC Eigen3::Eigen)
target_link_libraries(MDConfGenLib PUBLIC cxxopts::cxxopts)
target_link_libraries(MDConfGenLib PUBLIC Taskflow::Taskflow)

target_link_libraries(MDConfGen PRIVATE MDConfGenLib)

