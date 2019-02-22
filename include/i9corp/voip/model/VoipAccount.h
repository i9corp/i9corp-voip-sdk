//
// Created by sobrito on 22/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIPACCOUNT_H
#define I9CORP_VOIP_SDK_VOIPACCOUNT_H

#include <pjsua2.hpp>
#include <i9corp/voip/controller/VoipHandlerController.h>
#include <i9corp/voip/model/VoipCall.h>
#include <map>
#include <string>

namespace i9corp {
    class VoipAccount : public pj::Account {
    public:
        VoipAccount(int line, VoipHandlerController *controller);

        ~VoipAccount() override;

        // Native PJSIP Interface
        void onIncomingCall(pj::OnIncomingCallParam &prm) override;

        void onRegStarted(pj::OnRegStartedParam &prm) override;

        void onRegState(pj::OnRegStateParam &prm) override;

        void onIncomingSubscribe(pj::OnIncomingSubscribeParam &prm) override;

        void onInstantMessage(pj::OnInstantMessageParam &prm) override;

        void onInstantMessageStatus(pj::OnInstantMessageStatusParam &prm) override;

        void onTypingIndication(pj::OnTypingIndicationParam &prm) override;

        void onMwiInfo(pj::OnMwiInfoParam &prm) override;

        setCall(long id, VoipCall *call);
        void removeCall(long id);
    private:
        VoipHandlerController *handler;
        std::map<long, VoipCall *> calls;
        int line;
    public:
        const std::map<long, VoipCall *> &getCalls() const;
    };
}

#endif //I9CORP_VOIP_SDK_VOIPACCOUNT_H

