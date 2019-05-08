//
// Created by sobrito on 22/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIP_HANDLER_CONTROLLER_H
#define I9CORP_VOIP_SDK_VOIP_HANDLER_CONTROLLER_H

#include <i9corp/voip/common/CommonExport.h>
#include <stdlib.h>
#include <i9corp/voip/model/VoipType.h>

using namespace i9corp;
namespace i9corp {

class DLL_EXPORT VoipHandlerController {
public:
    // System
    virtual bool isAutoAnswer() = 0;


    // Call
    virtual const char *getWaveRingtone(TVoipCallDirection direction, const char *phoneNumber) = 0;
    virtual bool onReject(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) = 0;
    virtual bool onTransfer(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) = 0;
    virtual bool onDial(int line, long callId, const char *phoneNumber, TVoipCallDirection direction)= 0;
    virtual void onIncomingRinging(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) = 0;
    virtual void onOutgoingRinging(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) = 0;
    virtual void onRingStop(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) = 0;
    virtual void onAnswer(int line, long callId, const char *phoneNumber) = 0;
    virtual void onChangeRegisterState(int line, TVoipLineStatus status) = 0;
    virtual void onHangup(int line, int callId) = 0;
    virtual void onInMute(int line, int callId, bool value) = 0;
    virtual void onInHold(int line, int callId, bool value) = 0;
    virtual void onChangeVolume(int line, int volume) = 0;

    virtual void onError(const char *message, ...)= 0;

    virtual void onNotice(const char *message, ...)= 0;

    virtual TVoipCallDirection getDirection(const char *branch, const char *number)= 0;

};
}

#endif //I9CORP_VOIP_SDK_VOIP_HANDLER_CONTROLLER_H
