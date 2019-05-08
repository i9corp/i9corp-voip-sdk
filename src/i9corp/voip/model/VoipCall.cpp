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
    this->longId = VoipTools::getLongId(this);
    this->hasDirection = false;
    this->direction = TVoipCallDirection::UNDEFINED;
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
        this->handler->onInHold(this->line, this->getLongId(), value);
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
            this->handler->onInMute(this->line, this->getLongId(), value);
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
    pj::CallInfo ci = getInfo();
    Call::onCallState(prm);
    std::string source;

    switch (ci.state) {
        case PJSIP_INV_STATE_DISCONNECTED:
            this->handler->onHangup(this->line, this->getLongId());
            break;
        case PJSIP_INV_STATE_CONNECTING:
        case PJSIP_INV_STATE_CALLING:
            this->ringing(this->line, this->getLongId(), this->getNumber(),
                                             this->getDirection());
            break;
        case PJSIP_INV_STATE_CONFIRMED:
            this->handler->onAnswer(this->line, this->getLongId(), this->getNumber());
            break;
        case PJSIP_INV_STATE_INCOMING:
            this->ringing(this->line, this->getLongId(), this->getNumber(), this->getDirection());
            break;
        case PJSIP_INV_STATE_EARLY:
            if (ci.lastStatusCode != PJSIP_SC_RINGING) {
                this->handler->onRingStop(this->line, this->getLongId(), this->getNumber(), this->getDirection());
                return;
            }

            switch (ci.role) {
                case PJSIP_ROLE_UAC:
                    this->setDirection(this->handler->getDirection(this->getExten(), this->getNumber()));
                    this->ringing(this->line, this->getLongId(), this->getNumber(),
                                                     this->getDirection());
                    break;
                case PJSIP_ROLE_UAS:
                    this->setDirection(TVoipCallDirection::OUTGOING);
                    this->ringing(this->line, this->getLongId(), this->getNumber(),
                                                     this->getDirection());
                    break;
            }

            break;
    }
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

const char *VoipCall::getNumber() {
    if (this->number == nullptr) {
        pj::CallInfo ci = getInfo();
        char *mValue = VoipTools::getPhoneNumberFromUri(ci.remoteUri.c_str());
        this->setNumber(mValue);
        if (mValue != nullptr) free(mValue);
    }
    return number;
}


void VoipCall::setNumber(const char *number) {
    char *mValue = number == nullptr ? nullptr : strdup(number);
    if (this->number != nullptr) {
        free(this->number);
    }
    this->number = mValue;
}


const char *VoipCall::getExten() {
    if (this->exten == nullptr) {
        pj::CallInfo ci = getInfo();
        char *mValue = VoipTools::getPhoneNumberFromUri(ci.localUri.c_str());
        this->setExten(mValue);
        if (mValue != nullptr) free(mValue);
    }
    return number;
}

void VoipCall::setExten(const char *exten) {
    char *mValue = exten == nullptr ? nullptr : strdup(exten);
    if (this->exten != nullptr) {
        free(this->exten);
    }
    this->exten = mValue;
}


long VoipCall::getLongId() const {
    return longId;
}

void VoipCall::setDirection(TVoipCallDirection direction) {
    if (this->hasDirection) {
        return;
    }
    VoipCall::direction = direction;
    this->hasDirection = true;
}

TVoipCallDirection VoipCall::getDirection() const {
    return direction;
}

void VoipCall::ringing(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) {
    switch (direction) {
        case TVoipCallDirection::OUTGOING:
            this->handler->onOutgoingRinging(line, callId, phoneNumber, direction);
            break;
        case TVoipCallDirection::INCOMING:
        case TVoipCallDirection::EXTERNAL:
        case TVoipCallDirection::INTERNAL:
            this->handler->onIncomingRinging(line, callId, phoneNumber, direction);
            break;
        default:
            return;
    }

}
