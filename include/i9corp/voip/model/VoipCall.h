//
// Created by sobrito on 22/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIPCALL_H
#define I9CORP_VOIP_SDK_VOIPCALL_H

#include <i9corp/voip/common/CommonExport.h>
#include <i9corp/voip/controller/VoipHandlerController.h>
#include <i9corp/voip/model/VoipAccount.h>
#include <pjsua2.hpp>

namespace i9corp {

    class DLL_EXPORT VoipCall : public pj::Call {
    public:
        VoipCall(VoipHandlerController *controller, VoipAccount &account, int callId);

        void mute(bool value);

        void hold(bool value);

        char *getNumber() const;

    private:
        VoipHandlerController *handler;
        char *number;

    };
}

#endif //I9CORP_VOIP_SDK_VOIPCALL_H
