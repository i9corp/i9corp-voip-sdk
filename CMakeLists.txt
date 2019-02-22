cmake_minimum_required(VERSION 3.7)
project(i9corp-voip-sdk)

set(CMAKE_CXX_STANDARD 14)

include_directories(./include)

add_library(i9corp-voip-sdk SHARED include/i9corp/voip/common/CommonExport.h src/i9corp/voip/common/CommonBuildLibrary.h src/i9corp/voip/model/VoipLine.cpp include/i9corp/voip/model/VoipLine.h src/i9corp/voip/controller/VoipHandlerController.cpp include/i9corp/voip/controller/VoipHandlerController.h src/i9corp/voip/model/VoipCall.cpp include/i9corp/voip/model/VoipCall.h src/i9corp/voip/tools/VoipTools.cpp include/i9corp/voip/tools/VoipTools.h)