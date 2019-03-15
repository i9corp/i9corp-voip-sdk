//
// Created by sobrito on 22/02/2019.
//
#include "../common/CommonBuildLibrary.h"
#include <i9corp/voip/model/VoipAccount.h>
#include <i9corp/voip/tools/VoipTools.h>
#include <sstream>

using namespace i9corp;

VoipAccount::VoipAccount(int line, VoipRegisterStateController *stateController,
                         VoipHandlerController *handlerController) {
    this->handler = handlerController;
    this->state = stateController;
}

VoipAccount::~VoipAccount() {

}

void VoipAccount::onIncomingCall(pj::OnIncomingCallParam &iprm) {

    VoipCall *call = new VoipCall(this->line, this->handler, *this, iprm.callId);
    pj::CallInfo ci = call->getInfo();
    pj::CallOpParam prm;

    std::stringstream ss;
    ss << "*** Incoming Call: " << ci.remoteUri << " [" << ci.stateText << "]";
    this->handler->onNotice(ss.str().c_str());


    if (this->handler->isAutoAnswer()) {
        prm.statusCode = pjsip_status_code::PJSIP_SC_OK;
    } else {
        prm.statusCode = pjsip_status_code::PJSIP_SC_RINGING;
    }

    call->answer(prm);
    long id = VoipTools::getLongId(call);
    this->setCall(id, call);

    this->handler->onIncomingRinging(this->line, id, call->getNumber(), TVoipCallDirection::INCOMING);
}


void VoipAccount::onRegState(pj::OnRegStateParam &prm) {

    pj::AccountInfo ai = getInfo();

    TVoipLineStatus s = ai.regIsActive ? TVoipLineStatus::REGISTERED : TVoipLineStatus::UNREGISTERED;
    this->state->onChangeRegisterState(s);
}

const std::map<long, VoipCall *> &VoipAccount::getCalls() const {
    return calls;
}

void VoipAccount::removeCall(long id) {
    auto it = this->calls.find(id);
    if (it == this->calls.end()) {
        return;
    }
    delete it->second;
    this->calls.erase(it);
}

void VoipAccount::setCall(long id, VoipCall *call) {

    auto it = this->calls.find(id);
    if (it != this->calls.end()) {
        return;
    }
    this->calls.insert(std::pair<long, VoipCall *>(id, call));
}

VoipCall *VoipAccount::getCall(long id) {
    auto it = this->calls.find(id);
    if (it != this->calls.end()) {
        return nullptr;
    }
    return it->second;
}
