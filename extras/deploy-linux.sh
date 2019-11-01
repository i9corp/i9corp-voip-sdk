#!/bin/sh

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")
PROJECT_DIR=$(readlink -f $SCRIPTPATH/../)

set -e


PATH=/usr/bin:$PATH
export PATH="${PATH}"

COMMAND_SUDO="/usr/bin/sudo"
COMMAND_DATE="/bin/date"
COMMAND_RM="/bin/rm"
COMMAND_COPY="/bin/cp"
COMMAND_ECHO="/bin/echo"
COMMAND_MAKE="/usr/bin/make"
COMMAND_CMAKE="/usr/bin/cmake"

echo "${PROJECT_DIR}"

cd ${PROJECT_DIR}
${COMMAND_CMAKE} -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_SH=CMAKE_SH-NOTFOUND 
${COMMAND_MAKE}
${COMMAND_MAKE} install


STAGE_DIR=/tmp/i9corp-voip-debian
SCRIPT=$(readlink -f "$0")
SCRIPT_PATH=$(dirname "$SCRIPT")
DIST_DIR=${PROJECT_DIR}/dist
BUILD_DIR=${STAGE_DIR}/build
BASE_DIR=${STAGE_DIR}/usr
ARCH="$(/usr/bin/dpkg --print-architecture)"
set -e

echo "Starting..."
echo "Arch: ${ARCH}"
echo "Directory (dist): ${DIST_DIR}"
echo "Directory (base): ${BASE_DIR}"
echo "Directory (build): ${BUILD_DIR}"
echo "Directory (stage): ${STAGE_DIR}"

${COMMAND_SUDO} ${COMMAND_RM} -rf ${STAGE_DIR}
mkdir -p ${STAGE_DIR}/DEBIAN
mkdir -p ${BASE_DIR}

echo "Creating package structure..."

cat >> ${STAGE_DIR}/DEBIAN/control <<EOF
Package: i9corp-voip
Priority: extra
Section: net
Maintainer: I9CORP <repo@i9corp.com.br>
Version: @VERSION@
Depends: libpjproject-dev
Description: I9Corp Biblioteca para Voip
EOF

echo "Architecture: ${ARCH}" >> ${STAGE_DIR}/DEBIAN/control


${COMMAND_SUDO} ${COMMAND_COPY} -rf ${PROJECT_DIR}/dist/* ${BASE_DIR}/

chmod 755 ${STAGE_DIR}/DEBIAN/control

echo "Creating package..."
dpkg -b ${STAGE_DIR} ${DIST_DIR}/i9corp-voip_@VERSION@_${ARCH}.deb
echo "Done!";

