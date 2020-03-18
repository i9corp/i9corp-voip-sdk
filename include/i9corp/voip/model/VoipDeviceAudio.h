//
// Created by sobrito on 11/03/2020.
//

#ifndef I9CORP_VOIP_SDK_VOIPDEVICEAUDIO_H
#define I9CORP_VOIP_SDK_VOIPDEVICEAUDIO_H

#include <i9corp/voip/model/IOutputDeviceAudio.h>
#include <i9corp/voip/model/IInputDeviceAudio.h>
#include <i9corp/voip/common/CommonExport.h>
#include <vector>
#include <mutex>
#include <pjsua2.hpp>

namespace i9corp {

    class DLL_EXPORT VoipDeviceAudio {
    public:
        VoipDeviceAudio();

        ~VoipDeviceAudio();

        bool discovery();

        void setInput(IInputDeviceAudio *input);

        void setOutput(IOutputDeviceAudio *output);

        void play(const char *filename);

        void record(const char *filename);

        const std::vector<IInputDeviceAudio *> &getInputs() const;

        const std::vector<IOutputDeviceAudio *> &getOutputs() const;

    private:
        std::mutex *lock;

        void clear();

        void clear(bool safe);

        std::vector<IInputDeviceAudio *> inputs;
        std::vector<IOutputDeviceAudio *> outputs;
        IInputDeviceAudio *selectedInputDeviceAudio;
        IOutputDeviceAudio *selectedOutputDeviceAudio;
    };
}


#endif //I9CORP_VOIP_SDK_VOIPDEVICEAUDIO_H
