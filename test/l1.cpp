// Boost C++ Libraries
#include <boost/asio.hpp>
// Standard C++
#include <iostream>
#include <string>
#include <vector>

#define HOST_IP "192.168.0.120"
#define HOST_PORT 55000
#define REMOTE_IP "192.168.0.77"
#define REMOTE_MAC ""
#define REMOTE_NAME "Aura-Samsung"
#define APP_NAME "Aura-Gateway"
#define TV "LE32C650" // TV Model No.

#define temp_host "127.0.0.1"
#define temp_port 3000
#define temp_mac "DC-41-A9-DA-9B-98" // control device's mac address
#define temp_remote_ip "192.168.1.101"

namespace SamsungLegacy {
    std::string encodeBase64(std::string);
    std::vector<std::string> generateRequestBody(std::string, std::string, std::string);
    int sendCommandOverSocket(std::vector<std::string>, std::string, std::string);
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

std::vector<std::string> SamsungLegacy::generateRequestBody(std::string command, std::string remote_ip = REMOTE_IP, std::string remote_mac = REMOTE_MAC) {
    std::string src_64 = SamsungLegacy::encodeBase64(remote_ip);
    std::string mac_64 = SamsungLegacy::encodeBase64(remote_mac);
    std::string remote_64 = SamsungLegacy::encodeBase64(REMOTE_NAME);
    std::string app = APP_NAME;

    std::string command_64 = SamsungLegacy::encodeBase64(command);
    std::string tv = TV;

    std::string auth_msg =
        std::string( { char(0x64), char(0x00) } ) + \
        std::string( { char(src_64.length()), char(0x00) } ) + src_64 + \
        std::string( { char(mac_64.length()), char(0x00) } ) + mac_64 + \
        std::string( { char(remote_64.length()), char(0x00) } ) + remote_64;
    
    std::string auth_pkt =
        std::string(1, char(0x00)) + \
        std::string( { char(app.length()), char(0x00) } ) + app + \
        std::string( { char(auth_msg.length()), char(0x00) } ) + auth_msg;
    
    std::string cmd_msg =
        std::string(3, char(0x00)) + \
        std::string( { char(command_64.length()), char(0x00) } ) + command_64;
    
    std::string cmd_pkt =
        std::string(1, char(0x00)) + \
        std::string( { char(tv.length()), char(0x00) } ) + tv + \
        std::string( { char(cmd_msg.length()), char(0x00) } ) + cmd_msg;
    
    std::vector<std::string> request;
    request.push_back(auth_pkt);
    request.push_back(cmd_pkt);

    return request;
}

int sendCommandOverSocket(std::vector<std::string> payload, std::string host_ip = HOST_IP, std::string host_port = HOST_PORT) {}

int main(int argc, char **argv) {
    std::vector<std::string> v = SamsungLegacy::generateRequestBody("KEY_VOLUP", temp_host, temp_mac);
    for(std::string i : v) {
        std::cout << i <<std::endl;
    }
    return 0;
}