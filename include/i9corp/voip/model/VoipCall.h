//
// Created by sobrito on 22/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIPCALL_H
#define I9CORP_VOIP_SDK_VOIPCALL_H

#include <i9corp/voip/common/CommonExport.h>
#include <i9corp/voip/controller/VoipHandlerController.h>
#include <i9corp/voip/model/VoipType.h>
#include <pjsua2.hpp>

using namespace i9corp;

namespace i9corp {

    class DLL_EXPORT VoipCall : public pj::Call {
    public:
        VoipCall(int line, VoipHandlerController *controller, pj::Account &account, int callId = PJSUA_INVALID_ID);

        bool mute(bool value);

        bool hold(bool value);

        const char *getNumber();

    private:

        void ringing(int line, long callId, const char *phoneNumber, TVoipCallDirection direction);
        VoipHandlerController *handler;
        char *number;
        char *exten;
    public:
        const char *getExten();

        void setExten(const char *exten);

    public:

    private:
        bool muted;

    public:

    public:
        bool volume(unsigned short value);

        bool isMuted() const;

        bool isInHold() const;

        void onCallState(pj::OnCallStateParam &prm) override;

        void onCallMediaState(pj::OnCallMediaStateParam &prm) override;

    private:
        void setNumber(const char *number);

        TVoipCallDirection direction;
    public:
        TVoipCallDirection getDirection() const;
        void setDirection(TVoipCallDirection direction);


    private:

        bool inHold;
        int line;
        long longId;
        bool hasDirection;
    public:
        long getLongId() const;
    };
}

#endif //I9CORP_VOIP_SDK_VOIPCALL_H
