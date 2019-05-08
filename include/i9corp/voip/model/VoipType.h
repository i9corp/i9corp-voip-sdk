//
// Created by sobrito on 15/04/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIPTYPES_H
#define I9CORP_VOIP_SDK_VOIPTYPES_H

#include <i9corp/voip/common/CommonExport.h>

namespace i9corp {
    class DLL_EXPORT VoipType {
    public:
        enum Direction {
            OUTGOING,
            INCOMING,
            INTERNAL,
            EXTERNAL,
            UNDEFINED
        };

        enum Line {
            REGISTERED,
            UNREGISTERED,
            REGISTERING,
            UNREGISTERING
        };

        enum Call {
            HANGUP,
            TRANSFERRING,
            DIALING,
            RECEIVING,
            ANSWERED,
            RINGING,
            REJECT
        };
    private:
        VoipType();
    };
}

typedef i9corp::VoipType::Direction TVoipCallDirection;
typedef i9corp::VoipType::Line TVoipLineStatus;
typedef i9corp::VoipType::Call TVoipCallStatus;

#endif //I9CORP_VOIP_SDK_VOIPTYPES_H
