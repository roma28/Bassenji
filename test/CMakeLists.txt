find_package(GTest CONFIG REQUIRED)

add_executable(all_tests AtomTests.cpp)
target_link_libraries(all_tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(all_tests PRIVATE MDConfGenLib)
