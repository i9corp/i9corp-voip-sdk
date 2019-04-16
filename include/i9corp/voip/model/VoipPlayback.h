//
// Created by sobrito on 23/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIPPLAYBACK_H
#define I9CORP_VOIP_SDK_VOIPPLAYBACK_H

#include <i9corp/voip/common/CommonExport.h>
#include <i9corp/voip/controller/VoipHandlerController.h>
#include <pjsua2.hpp>
#include <pthread.h>

namespace i9corp {
    class DLL_EXPORT VoipPlayback {
    public:
        VoipPlayback(VoipHandlerController *handler, const char *filename, unsigned int duration, int deviceId);

        VoipPlayback(VoipHandlerController *handler, const char *filename, unsigned int duration);

        VoipPlayback(VoipHandlerController *handler, const char *filename);
        ~VoipPlayback();

        bool play();
        void stop();

    private:
        bool start();
        void initialize();

        char *ringtone;
        unsigned int duration;
        unsigned int remaining;
        int deviceId;
        bool playing;
        void keepPlaying();
    public:
        bool isPlaying() const;
        bool startPlayer();
        bool stopPlayer();

        static void * run(void *mData);
    private:
        VoipHandlerController *handler;
        pjmedia_snd_port *snd_port;
        pjmedia_endpt *med_endpt;
        pj_pool_t *pool;
        pjmedia_port *file_port;
        pj_thread_t *thread;
        pj_caching_pool cp;

        pthread_t player;
        void setRingtone(const char *ringtone);

    };
}

#endif //I9CORP_VOIP_SDK_VOIPPLAYBACK_H
