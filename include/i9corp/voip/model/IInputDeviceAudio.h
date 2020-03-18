//
// Created by sobrito on 11/03/2020.
//

#ifndef I9CORP_VOIP_SDK_IINPUTDEVICEAUDIO_H
#define I9CORP_VOIP_SDK_IINPUTDEVICEAUDIO_H

#include <vector>

namespace i9corp {

    class IInputDeviceAudio {
    public:
        virtual const char *name() = 0;

        virtual bool mute(bool value) = 0;

        virtual bool isDefault() = 0;

    };
}


#endif //I9CORP_VOIP_SDK_IINPUTDEVICEAUDIO_H
