PROJECT(vss-viewer)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
SET(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -Werror -lm -o2")

ADD_SUBDIRECTORY(VSS-Interface)

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

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE VSS VSS-Interface/*.cpp)

ADD_EXECUTABLE(vss-viewer ${SRC} ${VSS})

target_include_directories(vss-viewer PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_link_libraries(vss-viewer PUBLIC ${ZeroMQ_LIBRARY})

TARGET_LINK_LIBRARIES(vss-viewer VSS-Interface ${PROTOBUF_LIBRARY} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
TARGET_LINK_LIBRARIES(vss-viewer LINK_PUBLIC ${Boost_LIBRARIES})

INSTALL(TARGETS vss-viewer DESTINATION bin)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_NAME "vss-viewer")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "A 3D Software of visualization of states given by VSS-Simulator and VSS-Vision")
SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://sirlab.github.io/VSS-SDK/")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Johnathan Fercher")
SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

INCLUDE(CPack)
