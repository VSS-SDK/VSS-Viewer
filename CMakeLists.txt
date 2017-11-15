PROJECT(VSS-Viewer)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11")

ADD_SUBDIRECTORY(proto)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
find_package(PkgConfig)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )

find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})

ADD_EXECUTABLE(VSS-Viewer main.cpp graphics.cpp interface.cpp)

target_include_directories(VSS-Viewer PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_link_libraries(VSS-Viewer PUBLIC ${ZeroMQ_LIBRARY})

TARGET_LINK_LIBRARIES(VSS-Viewer proto ${PROTOBUF_LIBRARY} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
TARGET_LINK_LIBRARIES(VSS-Viewer LINK_PUBLIC ${Boost_LIBRARIES})
