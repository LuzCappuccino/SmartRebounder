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

set(SMART_REBOUNDER_SOURCES
	WiimotePixart.cpp
	WiimotePixart.h)


add_mbed_executable(test_pixart WiimotePixart.cpp WiimotePixart.h TestPixartSensor.cpp)

add_mbed_executable(hello_world HelloWorld.cpp mbed-cmake/mbed-src/connectivity/FEATURE_BLE/include/ble/services/HeartRateService.h)
add_mbed_executable(test test.cpp pretty_printer.h)
add_mbed_executable(connect connect.cpp pretty_printer.h)
add_mbed_executable(modeSwitch ModeSwitchService.cpp BleProcess.h pretty_printer.h)
# build report
# -------------------------------------------------------------

mbed_cmake_print_build_report()