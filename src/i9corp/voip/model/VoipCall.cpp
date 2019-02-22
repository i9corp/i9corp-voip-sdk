//
// Created by sobrito on 22/02/2019.
//
#include "../common/CommonBuildLibrary.h"
#include <i9corp/voip/model/VoipCall.h>
#include <i9corp/voip/tools/VoipTools.h>
#include <pjsua2.hpp>

using namespace i9corp;


VoipCall::VoipCall(VoipHandlerController *controller, VoipAccount &account, int callId) : pj::Call(account, callId) {
    this->handler = controller;
}


void VoipCall::mute(bool value) {

}

void VoipCall::hold(bool value) {

}


char *VoipCall::getNumber() const {
    if (this->number == nullptr) {
        pj::CallInfo ci = getInfo();
        this->number = VoipTools::getPhoneNumberFromUri(ci.remoteUri.c_str());
    }
    return number;
}


