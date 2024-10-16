cmake_minimum_required(VERSION 3.28)
project(CPPR)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(CPPR STATIC
        src/cppr.cpp
        src/cppr_tests.cpp
        src/descriptors.cpp
        src/serialization.cpp
        src/type_decleration.cpp
        src/type_info.cpp
        src/type_resolver.cpp)

set(MY_LIBRARY_VERSION_MAJOR 1)
set(MY_LIBRARY_VERSION_MINOR 0)