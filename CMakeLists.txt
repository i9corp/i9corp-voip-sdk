cmake_minimum_required(VERSION 3.7)
project(i9corp-voip-sdk)
include(CheckIncludeFile)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_POSITION_INDEPENDENT_CODE ON)
include_directories(./include)
set(PJSIP_BASE_DIR ./third-parties/pjsip)
# Copiando o arquivo com as configurações personalizadas do pjsip
file(COPY ./include/i9corp/voip/common/config_site.h DESTINATION ${PJSIP_DIR}/source/pjlib/include/pj)

# Incluindo os headers das bibliotecas usadas pela aplicação
set(PJSIP_SUBDIRECTORIES pjlib pjlib-util pjnath pjmedia pjsip)
foreach(SUBDIRECTORY ${PJSIP_SUBDIRECTORIES})
    include_directories(${PJSIP_BASE_DIR}/${SUBDIRECTORY}/include/)
endforeach()

# Adicionado diretório de onde será disponibilizado as lib geradas pelo projeto para ser efetuada a linkagem
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(PJSIP_LIB_SUFIX "-i686-pc-mingw32")
set(PJSIP_DEPS pjsua2 pjsua pjsip-ua pjsip-simple pjsip pjmedia-codec pjmedia pjmedia-videodev pjmedia-audiodev pjnath pjlib-util srtp resample gsmcodec ilbccodec speex g7221codec webrtc pjsdp pj)
foreach(DEP ${PJSIP_DEPS})
    # find_library(PSJIP_LIBRARY_DEP ${DEP}${PJSIP_LIB_SUFIX})
    # if(NOT PSJIP_LIBRARY_DEP)
     #   message(FATAL_ERROR "${DEP} library not found")
    # endif()
    set(EXTRA_LIB ${EXTRA_LIB} ${DEP}${PJSIP_LIB_SUFIX})
endforeach()

# Adicionando bibliotecas do windows para socket e rede
if ((${CMAKE_SYSTEM_NAME} MATCHES "(Windows)"))
    set(WIN32_DEPS m winmm ole32 wsock32 ws2_32 pthread gdi32 crypt32)
    foreach(WIN32_DEP ${WIN32_DEPS})
         find_library(WIN32_LIBRARY_DEP ${WIN32_DEP})
         if(NOT WIN32_LIBRARY_DEP)
           message(FATAL_ERROR "${WIN32_DEP} library not found")
         endif()
          set(EXTRA_LIB ${EXTRA_LIB} ${WIN32_DEP})
    endforeach()
endif ()


# Adicionado projeto do cmake do pjsip ao projeto principal com o objetivo de compilar o pjproject para que o mesmo seja
# incorporado ao projeto principal "i9corp-voip-sdk"

# add_subdirectory(./third-parties/pjsip)

# Comando para a criação de uma biblioteca dinâmica com o código fonte produzido
add_library(i9corp-voip-sdk SHARED include/i9corp/voip/common/CommonExport.h src/i9corp/voip/common/CommonBuildLibrary.h src/i9corp/voip/model/VoipLine.cpp include/i9corp/voip/model/VoipLine.h include/i9corp/voip/controller/VoipHandlerController.h src/i9corp/voip/model/VoipCall.cpp include/i9corp/voip/model/VoipCall.h src/i9corp/voip/tools/VoipTools.cpp include/i9corp/voip/tools/VoipTools.h src/i9corp/voip/model/VoipAccount.cpp include/i9corp/voip/model/VoipAccount.h src/i9corp/voip/model/VoipPlayback.cpp include/i9corp/voip/model/VoipPlayback.h src/i9corp/voip/controller/VoipHandlerController.cpp include/i9corp/voip/controller/VoipRegisterStateController.h
   )

# Adição de dependências ao projeto principal sendo o pjproject a biblioteca do pjsip e ${EXTRA_LIB} as demais
# bibliotecas que serão usadas pelo projeto (tanto as comuns a todos os S.O quanto as especificas)
target_link_libraries(i9corp-voip-sdk ${EXTRA_LIB} )

get_property(LIB_LINK_DIRECTORIES DIRECTORY PROPERTY LINK_DIRECTORIES)
# Resumo de variaveis do sistema
message("Target OS:             ${CMAKE_SYSTEM_NAME}") # Sistema operacional detectado
message("EXTRA_LIB:             ${EXTRA_LIB}") # Bibliotecas adicionais que serão linkadas.
message("LIB_DIR:               ${LIB_LINK_DIRECTORIES}") # Bibliotecas adicionais que serão linkadas.
