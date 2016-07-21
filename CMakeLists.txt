#
# This file is part of the VSS-Viewer project.
#
# This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
# v. 3.0. If a copy of the GPL was not distributed with this
# file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
#

PROJECT(VSS-Viewer)
# CONFIG
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11 -pthread")

# PROTO
ADD_SUBDIRECTORY(protos)

# GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)


# COMPILE
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
ADD_EXECUTABLE(VSS-Viewer src/main.cpp src/interface.cpp src/graphics.cpp)
TARGET_LINK_LIBRARIES(VSS-Viewer proto ${PROTOBUF_LIBRARY} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} -lzmq)