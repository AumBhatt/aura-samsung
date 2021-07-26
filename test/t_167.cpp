#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

/* namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp> */

// Sends a WebSocket message and prints the response
int main(int argc, char** argv)
{
    try
    {
        std::string host = argv[1];
        auto const  port = argv[2];
        auto const  text = argv[3];

        // The io_context is required for all I/O
        boost::asio::io_context ioc;

        // These objects perform our I/O
        boost::asio::ip::tcp::resolver resolver{ioc};
        boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws{ioc};

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        auto ep = boost::asio::connect(ws.next_layer(), results);

        // Update the host_ string. This will provide the value of the
        // Host HTTP header during the WebSocket handshake.
        // See https://tools.ietf.org/html/rfc7230#section-5.4
        host += ':' + std::to_string(ep.port());

        // Set a decorator to change the User-Agent of the handshake
/*         ws.set_option(boost::beast::websocket::stream_base::decorator(
            [](boost::beast::websocket::request_type& req)
            {
                req.set(boost::beast::http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-coro");
            })); */
        
        // ws.next_layer().handshake(boost::asio::ssl::stream_base::client);

        // Perform the websocket handshake
        ws.handshake(host, "/");

        // Send the message
        ws.write(boost::asio::buffer(std::string(text)));

        // This buffer will hold the incoming message
        boost::beast::flat_buffer buffer;

        // Read a message into our buffer
        ws.read(buffer);

        // Close the WebSocket connection
        ws.close(boost::beast::websocket::close_code::normal);

        // If we get here then the connection is closed gracefully

        // The make_printable() function helps print a ConstBufferSequence
        std::cout << boost::beast::make_printable(buffer.data()) << std::endl;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}