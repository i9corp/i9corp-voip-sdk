cmake_minimum_required(VERSION 3.7)
project(i9corp-voip-sdk)
include(CheckIncludeFile)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(PJ_ARCH -i686-w64-mingw32)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(INCLUDE_DIR ${INCLUDE_DIR} ./include)
set(LIBRARY_DIR ${LIBRARY_DIR} ./lib )


SET(REQUIRED_LIBRARIES pjsua pjsua pjsip-ua pjsip-simple pjsip pjmedia-codec pjmedia pjmedia-videodev pjmedia-audiodev pjnath pjlib-util srtp resample gsmcodec ilbccodec speex g7221codec webrtc pjsdp pj)
if ((${CMAKE_SYSTEM_NAME} MATCHES "(Windows)"))
    SET(REQUIRED_LIBRARIES ${REQUIRED_LIBRARIES} winmm ole32 ws2_32 wsock32 gdi32)
endif ()
SET(REQUIRED_LIBRARIES ${REQUIRED_LIBRARIES} m ssl crypto)

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

add_library(i9corp-voip-sdk SHARED include/i9corp/voip/common/CommonExport.h src/i9corp/voip/common/CommonBuildLibrary.h src/i9corp/voip/model/VoipLine.cpp include/i9corp/voip/model/VoipLine.h include/i9corp/voip/controller/VoipHandlerController.h src/i9corp/voip/model/VoipCall.cpp include/i9corp/voip/model/VoipCall.h src/i9corp/voip/tools/VoipTools.cpp include/i9corp/voip/tools/VoipTools.h src/i9corp/voip/model/VoipAccount.cpp include/i9corp/voip/model/VoipAccount.h src/i9corp/voip/model/VoipPlayback.cpp include/i9corp/voip/model/VoipPlayback.h src/i9corp/voip/controller/VoipHandlerController.cpp include/i9corp/voip/controller/VoipRegisterStateController.h
   )
target_link_libraries(i9corp-voip-sdk ${REQUIRED_LIBRARY} )

