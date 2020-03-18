//
// Created by sobrito on 12/03/2020.
//
#include "../common/CommonBuildLibrary.h"
#include <i9corp/voip/model/VoipInputAudioDevice.h>
#include <string.h>
#include <stdlib.h>

using namespace i9corp;

VoipInputAudioDevice::VoipInputAudioDevice() {
    this->standard = false;
    this->muted = false;
    this->displayName = nullptr;
}

VoipInputAudioDevice::~VoipInputAudioDevice() {
    this->setDisplayName(nullptr);
}

const char *VoipInputAudioDevice::name() {
    return this->displayName;
}

bool VoipInputAudioDevice::mute(bool value) {
    this->setMuted(value);
    return true;
}

bool VoipInputAudioDevice::isDefault() {
    return this->standard;
}

bool VoipInputAudioDevice::isStandard() const {
    return standard;
}

void VoipInputAudioDevice::setStandard(bool value) {
    VoipInputAudioDevice::standard = value;
}

bool VoipInputAudioDevice::isMuted() const {
    return muted;
}

void VoipInputAudioDevice::setMuted(bool value) {
    this->muted = value;
}

char *VoipInputAudioDevice::getDisplayName() const {
    return displayName;
}

void VoipInputAudioDevice::setDisplayName(const char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->displayName != nullptr) free(this->displayName);
    this->displayName = mValue;
}
