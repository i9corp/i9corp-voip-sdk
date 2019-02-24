cmake_minimum_required(VERSION 3.7)
project(i9corp-voip-sdk)
include(CheckIncludeFile)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(INCLUDE_DIR ${INCLUDE_DIR} ./include)
set(INCLUDE_DIR ${INCLUDE_DIR} ./third-parties/pjsip/pjlib/include)
set(INCLUDE_DIR ${INCLUDE_DIR} ./third-parties/pjsip/pjlib-util/include)
set(INCLUDE_DIR ${INCLUDE_DIR} ./third-parties/pjsip/pjnath/include)
set(INCLUDE_DIR ${INCLUDE_DIR} ./third-parties/pjsip/pjmedia/include)
set(INCLUDE_DIR ${INCLUDE_DIR} ./third-parties/pjsip/pjsip/include)

set(LIBRARY_DIR ${LIBRARY_DIR} ./lib )
set(LIBRARY_DIR ${LIBRARY_DIR} ./third-parties/pjsip/lib)

if ((${CMAKE_SYSTEM_NAME} MATCHES "(Windows)"))

    set(MINGW_BASE_DIR  "C:/MinGW")
    set(MINGW_BASE_ARCH_DIR  "${MINGW_BASE_DIR}/x86_64-w64-mingw32")

    if (EXISTS "${MINGW_BASE_ARCH_DIR}" AND EXISTS ${MINGW_BASE_ARCH_DIR}/include)
        set(INCLUDE_DIR ${INCLUDE_DIR} ${MINGW_BASE_ARCH_DIR}/include)
    endif()

    if (EXISTS "${MINGW_BASE_ARCH_DIR}" AND EXISTS ${MINGW_BASE_ARCH_DIR}/lib64)
        set(LIBRARY_DIR ${LIBRARY_DIR} ${MINGW_BASE_ARCH_DIR}/lib64)
    endif()

    if (EXISTS "${MINGW_BASE_ARCH_DIR}" AND EXISTS ${MINGW_BASE_ARCH_DIR}/lib)
        set(LIBRARY_DIR ${LIBRARY_DIR} ${MINGW_BASE_ARCH_DIR}/lib)
    endif()

    if (EXISTS "${MINGW_BASE_DIR}" AND EXISTS ${MINGW_BASE_DIR}/include)
        set(INCLUDE_DIR ${INCLUDE_DIR} ${MINGW_BASE_DIR}/include)
    endif()

    if (EXISTS "${MINGW_BASE_DIR}" AND EXISTS ${MINGW_BASE_DIR}/lib64)
        set(LIBRARY_DIR ${LIBRARY_DIR} ${MINGW_BASE_DIR}/lib64)
    endif()

    if (EXISTS "${MINGW_BASE_DIR}" AND EXISTS ${MINGW_BASE_DIR}/lib)
        set(LIBRARY_DIR ${LIBRARY_DIR} ${MINGW_BASE_DIR}/lib)
    endif()


    find_library(WSOCK32_LIBRARY wsock32)
    if(NOT WSOCK32_LIBRARY)
        message(FATAL_ERROR "wsock32 library not found")
    endif()

    find_library(WS2_32_LIBRARY ws2_32)
    if(NOT WS2_32_LIBRARY)
        message(FATAL_ERROR "ws2_32 library not found")
    endif()

    set(EXTRA_LIB ${EXTRA_LIB} wsock32)
    set(EXTRA_LIB ${EXTRA_LIB} ws2_32)
endif ()

include_directories(${INCLUDE_DIR})
link_directories(${LIBRARY_DIR})

################################################################################
# Print summary
################################################################################
message("Target OS:       ${CMAKE_SYSTEM_NAME}")
message("Resume:")
message("INCLUDE_DIR:     ${INCLUDE_DIR}")
message("LIBRARY_DIR:     ${LIBRARY_DIR}")
message("EXTRA_LIB:       ${EXTRA_LIB}")

add_subdirectory(./third-parties/pjsip)
add_library(i9corp-voip-sdk STATIC include/i9corp/voip/common/CommonExport.h src/i9corp/voip/common/CommonBuildLibrary.h src/i9corp/voip/model/VoipLine.cpp include/i9corp/voip/model/VoipLine.h include/i9corp/voip/controller/VoipHandlerController.h src/i9corp/voip/model/VoipCall.cpp include/i9corp/voip/model/VoipCall.h src/i9corp/voip/tools/VoipTools.cpp include/i9corp/voip/tools/VoipTools.h src/i9corp/voip/model/VoipAccount.cpp include/i9corp/voip/model/VoipAccount.h src/i9corp/voip/model/VoipPlayback.cpp include/i9corp/voip/model/VoipPlayback.h src/i9corp/voip/controller/VoipHandlerController.cpp include/i9corp/voip/controller/VoipRegisterStateController.h
   )

target_link_libraries(i9corp-voip-sdk pjproject ${EXTRA_LIB})

