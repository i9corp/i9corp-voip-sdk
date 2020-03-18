cmake_minimum_required(VERSION 3.7)
project(i9corp-voip-sdk)
include(CheckIncludeFile)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/dist)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PJSIP REQUIRED libpjproject)

set(INCLUDE_DIR ${INCLUDE_DIR} ./include)
set(LIBRARY_DIR ${LIBRARY_DIR} ./lib)

SET(REQUIRED_LIBRARIES ${PJSIP_LIBRARIES})

foreach (REQUIRED_LIBRARY ${REQUIRED_LIBRARIES})
    find_library(REQUIRED_LIBRARY_PATH NAMES ${REQUIRED_LIBRARY})
    if (NOT REQUIRED_LIBRARY_PATH)
        message(FATAL_ERROR "lib ${REQUIRED_LIBRARY} not found")
    endif ()
    message("library ${REQUIRED_LIBRARY} is found")
endforeach (REQUIRED_LIBRARY)

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

        src/i9corp/voip/controller/VoipHandlerController.cpp
        src/i9corp/voip/model/VoipLine.cpp
        src/i9corp/voip/model/VoipCall.cpp
        src/i9corp/voip/tools/VoipTools.cpp
        src/i9corp/voip/model/VoipAccount.cpp
        include/i9corp/voip/model/IOutputDeviceAudio.h
        include/i9corp/voip/model/IInputDeviceAudio.h
        src/i9corp/voip/model/VoipDeviceAudio.cpp
        include/i9corp/voip/model/VoipDeviceAudio.h
        src/i9corp/voip/model/VoipInputAudioDevice.cpp
        include/i9corp/voip/model/VoipInputAudioDevice.h
        src/i9corp/voip/model/VoipOutputAudioDevice.cpp
        include/i9corp/voip/model/VoipOutputAudioDevice.h
        )
target_link_libraries(i9corp-voip-sdk ${REQUIRED_LIBRARIES})
target_include_directories(i9corp-voip-sdk PUBLIC ${PJSIP_INCLUDE_DIRS})
target_compile_options(i9corp-voip-sdk PUBLIC ${PJSIP_CFLAGS_OTHER})


add_executable(voip-demo bin/main.cpp)
target_link_libraries(voip-demo i9corp-voip-sdk)

add_executable(voip-device bin/device.cpp)
target_link_libraries(voip-device i9corp-voip-sdk)


set(I9CORP_BINDIR bin)
set(I9CORP_BINCOMPONENT runtime)
set(I9CORP_LIBDIR lib)
set(I9CORP_LIBCOMPONENT dev)
set(I9CORP_INCLUDEDIR)
set(I9CORP_INCLUDECOMPONENT dev)

message("Install dir: ${CMAKE_INSTALL_PREFIX}")
install(DIRECTORY include/i9corp/voip/ DESTINATION "${CMAKE_INSTALL_PREFIX}/include/i9corp/voip")
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${I9CORP_BINDIR} COMPONENT ${I9CORP_BINCOMPONENT}
        LIBRARY DESTINATION ${I9CORP_LIBDIR} COMPONENT ${I9CORP_LIBCOMPONENT}
        ARCHIVE DESTINATION ${I9CORP_LIBDIR} COMPONENT ${I9CORP_LIBCOMPONENT}
        PUBLIC_HEADER DESTINATION ${I9CORP_INCLUDEDIR} COMPONENT ${I9CORP_INCLUDECOMPONENT})

if (NOT TARGET uninstall)
    configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
            IMMEDIATE @ONLY)

    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
    # xargs rm < install_manifest.txt
endif ()
