//
// Created by sobrito on 16/04/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include <i9corp/voip/controller/VoipHandlerController.h>
#include <i9corp/voip/model/VoipLine.h>

using namespace i9corp;

class Demo : public VoipHandlerController {
public:
    bool running;
    TVoipLineStatus status;
    bool isAutoAnswer() override {
        return false;
    }

    const char *getWaveRingtone(TVoipCallDirection direction, const char *phoneNumber) override {
        fprintf(stdout, "number: %s", phoneNumber);
        return nullptr;
    }

    bool onReject(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) override {
        fprintf(stdout, "number: %s", phoneNumber);
        return false;
    }

    bool onTransfer(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) override {
        fprintf(stdout, "number: %s", phoneNumber);
        return false;
    }

    bool onDial(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) override {
        fprintf(stdout, "number: %s", phoneNumber);
        return false;
    }

    void onIncomingRinging(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) override {
        fprintf(stdout, "number: %s", phoneNumber);
    }

    void onOutgoingRinging(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) override {
        fprintf(stdout, "number: %s", phoneNumber);
    }

    void onAnswer(int line, long callId, const char *phoneNumber) override {
        fprintf(stdout, "number: %s", phoneNumber);
    }

    void onChangeRegisterState(int line, TVoipLineStatus status) override {
        if (this->status != TVoipLineStatus::UNREGISTERED &&  status == TVoipLineStatus::UNREGISTERED) {
            this->running = false;
        }
        this->status = status;
    }

    void onHangup(int line, int callId) override {

    }

    void onInMute(int line, int callId, bool value) override {

    }

    void onInHold(int line, int callId, bool value) override {

    }

    void onChangeVolume(int line, int volume) override {

    }

    void onError(const char *message, ...) override {

    }

    void onNotice(const char *message, ...) override {

    }

    TVoipCallDirection getDirection(const char *number) override {
        return TVoipCallDirection::EXTERNAL;
    }

    void onRingStop(int line, long callId, const char *phoneNumber, TVoipCallDirection direction) override {

    }

};

int main(int argc, char *argv[]) {
    Demo d;
    d.status = TVoipLineStatus::UNREGISTERED;
    d.running = true;
    VoipLine line(1, &d, "4080", "4080!", "10.224.110.223", 5060);
    line.active();

    while(d.running);

    fprintf(stdout, "Fim do app");
}