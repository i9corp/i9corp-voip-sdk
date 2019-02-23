//
// Created by sobrito on 22/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIP_HANDLER_CONTROLLER_H
#define I9CORP_VOIP_SDK_VOIP_HANDLER_CONTROLLER_H

#include <i9corp/voip/common/CommonExport.h>

namespace i9corp {
    typedef enum eVoipCallDirection {
        OUTGOING,
        INCOMING,
        INTERNAL,
        EXTERNAL
    } TVoipCallDirection;

    typedef enum eVoipLineStatus {
        REGISTERED,
        UNREGISTERED,
        REGISTERING,
        UNREGISTERING
    } TVoipLineStatus;

    typedef enum eVoipCallStatus {
        HANGUP,
        TRANSFERRING,
        DIALING,
        RECEIVING,
        ANSWERED,
        RINGING,
        REJECT
    } TVoipCallStatus;

    class DLL_EXPORT VoipHandlerController {
    public:
        VoipHandlerController();

        ~VoipHandlerController();

        // System
        virtual bool isAutoAnswer() = 0;

        void onError(const char *message, ...);

        void onNotice(const char *message, ...);

        virtual const char *getWaveRingtone(TVoipCallDirection direction, const char *phoneNumber) = 0;

        TVoipCallDirection getDirection(const char *number);

        // Call

        virtual bool onReject(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) = 0;

        virtual bool onTransfer(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) = 0;

        virtual bool onDial(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) = 0;


        virtual void
        onIncomingRinging(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) = 0;

        virtual void
        onOutgoingRinging(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) = 0;

        virtual void onAnswer(int line, long callId, const char *phoneNumber) = 0;

        virtual void onChangeRegisterState(int line, TVoipLineStatus status) = 0;

        virtual void onHangup(int line, int callId) = 0;

        virtual void onInMute(int line, int callId, bool value) = 0;

        virtual void onInHold(int line, int callId, bool value) = 0;
        virtual void onChangeVolume(int line, int volume) = 0;

    };
}

#endif //I9CORP_VOIP_SDK_VOIP_HANDLER_CONTROLLER_H