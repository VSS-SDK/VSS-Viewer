PROJECT(vss-viewer)
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

ADD_EXECUTABLE(vss-viewer main.cpp graphics.cpp interface.cpp)

target_include_directories(vss-viewer PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_link_libraries(vss-viewer PUBLIC ${ZeroMQ_LIBRARY})

TARGET_LINK_LIBRARIES(vss-viewer proto ${PROTOBUF_LIBRARY} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
TARGET_LINK_LIBRARIES(vss-viewer LINK_PUBLIC ${Boost_LIBRARIES})

INSTALL(TARGETS vss-viewer DESTINATION bin)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_NAME "vss-viewer")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "A 3D Software of visualization of states given by VSS-Simulator and VSS-Vision")
SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://sirlab.github.io/VSS-SDK/")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Johnathan Fercher")

FIND_PROGRAM(LSB_RELEASE_EXECUTABLE lsb_release)
MARK_AS_ADVANCED(LSB_RELEASE_EXECUTABLE)

IF(LSB_RELEASE_EXECUTABLE)
  EXECUTE_PROCESS(COMMAND ${LSB_RELEASE_EXECUTABLE} -sr
    OUTPUT_VARIABLE LSB_RELEASE_RELEASE_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

  EXECUTE_PROCESS(COMMAND ${LSB_RELEASE_EXECUTABLE} -si
    OUTPUT_VARIABLE LSB_RELEASE_NAME
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
ENDIF()

IF(${LSB_RELEASE_NAME} EQUAL "Ubuntu")
  IF(${LSB_RELEASE_RELEASE_VERSION} EQUAL "17.10")
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "pkgconf cmake, g++, libzmq5, libzmqpp4, libzmqpp-dev, protobuf-compiler, libprotobuf-dev, freeglut3, freeglut3-dev")
  ENDIF()

  IF(${LSB_RELEASE_RELEASE_VERSION} EQUAL "16.04")
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "pkgconf cmake, g++, libzmq5, libzmqpp3, libzmqpp-dev, protobuf-compiler, libprotobuf-dev, freeglut3, freeglut3-dev")
  ENDIF()

  IF(${LSB_RELEASE_RELEASE_VERSION} EQUAL "14.04")
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "pkg-config cmake, g++, libzmq3, libzmq3-dev, protobuf-compiler, libprotobuf-dev, freeglut3, freeglut3-dev")
  ENDIF()
ENDIF()
IF(${LSB_RELEASE_NAME} EQUAL "Debian")
  IF(${LSB_RELEASE_RELEASE_VERSION} EQUAL "8.2")
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "pkgconf cmake, g++, libzmq3, libzmq3-dev, protobuf-compiler, libprotobuf-dev, freeglut3, freeglut3-dev")
  ENDIF()
  IF(${LSB_RELEASE_RELEASE_VERSION} EQUAL "8.5")
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "pkgconf cmake, g++, libzmq3, libzmq3-dev, protobuf-compiler, libprotobuf-dev, freeglut3, freeglut3-dev")
  ENDIF()
ENDIF()

INCLUDE(CPack)
