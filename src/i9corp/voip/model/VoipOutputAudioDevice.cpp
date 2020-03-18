//
// Created by sobrito on 12/03/2020.
//
#include "../common/CommonBuildLibrary.h"
#include <i9corp/voip/model/VoipOutputAudioDevice.h>

using namespace i9corp;

VoipOutputAudioDevice::VoipOutputAudioDevice() {
    this->displayName = nullptr;
    this->muted = false;
    this->standard = false;
}

VoipOutputAudioDevice::~VoipOutputAudioDevice() {
    this->setDisplayName(nullptr);
}

const char *VoipOutputAudioDevice::name() {
    return this->displayName;
}

bool VoipOutputAudioDevice::mute(bool value) {
    return false;
}

bool VoipOutputAudioDevice::isDefault() {
    return false;
}

void VoipOutputAudioDevice::play(const char *audioFile) {

}

bool VoipOutputAudioDevice::isStandard() const {
    return this->standard;
}

void VoipOutputAudioDevice::setStandard(bool value) {
    this->standard = value;
}

bool VoipOutputAudioDevice::isMuted() const {
    return this->muted;
}

void VoipOutputAudioDevice::setMuted(bool value) {
    this->muted = value;
}

char *VoipOutputAudioDevice::getDisplayName() const {
    return this->displayName;
}

void VoipOutputAudioDevice::setDisplayName(const char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->displayName != nullptr) free(this->displayName);
    this->displayName = mValue;
}
