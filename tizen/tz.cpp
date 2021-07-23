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
    std::string pocoWebSocket(std::string, std::string, std::string);
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

std::string SamsungTizen::pocoWebSocket(std::string ip_addr, std::string samsungRemoteControlName, std::string commandKey) {
    
    std::string url = "ws://" + ip_addr + "/api/v2/channels/samsung.remote.control?name=" + SamsungTizen::encodeBase64(samsungRemoteControlName);
    std::string urlTest = "wss://echo.websocket.org";

    Poco::URI uri(url);
    std::cout << uri.toString() << std::endl;
    Poco::Net::HTTPClientSession clientSession(uri.getHost());

    std::string path(uri.getPathAndQuery());
    if(path.empty()) {
        path = '/';
    }

    Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, path, Poco::Net::HTTPMessage::HTTP_1_1);

    Poco::Net::HTTPResponse res;

    try {
        Poco::Net::WebSocket *wbsock =  new Poco::Net::WebSocket(clientSession, req, res);
        char const *message = commandKey.c_str();
        char receiveBuff[256];

        int sentLength = wbsock->sendFrame(message, strlen(message), Poco::Net::WebSocket::FRAME_TEXT);
        std::cout << "Sent bytes " << sentLength << std::endl;
        int flags = 0;

        int recLength = wbsock->receiveFrame(receiveBuff, 256, flags);
        std::cout << "Received bytes " << recLength << std::endl;
        std::cout << "Received Message: " << receiveBuff << std::endl;

        wbsock->close();
    }
    catch(std::exception &e) {
        std::cout<<"\nException: "<<e.what()<<"\n";
    }
    return "";
}

int main(int argc, const char **args) {
    SamsungTizen::pocoWebSocket(args[1], "samXYZ", "KEY_UP");
    return 0;
}