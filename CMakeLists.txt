# mbed-cmake requires at least CMake 3.12
cmake_minimum_required(VERSION 3.12)

# load project upload methods (must be before mbed-cmake is loaded)
# -------------------------------------------------------------
include(cmake/UploadMethodConfig.cmake)

# load compilers and flags
# -------------------------------------------------------------

include(mbed-cmake/mbed-cmake.cmake)

project(mbed-cmake-test-project LANGUAGES NONE)

# recurse to subdirectories
# -------------------------------------------------------------

add_mbed_executable(hello_world HelloWorld.cpp)
add_mbed_executable(test test.cpp pretty_printer.h)
add_mbed_executable(connect connect.cpp pretty_printer.h)
add_mbed_executable(connectable connectable.cpp pretty_printer.h)

# build report
# -------------------------------------------------------------

mbed_cmake_print_build_report()