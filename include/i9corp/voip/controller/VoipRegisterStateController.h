//
// Created by sobrito on 23/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIP_REGISTER_STATE_CONTROLLER_H
#define I9CORP_VOIP_SDK_VOIP_REGISTER_STATE_CONTROLLER_H

#include <i9corp/voip/controller/VoipHandlerController.h>
#include <i9corp/voip/common/CommonExport.h>

namespace i9corp {
    class DLL_EXPORT VoipRegisterStateController {
    public:
        virtual void onChangeRegisterState(TVoipLineStatus status)
        {

        }
    };
}

#endif //I9CORP_VOIP_SDK_VOIP_REGISTER_STATE_CONTROLLER_H
