//
// Created by sobrito on 23/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIP_REGISTER_STATE_CONTROLLER_H
#define I9CORP_VOIP_SDK_VOIP_REGISTER_STATE_CONTROLLER_H

#include <i9corp/voip/controller/VoipHandlerController.h>
#include <i9corp/voip/common/CommonExport.h>
#include <i9corp/voip/model/VoipCall.h>

namespace i9corp {
    class DLL_EXPORT VoipRegisterStateController {
    public:
        virtual void onChangeRegisterState(TVoipLineStatus status) = 0;
        virtual void onCreateCall(VoipCall *call) = 0;
        virtual void onRemoveCall(VoipCall *call) = 0;
    };
}

#endif //I9CORP_VOIP_SDK_VOIP_REGISTER_STATE_CONTROLLER_H
