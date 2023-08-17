find_package(GTest CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_executable(all_tests
        AllTests.cpp
        AtomTests.cpp
        MoleculeTests.cpp
        TrajectoryBuilderTest.cpp)

target_link_libraries(all_tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(all_tests PRIVATE MDConfGenLib)
