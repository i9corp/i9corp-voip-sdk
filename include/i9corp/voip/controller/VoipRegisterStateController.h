//
// Created by sobrito on 23/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIP_REGISTER_STATE_CONTROLLER_H
#define I9CORP_VOIP_SDK_VOIP_REGISTER_STATE_CONTROLLER_H

#include <i9corp/voip/controller/VoipHandlerController.h>

namespace i9corp {
    class VoipRegisterStateController {
    public:
        virtual void onChangeRegisterState(TVoipLineStatus status) = 0;
    };
}

#endif //I9CORP_VOIP_SDK_VOIP_REGISTER_STATE_CONTROLLER_H