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

const char *VoipHandlerController::getWaveRingtone(TVoipCallDirection direction, const char *phoneNumber)
{
    throw "Not implemented yet";
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

bool VoipHandlerController::onReject(int line, long callId, const char *phoneNumber, TVoipCallDirection direction)
{
    throw "Not implemented yet";
}

bool VoipHandlerController::onTransfer(int line, long callId, const char *phoneNumber, TVoipCallDirection direction)
{
    throw "Not implemented yet";
}

bool VoipHandlerController::onDial(int line, long callId, const char *phoneNumber, TVoipCallDirection direction)
{
    throw "Not implemented yet";
}

void VoipHandlerController::onIncomingRinging(int line, long callId, const char *phoneNumber, TVoipCallDirection direction)
{
    throw "Not implemented yet";
}

void VoipHandlerController::onOutgoingRinging(int line, long callId, const char *phoneNumber, TVoipCallDirection direction)
{
    throw "Not implemented yet";
}

void VoipHandlerController::onAnswer(int line, long callId, const char *phoneNumber)
{
    throw "Not implemented yet";
}

void VoipHandlerController::onChangeRegisterState(int line, TVoipLineStatus status)
{
    throw "Not implemented yet";
}

void VoipHandlerController::onHangup(int line, int callId)
{
    throw "Not implemented yet";
}

void VoipHandlerController::onInMute(int line, int callId, bool value)
{
    throw "Not implemented yet";
}

void VoipHandlerController::onInHold(int line, int callId, bool value)
{
    throw "Not implemented yet";
}

void VoipHandlerController::onChangeVolume(int line, int volume)
{
    throw "Not implemented yet";
}
