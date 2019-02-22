//
// Created by sobrito on 22/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIP_HANDLER_CONTROLLER_H
#define I9CORP_VOIP_SDK_VOIP_HANDLER_CONTROLLER_H

#include <i9corp/voip/common/CommonExport.h>
#include <i9corp/voip/model/VoipCall.h>

using namespace i9corp;

namespace i9corp {
    typedef enum eVoipCallDirection {
        OUTGOING,
        INCOMING,
        INTERNAL
    } TVoipCallDirection;


    class DLL_EXPORT VoipHandlerController {
    public:
        virtual bool hangup(VoipCall *call) = 0;

        virtual bool isAutoAnswer() = 0;

        virtual bool reject(VoipCall *call) = 0;

        virtual bool transfer(const char *number) = 0;

        virtual bool dial(const char *number) = 0;

        virtual bool dtmf(const char key) = 0;

        virtual bool answer() = 0;

        virtual bool reload() = 0;

        virtual bool mute() = 0;

        virtual bool hold() = 0;

        virtual void onError(const char *message) = 0;

        virtual void onNotice(const char *message) = 0;

        virtual void onRingStart(VoipCall *call) = 0;

        virtual void
        onIncomingRinging(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) = 0;
    };
}

#endif //I9CORP_VOIP_SDK_VOIP_HANDLER_CONTROLLER_H
