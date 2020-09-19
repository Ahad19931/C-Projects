#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

const std::string &val1 = "LM::TB::BB";
const std::string &val2 = "__:/__77";
const std::string &val3 = "line=wowC++";
const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string DecryptB64(std::string s);
std::string base64_decode(const std::string &s);

int main(int argc, char *argv[])
{
    if(argc!=3)
        return std::cout<<"Program needs two arguments, i/p and o/P"<<std::endl,2;
    std::string in(argv[1]),out(argv[2]);
    std::ifstream fi(in);
    if(!fi)
        return std::cout<<"Cannot read i/p file '"<<in<<"'"<<std::endl,3;
    std::string data;
    fi>>data;
    if(!fi)
        return std::cout<<"I/p file '"<<in<<"' corrupted!"<<std::endl,4;
    data=DecryptB64(data);
    std::ofstream fo(out);
    if(!fo)
        return std::cout<<"Cannot write o/p file '"<<out<<"'"<<std::endl,5;
    fo<<data;
    std::cout<<"Decoding was successful"<<std::endl;
    return 0;
}

std::string base64_decode(const std::string &s)
    {
        std::string decoded;
        std::vector<int> vec(256, -1);
        for (int i = 0; i < 64; i++)
            vec [BASE64_CODES[i]] = i;
        int val = 0, bits = -8;
        for (const auto &c : s)
            {
                if (vec[c] == -1) break;
                val = (val << 6) + vec[c];
                bits += 6;

                if (bits >= 0)
                    {

                        decoded.push_back(char((val >> bits) & 0xFF));
                        bits -= 8;
                    }
            }

        return decoded;
    }


std::string DecryptB64(std::string s)
    {
        s = s.erase (7, 1);
        s = s.erase (1, 1);
        s = base64_decode (s);
        s = s.substr (val2.length() + val3.length());
        s = s.substr (0, s.length() - val1.length());
        s = base64_decode (s);
        s = s.substr (0, s.length() - val1.length());
        s = s.erase (7, val3.length());
        s = base64_decode (s);
        s = s.substr (val1.length());
        s = s.substr (0, s.length() - val2.length() - val3.length());
        return s;
    }
