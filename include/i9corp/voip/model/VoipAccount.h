//
// Created by sobrito on 22/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIPACCOUNT_H
#define I9CORP_VOIP_SDK_VOIPACCOUNT_H

#include <pjsua2.hpp>
#include <i9corp/voip/common/CommonExport.h>
#include <i9corp/voip/controller/VoipHandlerController.h>
#include <i9corp/voip/controller/VoipRegisterStateController.h>
#include <i9corp/voip/model/VoipCall.h>
#include <map>
#include <string>

using namespace i9corp;

namespace i9corp {
    class DLL_EXPORT VoipAccount : public pj::Account {
    public:
        VoipAccount(int line, VoipRegisterStateController *stateController, VoipHandlerController *handlerController);

        ~VoipAccount() override;

        // Native PJSIP Interface
        void onIncomingCall(pj::OnIncomingCallParam &prm) override;

        void onRegState(pj::OnRegStateParam &prm) override;

        VoipCall *getCall(long id);

        void setCall(long id, VoipCall *call);

        void removeCall(long id);

    private:
        VoipRegisterStateController *state;
        VoipHandlerController *handler;
        std::map<long, VoipCall *> calls;
        int line;
    public:
        const std::map<long, VoipCall *> &getCalls() const;
    };
}

#endif //I9CORP_VOIP_SDK_VOIPACCOUNT_H

