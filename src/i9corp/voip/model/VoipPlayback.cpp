//
// Created by sobrito on 23/02/2019.
//

#include "../common/CommonBuildLibrary.h"
#include <i9corp/voip/model/VoipPlayback.h>
#include <string.h>
#include <stdlib.h>

using namespace i9corp;

VoipPlayback::VoipPlayback(VoipHandlerController *handler, const char *filename) {
    this->initialize();
    this->handler = handler;
    this->setRingtone(filename);

}

VoipPlayback::VoipPlayback(VoipHandlerController *handler, const char *filename, unsigned int duration) {
    this->initialize();
    this->handler = handler;
    this->setRingtone(filename);
    this->duration = duration;
}

VoipPlayback::VoipPlayback(VoipHandlerController *handler, const char *filename, unsigned int duration, int deviceId) {
    this->initialize();
    this->handler = handler;
    this->setRingtone(filename);
    this->duration = duration;
    this->deviceId = deviceId;
}

VoipPlayback::~VoipPlayback() {
    this->stop();
    this->handler = nullptr;
}

bool VoipPlayback::start() {
    if (!this->startPlayer()) {
        return false;
    }
    this->keepPlaying();
}

void VoipPlayback::keepPlaying() {
    if (this->duration > 0) {
        this->remaining = this->duration;
    }

    while (this->isPlaying()) {
        pj_thread_sleep(1000);
        if (this->duration > 0) {
            this->remaining--;
        }

        if (this->remaining == 0 && this->duration > 0) {
            this->stop();
        }
    }
}

void VoipPlayback::stop() {
    if (this->isPlaying()) {
        this->stopPlayer();
    }
    this->remaining = 0;
    this->playing = false;
}

void VoipPlayback::setRingtone(const char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->ringtone != nullptr) {
        free(this->ringtone);
    }
    this->ringtone = mValue;
}

void VoipPlayback::initialize() {
    this->ringtone = nullptr;
    this->remaining = 0;
}

bool VoipPlayback::isPlaying() const {
    return playing;
}

bool VoipPlayback::startPlayer() {
    pj_status_t status;
    pj_thread_desc initdec;
    if (!pj_thread_is_registered() && pj_thread_register("PJ_THREAD", initdec, &thread) != PJ_SUCCESS) {
        this->handler->onError("Failure create playback thread");
        return false;
    }

    status = pj_init();
    if (status != PJ_SUCCESS) {
        this->handler->onError("Unable to  pj %d", status);
        return false;
    }

    pj_caching_pool_init(&cp, &pj_pool_factory_default_policy, 0);

    status = pjmedia_endpt_create(&cp.factory, nullptr, 1, &med_endpt);
    if (status != PJ_SUCCESS) {
        this->handler->onError("Unable to initialize the media endpoint %d", status);
        return false;
    }

    pool = pj_pool_create(&cp.factory, "wav", 4000, 4000, nullptr);

    status = pjmedia_wav_player_port_create(pool, this->ringtone, 20, 0, 0, &file_port);
    if (status != PJ_SUCCESS) {
        this->handler->onError("Unable to use WAV file: %s", this->ringtone);
        return false;
    }
    status = pjmedia_snd_port_create_player(
            pool, /* pool */
            -1, /* use default dev. */
            PJMEDIA_PIA_SRATE(&file_port->info),/* clock rate. */
            PJMEDIA_PIA_CCNT(&file_port->info),/* # of channels. */
            PJMEDIA_PIA_SPF(&file_port->info), /* samples per frame. */
            PJMEDIA_PIA_BITS(&file_port->info),/* bits per sample. */
            0, /* options */
            &snd_port /* returned port */
    );
    if (status != PJ_SUCCESS) {
        this->handler->onError("Unable to open sound device %d", status);
        return false;
    }
    status = pjmedia_snd_port_connect(snd_port, file_port);
    if (status != PJ_SUCCESS) {
        this->handler->onError("Unable to start sound player %d", status);
        return false;
    }

    pj_thread_sleep(100);
    this->handler->onError("Playing %s..\n", this->ringtone);

    this->playing = true;
    return true;
}

bool VoipPlayback::stopPlayer() {
    pj_status_t status;
    status = pjmedia_snd_port_disconnect(snd_port);
    if (status != PJ_SUCCESS) {
        this->handler->onError("Do not can disconnect the player");
        return false;
    }

    pj_thread_sleep(100);

    status = pjmedia_snd_port_destroy(snd_port);
    if (status != PJ_SUCCESS) {
        this->handler->onError("Do not can destroy the device");
        return false;
    }

    /* Destroy file port */
    status = pjmedia_port_destroy(file_port);
    if (status != PJ_SUCCESS) {
        this->handler->onError("Do not can destroy the file port");
        return false;
    }

    pj_pool_release(pool);
    pjmedia_endpt_destroy(med_endpt);
    pj_caching_pool_destroy(&cp);
    pj_shutdown();

    if (this->player.joinable()) {
        this->player.detach();
    }
    return true;
}

bool VoipPlayback::play() {

    if (this->isPlaying()) {
        this->handler->onError("Already is running");
        return false;
    }
    player = std::thread(VoipPlayback::run, this);
    player.join();
    return true;
}

void VoipPlayback::run(VoipPlayback *playback) {
    playback->start();
}

