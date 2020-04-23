//
// Created by sobrito on 11/03/2020.
//

#ifndef I9CORP_VOIP_SDK_IOUTPUTDEVICEAUDIO_H
#define I9CORP_VOIP_SDK_IOUTPUTDEVICEAUDIO_H

namespace i9corp {

    class IOutputDeviceAudio {
    public:
        virtual const char *name() = 0;

        virtual bool mute(bool value) = 0;

        virtual bool isDefault() = 0;

        virtual void play(const char *audioFile) = 0;

        virtual ~IOutputDeviceAudio();
    };

    IOutputDeviceAudio::~IOutputDeviceAudio() = default;
}


#endif //I9CORP_VOIP_SDK_IOUTPUTDEVICEAUDIO_H
