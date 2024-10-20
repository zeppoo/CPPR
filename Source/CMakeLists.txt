cmake_minimum_required(VERSION 3.28)
project(CPPR)
set(CMAKE_VERBOSE_MAKEFILE ON)


set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(CPPR STATIC
        src/descriptors.cpp
        src/serialization.cpp
        src/type_info.cpp
        src/type_resolver.cpp)


# Add test executable
add_executable(run_tests main.cpp)

# Link the library to the test executable
target_link_libraries(run_tests CPPR)

add_custom_target(tests
        COMMAND run_tests
        DEPENDS run_tests
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

set(MY_LIBRARY_VERSION_MAJOR 1)
set(MY_LIBRARY_VERSION_MINOR 0)