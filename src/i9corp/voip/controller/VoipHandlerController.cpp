//
// Created by sobrito on 23/02/2019.
//
#include "../common/CommonBuildLibrary.h"
#include <i9corp/voip/controller/VoipHandlerController.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <csignal>
#include <sstream>
#include <unistd.h>
#include <string.h>

using namespace i9corp;

VoipHandlerController::VoipHandlerController() {

}

VoipHandlerController::~VoipHandlerController() {

}

void VoipHandlerController::onError(const char *message, ...) {
    std::stringstream ss;
    va_list list;
    va_start(list, message);

    vfprintf(stderr, ss.str().c_str(), list);
    va_end(list);
}

void VoipHandlerController::onNotice(const char *message, ...) {
    std::stringstream ss;
    va_list list;
    va_start(list, message);
    vfprintf(stdout, ss.str().c_str(), list);
    va_end(list);
}

TVoipCallDirection VoipHandlerController::getDirection(const char *number) {
    if (number == nullptr || strlen(number)) {
        return EXTERNAL;
    }
    if (strlen(number) <= 4) {
        return INTERNAL;
    }
    return EXTERNAL;

}
