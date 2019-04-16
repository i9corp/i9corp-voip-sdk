//
// Created by sobrito on 22/02/2019.
//
#include "../common/CommonBuildLibrary.h"
#include <i9corp/voip/model/VoipCall.h>
#include <i9corp/voip/tools/VoipTools.h>
#include <pjsua2.hpp>

using namespace i9corp;


VoipCall::VoipCall(int line, VoipHandlerController *controller, pj::Account &account, int callId) : pj::Call(account,
                                                                                                             callId) {
    this->handler = controller;
    this->inHold = false;
    this->muted = false;
    this->line = line;
    this->number = nullptr;
}


const char *VoipCall::getNumber() {
    if (this->number == nullptr) {
        pj::CallInfo ci = getInfo();
        this->setNumber(VoipTools::getPhoneNumberFromUri(ci.remoteUri.c_str()));
    }
    return number;
}

bool VoipCall::hold(bool value) {
    this->inHold = value;
    pj::CallOpParam prm = new pj::CallOpParam(true);
    try {
        if (this->inHold) {
            this->setHold(prm);
        } else {
            prm.opt.flag = 1;
            this->reinvite(prm);
        }
        this->handler->onInHold(this->line, this->getId(), value);
        return true;
    } catch (pj::Error &e) {
        return false;
    }
}

bool VoipCall::mute(bool value) {
    this->muted = value;
    pj::CallInfo ci = this->getInfo();
    for (unsigned i = 0; i < ci.media.size(); i++) {
        if (ci.media[i].type != PJMEDIA_TYPE_AUDIO || !this->getMedia(i)) {
            continue;
        }
        auto aud_med = dynamic_cast<pj::AudioMedia *>(getMedia(i));
        try {
            pj::AudDevManager &mgr = pj::Endpoint::instance().audDevManager();
            if (this->muted) {
                mgr.getCaptureDevMedia().stopTransmit(*aud_med);
            } else {
                mgr.getCaptureDevMedia().startTransmit(*aud_med);
            }
            this->handler->onInMute(this->line, this->getId(), value);
            return true;
        } catch (pj::Error &e) {
            this->handler->onError(e.info(false).c_str());
            return false;
        }
    }
    return false;
}

bool VoipCall::volume(unsigned short value) {
    int mValue;
    mValue = value > 100 ? 100 : value;
    mValue = mValue < 0 ? 0 : mValue;

    float rValue = mValue * 2 / 100;
    pjsua_conf_adjust_rx_level(0, rValue);

    this->handler->onChangeVolume(this->line, mValue);
    return true;
}

bool VoipCall::isMuted() const {
    return muted;
}

bool VoipCall::isInHold() const {
    return inHold;
}


void VoipCall::onCallState(pj::OnCallStateParam &prm) {
    TVoipCallDirection d;
    pj::CallInfo ci = getInfo();
    switch (ci.state) {
        case PJSIP_INV_STATE_DISCONNECTED:
            this->handler->onHangup(this->line, this->getId());
            break;
        case PJSIP_INV_STATE_CONNECTING:
        case PJSIP_INV_STATE_CALLING:
            this->handler->onOutgoingRinging(this->line, this->getId(), this->getNumber(),
                                             TVoipCallDirection::OUTGOING);
            break;
        case PJSIP_INV_STATE_CONFIRMED:
            this->handler->onAnswer(this->line, this->getId(), this->getNumber());
            break;
        case PJSIP_INV_STATE_INCOMING:
            d = this->handler->getDirection(this->getNumber());
            this->handler->onIncomingRinging(this->line, this->getId(), this->getNumber(), d);
            break;
        case PJSIP_INV_STATE_EARLY:
            if (ci.lastStatusCode != PJSIP_SC_RINGING) {
                this->handler->onRingStop(this->line, this->getId(), this->getNumber(), d);
            } else if (ci.role == PJSIP_ROLE_UAC) {
                this->handler->onIncomingRinging(this->line, this->getId(), this->getNumber(), d);
            } else if (ci.role == PJSIP_ROLE_UAS) {
                d = this->handler->getDirection(this->getNumber());
                this->handler->onIncomingRinging(this->line, this->getId(), this->getNumber(), d);
            }
            break;
    }
    Call::onCallState(prm);
}

void VoipCall::onCallMediaState(pj::OnCallMediaStateParam &prm) {
    pj::CallInfo ci = getInfo();
    for (unsigned i = 0; i < ci.media.size(); i++) {
        if (ci.media[i].type != PJMEDIA_TYPE_AUDIO || !getMedia(i)) {
            continue;
        }
        auto aud_med = dynamic_cast<pj::AudioMedia *>(getMedia(i));
        // Connect the call audio media to sound device
        pj::AudDevManager &mgr = pj::Endpoint::instance().audDevManager();
        aud_med->startTransmit(mgr.getPlaybackDevMedia());
        mgr.getCaptureDevMedia().startTransmit(*aud_med);
    }
}


void VoipCall::setNumber(const char *number) {
    char *mValue = number == nullptr ? nullptr : strdup(number);
    if (this->number != nullptr) {
        free(this->number);
    }
    this->number = mValue;
}

