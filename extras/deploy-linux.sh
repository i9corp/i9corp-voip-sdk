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

${COMMAND_SUDO} ${COMMAND_COPY} -rf ${PROJECT_DIR}/dist/* /usr/

