#ifndef MGBUFFERSHARED_H
#define MGBUFFERSHARED_H
#include <string.h>

class IMGBufferClient
{
public:
    virtual bool onTriggerCompleteData(const char* pzData, size_t nLen)=0;
    virtual void sendData(const std::string& data)=0;
    virtual void sendData(const char* data, size_t nlen)=0;
};
#endif // MGBUFFERSHARED_H
