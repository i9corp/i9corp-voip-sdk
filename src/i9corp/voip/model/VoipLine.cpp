//
// Created by sobrito on 22/02/2019.
//

#include "../common/CommonBuildLibrary.h"
#include <i9corp/voip/model/VoipLine.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace i9corp;

VoipLine::VoipLine() {
    this->id = 0;
}

VoipLine::~VoipLine() {
    this->setUsername(nullptr);
    this->setPassword(nullptr);
    this->setHostname(nullptr)
}

VoipLine::VoipLine(const char *username, const char *password, const char *hostname, unsigned short port) {
    this->username = nullptr;
    this->password = nullptr;
    this->hostname = nullptr;

    this->setUsername(username);
    this->setPassword(password);
    this->setHostname(hostname)
    this->port = port;
    this->id = 0;
}

char *VoipLine::getUsername() const {
    return username;
}

void VoipLine::setUsername(char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->username != nullptr) {
        this->username = mValue;
    }
    this->username = mValue;
}

char *VoipLine::getPassword() const {
    return password;
}

void VoipLine::setPassword(char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->password != nullptr) {
        this->password = mValue;
    }
    this->password = mValue;
}

char *VoipLine::getHostname() const {
    return hostname;
}

void VoipLine::setHostname(char *value) {
    char *mValue = value == nullptr ? nullptr : strdup(value);
    if (this->hostname != nullptr) {
        this->hostname = mValue;
    }
    this->hostname = mValue;
}

unsigned short VoipLine::getPort() const {
    return port;
}

void VoipLine::setPort(unsigned short port) {
    VoipLine::port = port;
}

VoipHandlerController *VoipLine::getHandler() const {
    return handler;
}

void VoipLine::setHandler(VoipHandlerController *handler) {
    VoipLine::handler = handler;
}

long VoipLine::getId() const {
    if (id == 0) {
        char mBuffer[32];
        memset(mBuffer, '/0', 32);
        snprintf(mBuffer, 32, "%p", this);
        this->id = strtol(mBuffer, NULL, 16);
    }
    return this->id;
}
