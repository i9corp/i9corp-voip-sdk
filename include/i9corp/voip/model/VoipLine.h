//
// Created by sobrito on 22/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIPLINE_H
#define I9CORP_VOIP_SDK_VOIPLINE_H

#include <i9corp/voip/common/CommonExport.h>
#include <i9corp/voip/controller/VoipHandlerController.h>
#include <i9corp/voip/controller/VoipRegisterStateController.h>
#include <i9corp/voip/model/VoipCall.h>
#include <i9corp/voip/model/VoipAccount.h>
#include <pjsua2.hpp>

namespace i9corp {


    class DLL_EXPORT  VoipLine : public VoipRegisterStateController {
    public:
        VoipLine(int number, VoipHandlerController *controller);

        VoipLine(int number, VoipHandlerController *controller, const char *username, const char *password,
                 const char *hostname, unsigned short port);

       virtual  ~VoipLine();

        bool active();

        bool deactivate();

        // Call
        VoipCall *getCurrentCall();

        char *toSipNumber(const char *number);

        bool dtmf(long callId, char digits);

        bool dtmf(long callId, const char *digits);

        bool transfer(const char *number);

        bool transfer(long callId, const char *digits);

        bool dial(const char *digits);

        bool reject(long callId);

        bool volume(long callId, unsigned short value);

        bool hangup();

        bool hangup(long callId);

        bool answer();

        bool answer(long callId);

        bool mute(bool value);

        bool mute(long callId, bool value);

        bool hold(bool value);

        bool hold(long callId, bool value);

    public:
        char *getUsername() const;

        void setUsername(const char *username);

        char *getPassword() const;

        void setPassword(const char *password);

        char *getHostname() const;

        void setHostname(const char *hostname);

        unsigned short getPort() const;

        void setPort(unsigned short port);

        long getId();


        int getNumber() const;

        void setNumber(int number);

        void setStunServer(const char *stunServer);

        void setStatus(TVoipLineStatus value);

        void onChangeRegisterState(TVoipLineStatus status) override;


    private:
        void initialize();

        long id;
        int number;
        char *username;
        char *password;
        char *hostname;
        unsigned short port;
        VoipHandlerController *handler;
        VoipCall *currentCall;
        bool registered;
        char *stunServer;
        VoipAccount *account;
        TVoipLineStatus status;

        void setRegUri(const char *regUri);

        void setIdUri(const char *idUri);

        char *regUri;
        char *idUri;

        // PJSIP
        pj::Endpoint endpoint;
        pj::TransportConfig transportConfig;
        pj::AccountConfig accountConfig;
        pj::EpConfig endpointConfig;
        pj::AuthCredInfo cred;
    };

}
#endif //I9CORP_VOIP_SDK_VOIPLINE_H
