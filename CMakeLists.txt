cmake_minimum_required(VERSION 3.24)
project(Bassenji)

set(CMAKE_CXX_STANDARD 17)

include_directories(thirdparty/spdlog/include)
include_directories(thirdparty/cxxoptions/include)
include_directories(thirdparty/eigen)
include_directories(thirdparty/lexy/include)
include_directories(thirdparty/PEGTL-3.2.7/include)

#add_library(XYZParser src/XYZParser.cpp)
add_executable(MDConfGen src/main.cpp)
