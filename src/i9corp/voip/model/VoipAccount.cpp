//
// Created by sobrito on 22/02/2019.
//

#include <i9corp/voip/model/VoipAccount.h>
#include <i9corp/voip/tools/VoipTools.h>
#include <sstream>

using namespace i9corp;

VoipAccount::VoipAccount(int line, VoipHandlerController *controller) {
    this->handler = controller;
}

VoipAccount::~VoipAccount() {

}

void VoipAccount::onIncomingCall(pj::OnIncomingCallParam &iprm) {

    VoipCall *call = new VoipCall(this->handler, *this, iprm.callId);
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

void VoipAccount::onRegStarted(pj::OnRegStartedParam &prm) {
    Account::onRegStarted(prm);
}

void VoipAccount::onRegState(pj::OnRegStateParam &prm) {
    Account::onRegState(prm);
}

void VoipAccount::onIncomingSubscribe(pj::OnIncomingSubscribeParam &prm) {
    Account::onIncomingSubscribe(prm);
}

void VoipAccount::onInstantMessage(pj::OnInstantMessageParam &prm) {
    Account::onInstantMessage(prm);
}

void VoipAccount::onInstantMessageStatus(pj::OnInstantMessageStatusParam &prm) {
    Account::onInstantMessageStatus(prm);
}

void VoipAccount::onTypingIndication(pj::OnTypingIndicationParam &prm) {
    Account::onTypingIndication(prm);
}

void VoipAccount::onMwiInfo(pj::OnMwiInfoParam &prm) {
    Account::onMwiInfo(prm);
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
