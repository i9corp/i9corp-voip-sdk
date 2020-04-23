//
// Created by sobrito on 11/03/2020.
//
#include "../common/CommonBuildLibrary.h"
#include <i9corp/voip/model/VoipDeviceAudio.h>
#include <i9corp/voip/model/VoipInputAudioDevice.h>
#include <i9corp/voip/model/VoipOutputAudioDevice.h>
#include <stdlib.h>
#include <vector>

using namespace i9corp;

VoipDeviceAudio::VoipDeviceAudio() {
    this->selectedInputDeviceAudio = nullptr;
    this->selectedOutputDeviceAudio = nullptr;
    this->lock = new std::mutex();
}

VoipDeviceAudio::~VoipDeviceAudio() {
    this->clear();
    delete this->lock;
}

const std::vector<IInputDeviceAudio *> &VoipDeviceAudio::getInputs() const {
    return inputs;
}

const std::vector<IOutputDeviceAudio *> &VoipDeviceAudio::getOutputs() const {
    return outputs;
}

void VoipDeviceAudio::play(const char *filename) {
    std::unique_lock<std::mutex> lck(*this->lock);
    if (filename == nullptr)return;
    pj::AudioMediaPlayer player;
    pj::AudioMedia &play_dev_med = pj::Endpoint::instance().audDevManager().getPlaybackDevMedia();
    try {
        player.createPlayer(filename, PJMEDIA_FILE_NO_LOOP);
        player.startTransmit(play_dev_med);
    } catch (pj::Error &err) {
    }
}

void VoipDeviceAudio::record(const char *filename) {
//    AudioMediaRecorder recorder;
//    AudioMedia &cap_dev_med = Endpoint::instance().audDevManager().getCaptureDevMedia();
//    try {
//        recorder.createRecorder(filename);
//        cap_dev_med.startTransmit(recorder);
//    } catch (pj::Error &err) {
//    }

// Stop
//    cap_dev_med.stopTransmit(recorder);
}


void VoipDeviceAudio::setOutput(IOutputDeviceAudio *output) {
    std::unique_lock<std::mutex> lck(*this->lock);
    if (output == nullptr) return;
    this->selectedOutputDeviceAudio = output;
}

void VoipDeviceAudio::setInput(IInputDeviceAudio *input) {
    std::unique_lock<std::mutex> lck(*this->lock);
    if (input == nullptr) return;
    this->selectedInputDeviceAudio = input;
}

void VoipDeviceAudio::clear() {
    this->clear(true);
}

bool VoipDeviceAudio::discovery() {
#ifndef __APPLE__
    std::unique_lock<std::mutex> lck(*this->lock);
    this->clear(false);
    pj::Endpoint ep;
    ep.libCreate();
    // Initialize endpoint
    pj::EpConfig ep_cfg;
    ep.libInit(ep_cfg);
    pj::AudDevManager &manager = ep.audDevManager();
    manager.refreshDevs();
    const pj::AudioDevInfoVector &list = manager.enumDev();

    for (unsigned int i = 0; list.size() != i; i++) {
        pj::AudioDevInfo *info = list[i];

        if (info->inputCount > 0) {
            auto device = new VoipInputAudioDevice();
            device->setDisplayName(info->name.c_str());
            this->inputs.push_back(device);
        }
        if (info->outputCount > 0) {
            auto device = new VoipOutputAudioDevice();
            device->setDisplayName(info->name.c_str());
            this->outputs.push_back(device);
        }
    }
    ep.libDestroy();
    // if (!this->discoveryInput()) return false;
    //if (!this->discoveryOutput()) return false;
#endif
    return true;
}

void VoipDeviceAudio::clear(bool safe) {
    if (safe) std::unique_lock<std::mutex> lck(*this->lock);
    for (auto it = inputs.begin(); it != inputs.end(); it++) delete *it;
    inputs.clear();

    for (auto it = outputs.begin(); it != outputs.end(); it++) delete *it;
    outputs.clear();
}
