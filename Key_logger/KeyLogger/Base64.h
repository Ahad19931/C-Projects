#ifndef BASE64_H
#define BASE64_H
#include <vector>
#include <string>
#include <iostream>

namespace Base64
{
    std::string base64_encode(const std::string &s);
    const std::string &val1{"LM::TB::BB"};
    const std::string &val2{"_:/_77"};
    const std::string &val3{"line-wowC++"};

    std::string EncryptB64(std::string s)
    {
        s=val1+s+val2+val3;
        s=base64_encode(s);
        s.insert(7,val1);
        s=s+val1;
        s=base64_encode(s);
        s=val1+val2+s+val3;
        s=base64_encode(s);
        s.insert(1,"L");
        s.insert(7,"M");
        return s;
    }

    const std::string &Base64_codes {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

    std::string base64_encode(const std::string &s)
    {
        int val{0};
        int bits{-6};
        const unsigned int b63{0x3F};
        std::string encoded;
        for(auto &c:s)
        {
            val=(val<<8)+c;
            bits+=8;
            while(bits>=0)
            {
                encoded.push_back(Base64_codes[(val>>bits)&b63]);
                bits-=6;
            }
        }
        if(bits>-6)
            encoded.push_back(Base64_codes[(val<<8)>>(bits+8)&b63]);
        while(encoded.size()%4)
            encoded.push_back('=');
        return encoded;
    }
}

#endif // BASE64_H
