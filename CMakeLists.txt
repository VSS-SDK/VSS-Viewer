PROJECT(vss-viewer)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++17 -o2")

find_package(PkgConfig)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
FIND_PACKAGE(Boost 1.40 COMPONENTS program_options REQUIRED)
INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} src src/Cameras src/Communications src/Domain src/Drawers src/Drawers/FieldDrawers src/Drawers/DebugDrawers src/Drawers/RobotDrawers src/Drawers/BallDrawers rc/Factories src/Framework src/Factories src/Core)

file(GLOB_RECURSE SRC src/*.cpp)

set (VSS_INTERFACE libvss-interface.so)
link_directories(usr/lib)
include_directories(usr/local/include)

ADD_EXECUTABLE(vss-viewer ${SRC})

TARGET_LINK_LIBRARIES(vss-viewer ${VSS_INTERFACE} ${PROTOBUF_LIBRARY} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
TARGET_LINK_LIBRARIES(vss-viewer LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries(vss-viewer ${PROTOBUF_LIBRARIES})

INSTALL(TARGETS vss-viewer DESTINATION bin)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_NAME "vss-viewer")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "A 3D Software of visualization of states given by VSS-Simulator and VSS-Vision")
SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://sirlab.github.io/VSS-SDK/")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Johnathan Fercher")
SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

INCLUDE(CPack)
