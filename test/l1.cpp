// Boost C++ Libraries
#include <boost/asio.hpp>
// Standard C++
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#define HOST_IP "192.168.0.120"
#define HOST_PORT 55000
#define REMOTE_IP "192.168.0.77"
#define REMOTE_MAC ""
#define REMOTE_NAME "Aura-Samsung"
#define APP_NAME "Aura-Gateway"
#define TV "LE32C650" // TV Model No.

#define temp_host "127.0.0.1"
#define temp_port 3000
#define temp_remote_mac "DC-41-A9-DA-9B-98" // control device's mac address
#define temp_remote_ip "192.168.1.101"

namespace SamsungLegacy {
    std::string encodeBase64(std::string);
    std::vector<std::string> generateRequestBody(std::string command, std::string remote_ip, std::string remote_mac);
    int sendCommandOverSocket(std::vector<std::string> payload, std::string host_ip, int host_port);
};

std::string SamsungLegacy::encodeBase64(std::string in) {
    
    const std::string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string out = "";
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

std::vector<std::string> SamsungLegacy::generateRequestBody(std::string command, std::string remote_ip = temp_remote_ip, std::string remote_mac = temp_remote_mac) {
    std::string src_64 = SamsungLegacy::encodeBase64(remote_ip);
    std::string mac_64 = SamsungLegacy::encodeBase64(remote_mac);
    std::string remote_64 = SamsungLegacy::encodeBase64(REMOTE_NAME);
    std::string app = APP_NAME;

    std::string command_64 = SamsungLegacy::encodeBase64(command);
    std::string tv = TV;

// Form authentication packet
    std::string auth_msg =
        std::string( { char(0x64), char(0x00) } ) + \
        std::string( { char(src_64.length()), char(0x00) } ) + src_64 + \
        std::string( { char(mac_64.length()), char(0x00) } ) + mac_64 + \
        std::string( { char(remote_64.length()), char(0x00) } ) + remote_64;
    
    std::string auth_pkt =
        std::string(1, char(0x00)) + \
        std::string( { char(app.length()), char(0x00) } ) + app + \
        std::string( { char(auth_msg.length()), char(0x00) } ) + auth_msg;
    
// Form command packet
    std::string cmd_msg =
        std::string(3, char(0x00)) + \
        std::string( { char(command_64.length()), char(0x00) } ) + command_64;
    
    std::string cmd_pkt =
        std::string(1, char(0x00)) + \
        std::string( { char(tv.length()), char(0x00) } ) + tv + \
        std::string( { char(cmd_msg.length()), char(0x00) } ) + cmd_msg;
    
    std::vector<std::string> request{auth_pkt, cmd_pkt};
    return request;
}

int SamsungLegacy::sendCommandOverSocket(std::vector<std::string> payload, std::string host_ip = temp_host, int host_port = temp_port) {

    // get IO Services
    boost::asio::io_service io_serv;
    // Asio Socket
    boost::asio::ip::tcp::socket socket(io_serv);
    // Make Socket Connection
    socket.connect(
        boost::asio::ip::tcp::endpoint(
            boost::asio::ip::address::from_string(host_ip), host_port
        )
    );
    // Error Handling
    boost::system::error_code error;

    for(std::string pkt : payload) {

        boost::asio::write(
            socket,
            boost::asio::buffer(pkt),
            error
        );

        if(!error) {
            std::cout << "\nSamsungLegacy:\n Sending: " << pkt << std::endl;
        }
        else {
            std::cout << "\nSamsungLegacy:\n socket write failed\n";
            return -1;
        }
    }
    sleep(0.25);
    socket.close();
    return 0;
}

int main(int argc, char **argv) {
    std::vector<std::string> v = SamsungLegacy::generateRequestBody("KEY_VOLUP");
    if(!v.empty()) {
        SamsungLegacy::sendCommandOverSocket(v);
    }
    return 0;
}