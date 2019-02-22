//
// Created by sobrito on 22/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIP_HANDLER_CONTROLLER_H
#define I9CORP_VOIP_SDK_VOIP_HANDLER_CONTROLLER_H

#include <i9corp/voip/common/CommonExport.h>
#include <i9corp/voip/model/VoipCall.h>
using  namespace i9corp;

namespace i9corp {
    class DLL_EXPORT VoipHandlerController {
    public:
        bool hangup(VoipCall *call);

        bool reject(VoipCall *call);

        bool transfer(const char *number);

        bool dial(const char *number);

        bool dtmf(const char key);

        bool answer();

        bool reload();

        bool mute();

        bool hold();

        void onRingStart(VoipCall *call);
    };
}

#endif //I9CORP_VOIP_SDK_VOIP_HANDLER_CONTROLLER_H
