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
#include <pjsua2.hpp>
#include <sys/time.h>
#include <sys/types.h>
#include <winsock2.h>

using namespace i9corp;

VoipLine::VoipLine(int number, VoipHandlerController *controller) {
    if (controller == nullptr) {
        throw "Controller is null";
    }

    this->number = number;
    this->handler = controller;
    this->initialize();
    this->port = 5060;
}

void VoipLine::setStatus(TVoipLineStatus value) {
    this->status = value;
    if (this->handler == nullptr) {
        return;
    }
    this->handler->onChangeRegisterState(this->number, this->status);
}

VoipLine::VoipLine(int number, VoipHandlerController *controller, const char *username, const char *password,
                   const char *hostname, unsigned short port) {
    if (controller == nullptr) {
        throw "Controller is null";
    }
    this->handler = controller;
    this->number = number;
    this->initialize();
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

    auto ep = this->endpoint;
    // Initialize endpoint
    EpConfig endpointConfig;
    ep->libInit(endpointConfig);

    // Create SIP transport. Error handling sample is shown
    TransportConfig transportConfig;
    transportConfig.port = this->port;

    try {
        ep->transportCreate(PJSIP_TRANSPORT_UDP, transportConfig);
        // ep->transportCreate(PJSIP_TRANSPORT_TCP, transportConfig);
    } catch (Error &err) {
        this->handler->onError(err.info().c_str());
        return false;
    }

    ep->libStart();
    this->handler->onNotice("Native pjsip lib is started");

    AccountConfig accountConfig;
    endpointConfig.uaConfig.userAgent = "I9Corp Mamute 1.0.0";

    std::stringstream sIdUri;
    sIdUri << "sip:" << this->username << "@" << this->hostname;
    this->setIdUri(sIdUri.str().c_str());

    std::stringstream sRegUri;
    sRegUri << "sip:" << this->hostname;
    this->setRegUri(sRegUri.str().c_str());

    accountConfig.idUri = this->idUri;
    accountConfig.regConfig.registrarUri = this->regUri;
    accountConfig.sipConfig.proxies.push_back(this->regUri);

    AuthCredInfo cred("digest", "*", this->username, 0, this->password);
    accountConfig.sipConfig.authCreds.clear();
    accountConfig.sipConfig.authCreds.push_back(cred);

    accountConfig.callConfig.timerMinSESec = 120;
    accountConfig.callConfig.timerSessExpiresSec = 1800;
    accountConfig.regConfig.retryIntervalSec = 300;
    accountConfig.regConfig.firstRetryIntervalSec = 60;
    accountConfig.natConfig.mediaStunUse = PJSUA_STUN_USE_DISABLED;

    accountConfig.natConfig.viaRewriteUse = PJ_FALSE;
    accountConfig.natConfig.sdpNatRewriteUse = PJ_FALSE;
    accountConfig.natConfig.contactRewriteUse = PJ_FALSE;
    accountConfig.natConfig.contactRewriteMethod = PJ_FALSE;
    accountConfig.natConfig.contactUseSrcPort = PJ_FALSE;

    endpointConfig.uaConfig.stunServer.clear();
    if (this->stunServer != nullptr) {
        accountConfig.natConfig.mediaStunUse = PJSUA_STUN_USE_DEFAULT;
        endpointConfig.uaConfig.stunServer.push_back(this->stunServer);
    }
    endpointConfig.uaConfig.natTypeInSdp = 2;
    // Setup the account
    auto *a = new VoipAccount(this->number, this, this->handler);
    a->create(accountConfig);

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
    auto ep = this->endpoint;
    if (ep != nullptr) {
        ep->hangupAllCalls();
        pj_thread_sleep(4000);
        ep->libDestroy();
    }
    this->setStatus(TVoipLineStatus::UNREGISTERED);
    return true;
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
    Endpoint *ep = new Endpoint();
    try {
        ep->libCreate();
        this->endpoint = ep;
    } catch (Error &err) {
        handler->onError("Startup error: %s", err.info().c_str());
        delete ep;
        this->endpoint = nullptr;
    }
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
        this->account->setCall(call->getId(), call);
        // this->currentCall = call;
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
    VoipCall *call = this->getCurrentCall();
    if (call == nullptr) {
        handler->onError("Call not found");
        return false;
    }
    try {
        pj::CallOpParam prm;
        prm.statusCode = pjsip_status_code::PJSIP_SC_BUSY_HERE;
        call->answer(prm);
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

bool VoipLine::volume(unsigned short value) {
    if (this->currentCall == nullptr) {
        handler->onError("Current call is null");
        return false;
    }
    return this->volume(this->currentCall->getId(), value);
}

bool VoipLine::reject() {
    if (this->currentCall == nullptr) {
        handler->onError("Current call is null");
        return false;
    }
    return this->reject(this->currentCall->getId());
}

bool VoipLine::dtmf(const char *digits) {
    if (this->currentCall == nullptr) {
        handler->onError("Current call is null");
        return false;
    }
    return this->dtmf(this->currentCall->getId(), digits);
}

bool VoipLine::dtmf(char digits) {
    if (this->currentCall == nullptr) {
        handler->onError("Current call is null");
        return false;
    }
    return this->dtmf(this->currentCall->getId(), digits);
}

void VoipLine::onCreateCall(VoipCall *call) {
    this->currentCall = call;
}

void VoipLine::onRemoveCall(VoipCall *call) {
    if (this->currentCall == call) {
        this->currentCall = nullptr;
    }
}
