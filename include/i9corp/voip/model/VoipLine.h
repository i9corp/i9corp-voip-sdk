//
// Created by sobrito on 22/02/2019.
//

#ifndef I9CORP_VOIP_SDK_VOIPLINE_H
#define I9CORP_VOIP_SDK_VOIPLINE_H

#include <i9corp/voip/common/CommonExport.h>
#include <i9corp/voip/controller/VoipHandlerController.h>

namespace i9corp {
    class DLL_EXPORT  VoipLine {
    public:
        VoipLine();

        VoipLine(const char *username, const char *password, const char *hostname, unsigned short port);

        ~VoipLine();

    private:
        char *username;
    public:
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
    public:
        long getId() const;

    private:
        long id;
        char *password;
        char *hostname;
        unsigned short port;
        VoipHandlerController *handler;
    };

}
#endif //I9CORP_VOIP_SDK_VOIPLINE_H
