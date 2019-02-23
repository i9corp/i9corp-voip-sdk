//
// Created by sobrito on 22/02/2019.
//

#include "../common/CommonBuildLibrary.h"
#include <i9corp/voip/tools/VoipTools.h>
#include <i9corp/voip/model/VoipLine.h>
#include <pjsip/sip_config.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sstream>

using namespace i9corp;

VoipLine::VoipLine(int number, VoipHandlerController *controller) {
    if (controller == nullptr) {
        throw "Controller is null";
    }

    this->initialize();
    this->number = number;
    this->handler = controller;
    this->port = 5060;
}

void VoipLine::setStatus(TVoipLineStatus value) {
    this->status = value;
    this->handler->onChangeRegisterState(this->number, this->status);
}

VoipLine::VoipLine(int number, VoipHandlerController *controller, const char *username, const char *password,
                   const char *hostname, unsigned short port) {
    if (controller == nullptr) {
        throw "Controller is null";
    }

    this->initialize();
    this->number = number;
    this->handler = controller;
    this->port = port;
    this->setUsername(username);
    this->setPassword(password);
    this->setHostname(hostname);
}

VoipLine::~VoipLine() {
    this->setUsername(nullptr);
    this->setPassword(nullptr);
    this->setHostname(nullptr);
    this->setIdUri(nullptr);
    this->setRegUri(nullptr);
    this->setStunServer(nullptr);

    this->deactivate();
}

bool VoipLine::active() {
    if (this->status != TVoipLineStatus::UNREGISTERED) {
        this->handler->onError("Line not is unregistered");
        return false;
    }
    this->setStatus(TVoipLineStatus::REGISTERING);

    if (this->username == nullptr || this->hostname == nullptr || this->password == nullptr) {
        this->handler->onError("Username, hostname or password is null");
        return false;
    }

    this->endpoint.libCreate();
    this->endpoint.libInit(this->endpointConfig);
    this->transportConfig.port = this->port;


    this->endpointConfig.uaConfig.userAgent = "I9Corp Mamute 1.0.0";

    try {
        this->endpoint.transportCreate(PJSIP_TRANSPORT_UDP, this->transportConfig);
        this->endpoint.transportCreate(PJSIP_TRANSPORT_TCP, this->transportConfig);
    } catch (pj::Error &err) {
        this->handler->onError(err.info().c_str());
        return false;
    }

    this->endpoint.libStart();
    this->handler->onNotice("Native pjsip lib is started");

    std::stringstream sIdUri;
    sIdUri << "sip:" << this->username << "@" << this->hostname;
    this->setIdUri(sIdUri.str().c_str());

    std::stringstream sRegUri;
    sRegUri << "sip:" << this->hostname;
    this->setRegUri(sRegUri.str().c_str());

    this->accountConfig.idUri = this->idUri;
    this->accountConfig.regConfig.registrarUri = this->regUri;

    this->accountConfig.sipConfig.proxies.clear();
    this->accountConfig.sipConfig.proxies.push_back(this->regUri);

    this->accountConfig.sipConfig.authCreds.clear();
    this->accountConfig.sipConfig.authCreds.push_back(
            pj::AuthCredInfo("digest", "*", this->username, 0, this->password)
    );

    this->accountConfig.callConfig.timerMinSESec = 120;
    this->accountConfig.callConfig.timerSessExpiresSec = 1800;
    this->accountConfig.regConfig.retryIntervalSec = 300;
    this->accountConfig.regConfig.firstRetryIntervalSec = 60;
    this->accountConfig.natConfig.mediaStunUse = PJSUA_STUN_USE_DISABLED;

    // pjsip_cfg()->endpt.disable_rport = PJ_FALSE;
    // pjsip_cfg()->endpt.disable_tcp_switch = PJ_TRUE;
    // pjsip_cfg()->endpt.allow_port_in_fromto_hdr = PJ_TRUE;
    // pjsip_cfg()->endpt.use_compact_form = PJ_FALSE;

    this->accountConfig.natConfig.viaRewriteUse = false;
    this->accountConfig.natConfig.sdpNatRewriteUse = PJ_FALSE;

    this->endpointConfig.uaConfig.stunServer.clear();
    if (this->stunServer != nullptr) {
        this->accountConfig.natConfig.mediaStunUse = PJSUA_STUN_USE_DEFAULT;
        this->endpointConfig.uaConfig.stunServer.push_back(this->stunServer);
    }
    this->endpointConfig.uaConfig.natTypeInSdp = 2;
    // Setup the account
    auto *a = new VoipAccount(this->number, this, this->handler);
    a->create(this->accountConfig);

    if (this->account != nullptr) {
        delete this->account;
    }

    this->account = a;
    return true;
}

bool VoipLine::deactivate() {
    this->setStatus(TVoipLineStatus::UNREGISTERING);
    if (this->account != nullptr) {
        delete this->account;
        this->account = nullptr;
    }
    pj_thread_sleep(4000);
    this->endpoint.hangupAllCalls();
    pj_thread_sleep(4000);
    this->endpoint.libDestroy();
    this->setStatus(TVoipLineStatus::UNREGISTERED);
}

void VoipLine::initialize() {
    this->username = nullptr;
    this->password = nullptr;
    this->hostname = nullptr;
    this->currentCall = nullptr;
    this->regUri = nullptr;
    this->idUri = nullptr;
    this->stunServer = nullptr;
    this->currentCall = nullptr;
    this->registered = false;
    this->account = nullptr;
    this->id = 0;
    this->setStatus(TVoipLineStatus::UNREGISTERED);
}

char *VoipLine::getUsername() const {
    return username;
}

void VoipLine::setUsername(const char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->username != nullptr) {
        this->username = mValue;
    }
    this->username = mValue;
}

char *VoipLine::getPassword() const {
    return password;
}

void VoipLine::setPassword(const char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->password != nullptr) {
        this->password = mValue;
    }
    this->password = mValue;
}

char *VoipLine::getHostname() const {
    return hostname;
}

void VoipLine::setHostname(const char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->hostname != nullptr) {
        this->hostname = mValue;
    }
    this->hostname = mValue;
}

unsigned short VoipLine::getPort() const {
    return port;
}

void VoipLine::setPort(unsigned short port) {
    VoipLine::port = port;
}


long VoipLine::getId() {
    if (id == 0) {
        this->id = VoipTools::getLongId(this);
    }
    return this->id;
}

bool VoipLine::dial(const char *digits) {
    if (digits == nullptr || strlen(digits) == 0) {
        this->handler->onError("Number to dial is empty or null");
        return false;
    }
    if (this->account == nullptr) {
        this->handler->onError("Account is null");
        return false;
    }

    char *sipNumber = this->toSipNumber(digits);
    if (sipNumber == nullptr) {
        this->handler->onError("Failure on convert sip number");
        return false;
    }

    auto call = new VoipCall(this->number, this->handler, *this->account);
    this->account->setCall(call->getId(), call);

    std::stringstream ss;
    ss << sipNumber;
    free(sipNumber);

    try {
        pj::CallOpParam prm(true);
        prm.opt.audioCount = 1;
        prm.opt.videoCount = 0;
        call->makeCall(ss.str(), prm);
        this->currentCall = call;
        TVoipCallDirection d = handler->getDirection(call->getNumber());
        this->handler->onDial(this->number, call->getId(), call->getNumber(), d);
        return true;
    } catch (pj::Error &e) {
        handler->onError(e.info(false).c_str());
        this->account->removeCall(call->getId());
        return false;
    }
}

int VoipLine::getNumber() const {
    return number;
}

void VoipLine::setNumber(int number) {
    this->number = number;
}

void VoipLine::setRegUri(const char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->regUri != nullptr) {
        this->regUri = mValue;
    }
    this->regUri = mValue;
}

void VoipLine::setIdUri(const char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->idUri != nullptr) {
        this->idUri = mValue;
    }
    this->idUri = mValue;
}

void VoipLine::setStunServer(const char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->stunServer != nullptr) {
        this->stunServer = mValue;
    }
    this->stunServer = mValue;
}

bool VoipLine::dtmf(long callId, const char *digits) {
    if (this->account == nullptr) {
        return false;
    }
    auto call = this->account->getCall(callId);
    if (call == nullptr) {
        return false;
    }
    std::stringstream ss;
    ss << digits;
    try {
        call->dialDtmf(ss.str());
        return true;
    } catch (pj::Error &e) {
        handler->onError(e.info(false).c_str());
        return false;
    }
}

bool VoipLine::dtmf(long callId, char digits) {
    std::stringstream ss;
    ss << digits;
    return this->dtmf(callId, ss.str().c_str());
}

VoipCall *VoipLine::getCurrentCall() {
    return this->currentCall;
}

char *VoipLine::toSipNumber(const char *number) {
    if (number == nullptr || this->hostname == nullptr) {
        handler->onError("Number or hostname is null");
        return nullptr;
    }
    std::stringstream ss;
    ss << "sip:" << number << "@" << this->hostname;
    return strdup(ss.str().c_str());
}

bool VoipLine::transfer(const char *number) {
    if (number == nullptr || this->currentCall == nullptr) {
        handler->onError("Number or current call is null");
        return false;
    }
    return this->transfer(this->currentCall->getId(), number);
}

bool VoipLine::transfer(long callId, const char *digits) {
    if (digits == nullptr) {
        handler->onError("Digits is null or empty");
        return false;
    }

    VoipCall *call = this->account->getCall(callId);
    if (call == nullptr) {
        handler->onError("Call not found");
        return false;
    }

    char *sipNumber = this->toSipNumber(digits);
    if (sipNumber == nullptr) {
        handler->onError("Failure on parser digits to sip");
        return false;
    }

    std::stringstream ss;
    ss << sipNumber;
    free(sipNumber);

    try {
        pj::CallOpParam prm;
        call->xfer(ss.str(), prm);
        TVoipCallDirection d = handler->getDirection(call->getNumber());
        this->handler->onTransfer(this->number, call->getId(), call->getNumber(), d);
        return true;
    } catch (pj::Error &e) {
        handler->onError(e.info(false).c_str());
        return false;
    }
}

bool VoipLine::reject(long callId) {
    VoipCall *call = this->account->getCall(callId);
    if (call == nullptr) {
        handler->onError("Call not found");
        return false;
    }

    try {
        pj::CallOpParam prm;
        prm.statusCode = pjsip_status_code::PJSIP_SC_BUSY_HERE;
        TVoipCallDirection d = handler->getDirection(call->getNumber());
        this->handler->onReject(this->number, call->getId(), call->getNumber(), d);
        call->hangup(prm);
    } catch (pj::Error &e) {
        handler->onError(e.info(false).c_str());
    }
    this->account->removeCall(callId);
    return true;
}

bool VoipLine::hangup() {
    if (this->currentCall == nullptr) {
        this->handler->onError("Current call is null");
        return false;
    }

    return this->hangup(this->currentCall->getId());
}

bool VoipLine::hangup(long callId) {
    VoipCall *call = this->account->getCall(callId);
    if (call == nullptr) {
        handler->onError("Call not found");
        return false;
    }
    try {
        pj::CallOpParam prm;
        prm.statusCode = pjsip_status_code::PJSIP_SC_ACCEPTED;
        call->hangup(prm);
        this->account->removeCall(callId);
        return true;
    } catch (pj::Error &e) {
        handler->onError(e.info(false).c_str());
        return false;
    }
}

bool VoipLine::answer(long callId) {
    VoipCall *call = this->account->getCall(callId);
    if (call == nullptr) {
        handler->onError("Call not found");
        return false;
    }

    pj::CallInfo ci = call->getInfo();
    if (ci.lastStatusCode != PJSIP_SC_RINGING) {
        handler->onError("Call not is ringing");
        return false;
    }

    try {
        pj::CallOpParam prm;
        prm.statusCode = pjsip_status_code::PJSIP_SC_OK;
        call->answer(prm);
        return true;
    } catch (pj::Error &e) {
        handler->onError(e.info(false).c_str());
        return false;
    }
}

bool VoipLine::answer() {
    if (this->currentCall == nullptr) {
        handler->onError("Current call is null");
        return false;
    }
    return this->answer(this->currentCall->getId());
}

bool VoipLine::mute(bool value) {
    if (this->currentCall == nullptr) {
        handler->onError("Current call is null");
        return false;
    }
    return this->mute(this->currentCall->getId(), value);
}

bool VoipLine::mute(long callId, bool value) {
    VoipCall *call = this->account->getCall(callId);
    if (call == nullptr) {
        handler->onError("Call not found");
        return false;
    }
    return call->mute(value);
}

bool VoipLine::hold(bool value) {
    if (this->currentCall == nullptr) {
        handler->onError("Current call is null");
        return false;
    }
    return this->hold(this->currentCall->getId(), value);
}

bool VoipLine::hold(long callId, bool value) {
    VoipCall *call = this->account->getCall(callId);
    if (call == nullptr) {
        handler->onError("Call not found");
        return false;
    }
    return call->hold(value);
}

bool VoipLine::volume(long callId, unsigned short value) {
    VoipCall *call = this->account->getCall(callId);
    if (call == nullptr) {
        handler->onError("Call not found");
        return false;
    }
    return call->volume(value);

}

void VoipLine::onChangeRegisterState(TVoipLineStatus status) {
    this->setStatus(status);
}
