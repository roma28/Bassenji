cmake_minimum_required(VERSION 3.20)
project(Bassenji)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)

add_test(all_gtests all_tests)
