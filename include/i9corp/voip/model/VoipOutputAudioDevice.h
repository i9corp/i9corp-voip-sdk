//
// Created by sobrito on 12/03/2020.
//

#ifndef I9CORP_VOIP_SDK_VOIPOUTPUTAUDIODEVICE_H
#define I9CORP_VOIP_SDK_VOIPOUTPUTAUDIODEVICE_H

#include <i9corp/voip/common/CommonExport.h>
#include <i9corp/voip/model/IOutputDeviceAudio.h>
#include <string.h>
#include <stdlib.h>

namespace i9corp {

    class DLL_EXPORT VoipOutputAudioDevice : public IOutputDeviceAudio {
    public:
        VoipOutputAudioDevice();

        ~VoipOutputAudioDevice();

        const char *name() override;

        bool mute(bool value) override;

        bool isDefault() override;

        void play(const char *audioFile) override;

        bool isStandard() const;

        void setStandard(bool standard);

        bool isMuted() const;

        void setMuted(bool muted);

        char *getDisplayName() const;

        void setDisplayName(const char *displayName);

    private:
        bool standard;
        bool muted;
        char *displayName;
    };

}
#endif //I9CORP_VOIP_SDK_VOIPOUTPUTAUDIODEVICE_H
