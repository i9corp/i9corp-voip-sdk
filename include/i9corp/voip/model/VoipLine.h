//
// Created by sobrito on 22/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIPLINE_H
#define I9CORP_VOIP_SDK_VOIPLINE_H

#include <i9corp/voip/common/CommonExport.h>
#include <i9corp/voip/controller/VoipHandlerController.h>
#include <i9corp/voip/model/VoipCall.h>
#include <i9corp/voip/model/VoipAccount.h>
#include <pjsua2.hpp>

namespace i9corp {

    typedef enum eVoipLineStatus {
        REGISTERED,
        UNREGISTERED,
        REGISTERING,
        UNREGISTERING
    } TVoipLineStatus;

    class DLL_EXPORT  VoipLine {
    public:
        VoipLine(int number, VoipHandlerController *controller,);

        VoipLine(int number, VoipHandlerController *controller, const char *username, const char *password,
                 const char *hostname, unsigned short port);

        ~VoipLine();

        bool active();

        bool deactivate();

        bool reject(VoipCall *call);

        bool hangup(VoipCall *call);

    private:
        void initialize();

        char *username;
    public:
        void dial(const char *text);

        char *getUsername() const;

        void setUsername(char *username);

        char *getPassword() const;

        void setPassword(char *password);

        char *getHostname() const;

        void setHostname(char *hostname);

        unsigned short getPort() const;

        void setPort(unsigned short port);

        VoipHandlerController *getHandler() const;

        void setHandler(VoipHandlerController *handler);

        VoipCall *getCurrentCall();

    public:
        long getId() const;

    private:
        int number;
    public:
        int getNumber() const;

        void setNumber(int number);

    private:
        long id;
        char *password;
        char *hostname;
        unsigned short port;
        VoipHandlerController *handler;
        VoipCall *currentCall;
        bool registered;
        char *stunServer;
        VoipAccount *account;
        TVoipLineStatus status;

    public:
        void setStunServer(char *stunServer);

    private:
        char *regUri;
    public:
        void setRegUri(char *regUri);

        void setIdUri(char *idUri);

    private:
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
