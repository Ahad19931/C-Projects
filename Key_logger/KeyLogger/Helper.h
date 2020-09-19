#ifndef HELPER_H
#define HELPER_H
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>

namespace Helper
{
    template <typename T>
    std::string Tostring(const T &obj);
    struct DateTime
    {
        int d,m,y,M,H,S;
        DateTime()
        {
            time_t s;
            time(&s);
            struct tm *info=localtime(&s);
            d=info->tm_mday;
            m=info->tm_mon+1;
            y=1900+info->tm_year;
            M=info->tm_min;
            H=info->tm_hour;
            S=info->tm_sec;
        }
        DateTime(int d,int m,int y,int H,int M,int S)
            :d(d),m(m),y(y),H(H),M(M),S(S) {}
        DateTime(int d,int m,int y)
            :d(d),m(m),y(y),H(0),M(0),S(0) {}
        DateTime Now() const
        {
            return DateTime();
        }

        std::string GetDateString() const
        {
            return std::string(d<10 ? "0":"")+Tostring(d)
                   +std::string(m<10 ? ".0":".")+Tostring(m)
                   +"."+Tostring(y);
        }
        std::string GetTimeString(const std::string &sep=":") const
        {
            return std::string(H<10 ? "0":"")+Tostring(H)+sep+
                   std::string(M<10 ? "0":"")+Tostring(M)+sep+
                   std::string(S<10 ? sep:"")+Tostring(S);
        }
        std::string GetDateTimeString(const std::string &sep=":") const
        {
            return GetDateString()+" "+GetTimeString(sep);
        }
    };

    template <typename T>
    std::string Tostring(const T &obj)
    {
        std::stringstream ss;
        ss<<obj;
        return ss.str();
    }

    void WriteAppLog(const std::string &s)
    {
        std::ofstream file("AppLog.txt",std::ios::app);
        file<<"["<<Helper::DateTime().GetDateTimeString()<<"]"
        <<"\n"<<s<<std::endl<<"\n";
        file.close();
    }
}


#endif // HELPER_H
