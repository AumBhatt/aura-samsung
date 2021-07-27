#include <iostream>
#include <string>

// Encode string -> base64

int main() {
    try {
        std::string test = "Aum";
        std::string out;
        const std::string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        int val=0, valb=-6;
        for (unsigned char c : test) {
            val = (val<<8) + c;
            valb += 8;
            while (valb>=0) {
                out.push_back(b[(val>>valb)&0x3F]);
                valb-=6;
            }
        }
        if (valb>-6) out.push_back(b[((val<<8)>>(valb+8))&0x3F]);
        while (out.size()%4) out.push_back('=');
        std::cout << out;
    }
    catch(std::exception &e) {
        std::cout << e.what();
    }
}