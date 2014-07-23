#
#  drsreset - Soft-reset DRS4 Evaluation Boards
#  Copyright (C) 2014  Gregor Vollmer <vollmer@ekp.uni-karlsruhe.de>
# 
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.


cmake_minimum_required(VERSION 2.6)
project(drsreset)

include(FindPkgConfig)
set(CMAKE_CXX_FLAGS "-std=c++11")
pkg_check_modules(LIBUSB10 REQUIRED libusb-1.0)
include_directories(${LIBUSB10_INCLUDE_DIRS})

add_executable(drsreset main.cpp)
target_link_libraries(drsreset ${LIBUSB10_LIBRARIES})

install(TARGETS drsreset RUNTIME DESTINATION bin)
