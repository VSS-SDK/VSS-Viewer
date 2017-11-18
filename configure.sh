#!/bin/bash
#
# This file is part of the VSS-SDK project.
#
# This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
# v. 3.0. If a copy of the GPL was not distributed with this
# file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
#

DISTRO=`lsb_release -si`
RELEASE=`lsb_release -sr`
ARCHITECTURE=`uname -m`

INSTALLED=0

INSTALL_UBUNTU_14_04 () {
  sudo apt-get update && apt-get upgrade
  sudo apt-get install pkg-config
  sudo apt-get install g++ cmake libzmq3 libzmq3-dev protobuf-compiler libprotobuf-dev libboost-all-dev freeglut3 freeglut3-dev
  INSTALLED=1
}

INSTALL_UBUNTU_16_04 () {
  sudo apt-get update && apt-get upgrade
  sudo apt-get install pkg-config
  sudo apt-get install g++ cmake libxmu-dev libxi-dev libzmqpp3 libzmqpp-dev protobuf-compiler libprotobuf-dev libboost-all-dev freeglut3 freeglut3-dev
  INSTALLED=1
}

INSTALL_UBUNTU_17_10 () {
  sudo apt-get update && apt-get upgrade
  sudo apt-get install pkg-config
  sudo apt-get install g++ cmake libzmq5 libzmqpp4 libzmqpp-dev protobuf-compiler libprotobuf-dev libboost-all-dev freeglut3 freeglut3-dev
  INSTALLED=1
}

INSTALL_DEBIAN_8_2 () {
  sudo apt-get update && apt-get upgrade
  sudo apt-get install pkgconf
  sudo apt-get install g++ cmake libzmq3 libzmq3-dev protobuf-compiler libprotobuf-dev libboost-all-dev freeglut3 freeglut3-dev
  INSTALLED=1
}

INSTALL_DEBIAN_8_5 () {
  sudo apt-get update && apt-get upgrade
  sudo apt-get install pkgconf
  sudo apt-get install g++ cmake libzmq3 libzmq3-dev protobuf-compiler libprotobuf-dev libboost-all-dev freeglut3 freeglut3-dev
  INSTALLED=1
}

INSTALL () {
  # Ubuntu
  if [[ "$DISTRO" == "Ubuntu" ]] && [[ "$RELEASE" == "17.10" ]]; then
    INSTALL_UBUNTU_17_10;
  fi
  if [[ "$DISTRO" == "Ubuntu" ]] && [[ "$RELEASE" == "16.04" ]]; then
    INSTALL_UBUNTU_16_04;
  fi
  if [[ "$DISTRO" == "Ubuntu" ]] && [[ "$RELEASE" == "14.04" ]]; then
    INSTALL_UBUNTU_14_04;
  fi

  # Debian
  if [[ "$DISTRO" == "Debian" ]] && [[ "$RELEASE" == "8.5" ]]; then
    INSTALL_DEBIAN_8_5;
  fi
  if [[ "$DISTRO" == "Debian" ]] && [[ "$RELEASE" == "8.2" ]]; then
    INSTALL_DEBIAN_8_2;
  fi
}

CMAKE () {
  sudo rm -R build
  mkdir build
  cd build
  cmake ..
  make package
  sudo dpkg -i vss-viewer-0.1.1-Linux.deb
  cd ..
}

INSTALL;

if [ $INSTALLED == 1 ]; then
  CMAKE;
fi
