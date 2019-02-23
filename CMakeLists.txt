cmake_minimum_required(VERSION 3.7)
project(i9corp-voip-sdk)
include(CheckIncludeFile)

set(CMAKE_CXX_STANDARD 14)

include_directories(./include)

include_directories(./third-parties/pjsip/pjlib/include)
include_directories(./third-parties/pjsip/pjlib-util/include)
include_directories(./third-parties/pjsip/pjnath/include)
include_directories(./third-parties/pjsip/pjmedia/include)
include_directories(./third-parties/pjsip/pjsip/include)

add_subdirectory(./third-parties/pjsip)

add_library(i9corp-voip-sdk SHARED include/i9corp/voip/common/CommonExport.h src/i9corp/voip/common/CommonBuildLibrary.h src/i9corp/voip/model/VoipLine.cpp include/i9corp/voip/model/VoipLine.h include/i9corp/voip/controller/VoipHandlerController.h src/i9corp/voip/model/VoipCall.cpp include/i9corp/voip/model/VoipCall.h src/i9corp/voip/tools/VoipTools.cpp include/i9corp/voip/tools/VoipTools.h src/i9corp/voip/model/VoipAccount.cpp include/i9corp/voip/model/VoipAccount.h src/i9corp/voip/model/VoipPlayback.cpp include/i9corp/voip/model/VoipPlayback.h src/i9corp/voip/controller/VoipHandlerController.cpp include/i9corp/voip/controller/VoipRegisterStateController.h)

target_link_libraries(i9corp-voip-sdk m)