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

int main() {

    std::string url = "ws://echo.websocket.org";

    Poco::URI uri(url);
    Poco::Net::HTTPClientSession clientSession(uri.getHost());

    std::string path(uri.getPathAndQuery());
    if(path.empty()) {
        path = '/';
    }

    Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, path, Poco::Net::HTTPMessage::HTTP_1_1);

    Poco::Net::HTTPResponse res;

    try {
        Poco::Net::WebSocket *wbsock =  new Poco::Net::WebSocket(clientSession, req, res);
        char const *message="Hello echo websocket!";
        char receiveBuff[256];

        int sentLength = wbsock->sendFrame(message, strlen(message), Poco::Net::WebSocket::FRAME_TEXT);
        std::cout << "Sent bytes " << sentLength << std::endl;
        int flags = 0;

        int recLength = wbsock->receiveFrame(receiveBuff, 256, flags);
        std::cout << "Received bytes " << recLength << std::endl;
        std::cout<<receiveBuff<<std::endl;

        wbsock->close();
    }
    catch(std::exception &e) {
        std::cout<<"\nException: "<<e.what()<<"\n";
    }

}