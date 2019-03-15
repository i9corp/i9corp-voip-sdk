//
// Created by sobrito on 22/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIPTOOLS_H
#define I9CORP_VOIP_SDK_VOIPTOOLS_H

#include <i9corp/voip/common/CommonExport.h>

namespace i9corp {
    class DLL_EXPORT VoipTools {
    public:
        static char *getPhoneNumberFromUri(const char *value);

        static long getLongId(const void *reference);
    };
}

#endif //I9CORP_VOIP_SDK_VOIPTOOLS_H
