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

        virtual ~VoipHandlerController();

        // System
        virtual bool isAutoAnswer() = 0;

        void onError(const char *message, ...);

        void onNotice(const char *message, ...);

         const char *getWaveRingtone(TVoipCallDirection direction, const char *phoneNumber);

        TVoipCallDirection getDirection(const char *number);

        // Call

         bool onReject(int line, long callId, const char *phoneNumber, TVoipCallDirection direction);

         bool onTransfer(int line, long callId, const char *phoneNumber, TVoipCallDirection direction);

         bool onDial(int line, long callId, const char *phoneNumber, TVoipCallDirection direction);


         void
        onIncomingRinging(int line, long callId, const char *phoneNumber, TVoipCallDirection direction);

         void
        onOutgoingRinging(int line, long callId, const char *phoneNumber, TVoipCallDirection direction);

         void onAnswer(int line, long callId, const char *phoneNumber);

         void onChangeRegisterState(int line, TVoipLineStatus status);

         void onHangup(int line, int callId);

         void onInMute(int line, int callId, bool value) ;

         void onInHold(int line, int callId, bool value);
         void onChangeVolume(int line, int volume);

    };
}

#endif //I9CORP_VOIP_SDK_VOIP_HANDLER_CONTROLLER_H
