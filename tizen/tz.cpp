// Boost Libraries
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
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
    //std::string boostWebSocket(const char**, std::string, std::string);
    int boostWebSocket(const char**);
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
    std::string payload = "{'method': 'ms.remote.control', 'params': {'Cmd': 'Click', 'DataOfCmd': '" + command + "', 'Option': 'false', 'TypeOfRemote': 'SendRemoteKey'}}";
    return payload;
}

int SamsungTizen::boostWebSocket(const char **argv) {
    try
    {
        std::string host = argv[1];
        auto const port = argv[2];
        std::string samsungRemoteControlName = argv[3];
        auto const text = SamsungTizen::generateRequestBody(argv[4]);

        boost::asio::io_context ioc;

        boost::asio::ip::tcp::resolver resolver{ioc};
        boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws{ioc};

        auto const results = resolver.resolve(host, port);

        auto ep = boost::asio::connect(ws.next_layer(), results);

        host += ':' + std::to_string(ep.port());

        ws.set_option(boost::beast::websocket::stream_base::decorator(
            [](boost::beast::websocket::request_type& req)
            {
                req.set(boost::beast::http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-coro");
            }));

        // Perform the websocket handshake
        ws.handshake(host, "/api/v2/channels/samsung.remote.control?name=" + SamsungTizen::encodeBase64(samsungRemoteControlName));
//    std::string url = "ws://" + ip_addr + "/api/v2/channels/samsung.remote.control?name=" + SamsungTizen::encodeBase64(samsungRemoteControlName);


        // Send the message
        ws.write(boost::asio::buffer(std::string(text)));

        // This buffer will hold the incoming message
        boost::beast::flat_buffer buffer;

        // Read a message into our buffer
        ws.read(buffer);
        std::cout << boost::beast::make_printable(buffer.data()) << std::endl;
        sleep(1.5);
        // Close the WebSocket connection
        ws.close(boost::beast::websocket::close_code::normal);


    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(int argc, const char **args) {
    if(argc != 5) {
        std::cerr <<
            "Usage:\n ./tz <host> <port> <Remote-Control-Name> <Samsung-Command-Key>\n";
        //return EXIT_FAILURE;
    }
    else
        SamsungTizen::boostWebSocket(args);
    return 0;
}