cmake_minimum_required(VERSION 3.7)
project(i9corp-voip-sdk)
include(CheckIncludeFile)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PJSIP REQUIRED libpjproject)

set(INCLUDE_DIR ${INCLUDE_DIR} ./include)
set(LIBRARY_DIR ${LIBRARY_DIR} ./lib )

SET(REQUIRED_LIBRARIES ${PJSIP_LIBRARIES})

foreach(REQUIRED_LIBRARY ${REQUIRED_LIBRARIES})
    find_library(REQUIRED_LIBRARY_PATH NAMES ${REQUIRED_LIBRARY})
    if(NOT REQUIRED_LIBRARY_PATH)
        message(FATAL_ERROR "lib ${REQUIRED_LIBRARY} not found")
    endif()
    message ("library ${REQUIRED_LIBRARY} is found")
endforeach(REQUIRED_LIBRARY)

include_directories(${INCLUDE_DIR})
link_directories(${LIBRARY_DIR})

################################################################################
# Print summary
################################################################################
message("Target OS:                 ${CMAKE_SYSTEM_NAME}")
message("Resume:")
message("INCLUDE_DIR:               ${INCLUDE_DIR}")
message("LIBRARY_DIR:               ${LIBRARY_DIR}")
message("REQUIRED_LIBRARY:          ${REQUIRED_LIBRARIES}")

add_library(i9corp-voip-sdk SHARED
            include/i9corp/voip/common/CommonExport.h
            src/i9corp/voip/common/CommonBuildLibrary.h
            include/i9corp/voip/controller/VoipRegisterStateController.h
            include/i9corp/voip/controller/VoipHandlerController.h
            include/i9corp/voip/model/VoipLine.h
            include/i9corp/voip/model/VoipCall.h
            include/i9corp/voip/tools/VoipTools.h
            include/i9corp/voip/model/VoipAccount.h
            include/i9corp/voip/model/VoipPlayback.h

            src/i9corp/voip/controller/VoipHandlerController.cpp
            src/i9corp/voip/model/VoipLine.cpp
            src/i9corp/voip/model/VoipCall.cpp
            src/i9corp/voip/tools/VoipTools.cpp
            src/i9corp/voip/model/VoipAccount.cpp
            src/i9corp/voip/model/VoipPlayback.cpp
   )
target_link_libraries(i9corp-voip-sdk  ${REQUIRED_LIBRARIES})
target_include_directories(i9corp-voip-sdk PUBLIC ${PJSIP_INCLUDE_DIRS})
target_compile_options(i9corp-voip-sdk PUBLIC ${PJSIP_CFLAGS_OTHER})

