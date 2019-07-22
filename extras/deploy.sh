#!/bin/sh

SCRIPT=$(readlink -f "$0")
SCRIPT_PATH=$(dirname "$SCRIPT")
SOURCE_DIR=$(readlink -f ${SCRIPT_PATH}/../)
STAGE_DIR=$(mktemp -d)

source "/etc/profile"

MINGW_HOME="C:/msys64/mingw64"
MINGW_BIN="${MINGW_HOME}/bin"
MINGW_LIBRARY="${MINGW_HOME}/lib"
MINGW_INCLUDE="${MINGW_HOME}/include"
COMMAND_CMAKE="${MINGW_BIN}/cmake.exe"
C_COMPILER="${MINGW_BIN}/gcc"
CPP_COMPILER="${MINGW_BIN}/g++"
COMMAND_MAKE="${MINGW_BIN}/mingw32-make.exe"
BUILD_OUTPUT_DIR="${PROJECT_DIR}\cmake-build"
COMMAND_COPY="/usr/bin/cp.exe"
COMMAND_TAR="/usr/bin/tar.exe"
COMMAND_MAKE_PKG="/usr/bin/makepkg"

function build(){
    cd ${SOURCE_DIR}
    ${COMMAND_CMAKE} . -G "CodeBlocks - MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release  -DCMAKE_PREFIX_PATH=${MINGW_HOME} -DCMAKE_SH=CMAKE_SH-NOTFOUND -B${BUILD_OUTPUT_DIR}

    cd "${BUILD_OUTPUT_DIR}"
    ${COMMAND_MAKE}
    ${COMMAND_MAKE} install
}

function dist() {
    cd "${SOURCE_DIR}/dist"
    ${COMMAND_TAR} -czvf ${STAGE_DIR}/i9corp-voip.tar.gz . --transform='s/\./usr/'
    ${COMMAND_COPY} -fr ${STAGE_DIR}/i9corp-voip.tar.gz ${SCRIPT_PATH}

    cd "${SCRIPT_PATH}"
    ${COMMAND_MAKE_PKG} -g >> PKGBUILD && ${COMMAND_MAKE_PKG}
}

function main() {
    build
    dist
}

main