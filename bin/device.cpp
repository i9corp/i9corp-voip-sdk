//
// Created by sobrito on 12/03/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <i9corp/voip/model/VoipDeviceAudio.h>
#include <vector>
#include <i9corp/voip/model/IOutputDeviceAudio.h>
#include <i9corp/voip/model/IInputDeviceAudio.h>

using namespace i9corp;

int main(int argc, char *argv[]) {
    VoipDeviceAudio dev;
    if (!dev.discovery()) {
        fprintf(stdout, "failure on discovery\r\n");
    }
    fprintf(stdout, "discovered input device\r\n");
    const std::vector<IInputDeviceAudio *> &inputs = dev.getInputs();
    for (auto it = inputs.begin(); it != inputs.end(); it++) {
        IInputDeviceAudio *device = *it;
        fprintf(stdout, "dev: %s\r\n", device->name());
    }
    fprintf(stdout, "discovered output device\r\n");
    const std::vector<IOutputDeviceAudio *> &outputs = dev.getOutputs();
    for (auto it = outputs.begin(); it != outputs.end(); it++) {
        IOutputDeviceAudio *device = *it;
        fprintf(stdout, "dev: %s\r\n", device->name());
    }
}