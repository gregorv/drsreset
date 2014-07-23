cmake_minimum_required(VERSION 2.6)
project(drsreset)

include(FindPkgConfig)
set(CMAKE_CXX_FLAGS "-std=c++11")
pkg_check_modules(LIBUSB10 REQUIRED libusb-1.0)
include_directories(${LIBUSB10_INCLUDE_DIRS})

add_executable(drsreset main.cpp)
target_link_libraries(drsreset ${LIBUSB10_LIBRARIES})

install(TARGETS drsreset RUNTIME DESTINATION bin)
