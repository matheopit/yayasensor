#ifndef MGCLIENTBASE_H
#define MGCLIENTBASE_H

#include <uv.h>
#include <string>
#include <core/mgbufferclient.h>

class MGClientBase : public IMGBufferClient
{
    friend class MGClientBasePriv;
public:
    virtual ~MGClientBase();
    MGClientBase();
    void sendData(const std::string& data)override;
    void sendData(const char* data, size_t nlen)override;
    virtual bool onDataAvailable(const char* buffer,size_t datalen)=0;
    virtual void onClientConnected()=0;
    virtual void onClientDisconnected(ssize_t status)=0;
    bool onTriggerCompleteData(const char* pzData, size_t nLen)override;
protected:
    virtual void onClientWrite(){}
private:
    void doSendData(const char* data, size_t nlen);
protected:
   uv_tcp_t * m_client;

};

#endif // MGCLIENTBASE_H
