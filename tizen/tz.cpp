// Poco Libraries
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/WebSocket.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
// RapidJSON Libraries
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
// Standard C++ Libraries
#include <iostream>
#include <exception>
#include <sstream>

namespace SamsungTizen {
    std::string encodeBase64(std::string);
    std::string generateRequestBody(std::string);
};

std::string SamsungTizen::encodeBase64(std::string in) {
    
    const std::string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string out;
    int val=0, valb=-6;

    for (unsigned char c : in) {
        val = (val<<8) + c;
        valb += 8;
        while (valb>=0) {
            out.push_back(b[(val>>valb)&0x3F]);
            valb-=6;
        }
    }
    if (valb>-6) out.push_back(b[((val<<8)>>(valb+8))&0x3F]);
    while (out.size()%4) out.push_back('=');
    return out;

}

std::string SamsungTizen::generateRequestBody(std::string command) {
    std::string payload = "{'method': 'ms.control.control', 'params': {'Cmd': 'Click', 'DataOfCmd': '" + command + "', 'Option': 'false', 'TypeOfRemote': 'SendRemoteKey'}}";
    return payload;
}

int main() {
    std::cout << SamsungTizen::generateRequestBody("hi") << std::endl;
}