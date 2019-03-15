//
// Created by sobrito on 22/02/2019.
//

#include "../common/CommonBuildLibrary.h"
#include <i9corp/voip/tools/VoipTools.h>
#include <string>
#include <regex>
#include <string.h>
using namespace i9corp;

char *VoipTools::getPhoneNumberFromUri(const char *value) {
    if (value == nullptr) {
        return nullptr;
    }
    std::string subject(value);
    std::string result;
    try {
        std::regex re("<*sip:([0-9A-Za-z#]+)@.+");
        std::smatch match;
        if (std::regex_search(subject, match, re) && match.size() > 1) {
            result = match.str(1);
        } else {
            result = std::string("");
        }
    } catch (std::regex_error &e) {
        return nullptr;
    }
    if (result.length() == 0) {
        return nullptr;
    }
    return strdup(result.c_str());
}


long VoipTools::getLongId(const void *reference) {
    char mBuffer[32];
    memset(mBuffer, '\0', 32);
    snprintf(mBuffer, 32, "%p", reference);
    return strtol(mBuffer, NULL, 16);
}
