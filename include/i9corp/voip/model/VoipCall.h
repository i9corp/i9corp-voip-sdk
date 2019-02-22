//
// Created by sobrito on 22/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIPCALL_H
#define I9CORP_VOIP_SDK_VOIPCALL_H

#include <i9corp/voip/common/CommonExport.h>

namespace i9corp {
    class DLL_EXPORT VoipCall {
    public:
        void mute(bool value);
        void hold(bool value);
    };
}

#endif //I9CORP_VOIP_SDK_VOIPCALL_H
