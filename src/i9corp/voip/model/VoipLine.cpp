//
// Created by sobrito on 22/02/2019.
//

#include "../common/CommonBuildLibrary.h"
#include <i9corp/voip/model/VoipLine.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <pjsip/sip_config.h>
#include <i9corp/voip/tools/VoipTools.h>

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
    this->setHostname(hostname)
}

VoipLine::~VoipLine() {
    this->setUsername(nullptr);
    this->setPassword(nullptr);
    this->setHostname(nullptr)
    this->setIdUri(nullptr);
    this->setRegUri(nullptr);
    this->setStunServer(nullptr);

    this->deactivate();
}

bool VoipLine::active() {
    if (this->status != TVoipLineStatus::UNREGISTERED) {
        this->handler->onError("Line not is unregistered")
        return false;
    }
    this->status = TVoipLineStatus::REGISTERING;
    if (this->username == nullptr || this->hostname == nullptr || this->password == nullptr) {
        this->handler->onError("Username, hostname or password is null");
        return false;
    }

    this->endpoint.libCreate();
    this->endpoint.libInit(this->endpointConfig);
    this->transportConfig.port = this->port;


    this->endpointConfig.uaConfig.userAgent = "I9Corp Mamute 1.0.0";

    try {
        this->endpointConfig.transportCreate(PJSIP_TRANSPORT_UDP, this->tcfg);
        this->endpointConfig.transportCreate(PJSIP_TRANSPORT_TCP, this->tcfg);
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
    sRegUri << "sip:" << this->hostname
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
    VoipAccount *a = new VoipAccount(this->number, this->handler);
    a->create(this->accountConfig);
    if (this->account != nullptr) {
        delete this->account;
    }
    this->account = a;
    return true;
}

bool VoipLine::deactivate() {
    this->status = TVoipLineStatus::UNREGISTERING;
    if (this->account != nullptr) {
        delete this->account;
        this->account = nullptr;
    }
    pj_thread_sleep(4000);
    this->endpoint.hangupAllCalls();
    pj_thread_sleep(4000);
    this->endpoint.libDestroy();
    this->status = TVoipLineStatus::UNREGISTERED;
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
    this->status = TVoipLineStatus::UNREGISTERED;
}

char *VoipLine::getUsername() const {
    return username;
}

void VoipLine::setUsername(char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->username != nullptr) {
        this->username = mValue;
    }
    this->username = mValue;
}

char *VoipLine::getPassword() const {
    return password;
}

void VoipLine::setPassword(char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->password != nullptr) {
        this->password = mValue;
    }
    this->password = mValue;
}

char *VoipLine::getHostname() const {
    return hostname;
}

void VoipLine::setHostname(char *value) {
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

VoipHandlerController *VoipLine::getHandler() const {
    return handler;
}

void VoipLine::setHandler(VoipHandlerController *handler) {
    VoipLine::handler = handler;
}

long VoipLine::getId() const {
    if (id == 0) {
        this->id = VoipTools::getLongId(this);
    }
    return this->id;
}

void VoipLine::dial(const char *text) {
    if (text == nullptr || strlen(text) == 0) {
        this->handler->onError("Number to dial is empty or null");
        return nullptr;
    }
}

int VoipLine::getNumber() const {
    return number;
}

void VoipLine::setNumber(int number) {
    this->number = number;
}

void VoipLine::setRegUri(char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->regUri != nullptr) {
        this->regUri = mValue;
    }
    this->regUri = mValue;
}

void VoipLine::setIdUri(char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->idUri != nullptr) {
        this->idUri = mValue;
    }
    this->idUri = mValue;
}

void VoipLine::setStunServer(char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->stunServer != nullptr) {
        this->stunServer = mValue;
    }
    this->stunServer = mValue;
}
