#ifndef MGCONNHANDLE_H
#define MGCONNHANDLE_H

#include <uv.h>
#include  <string>
#include  <core/mgclientbase.h>



class MGRemoteBuffer;
class MGServerBase;
class MGConnHandle : public MGClientBase
{
    friend class MGServerBase;
    friend class MGPrivServerBase;
public:
    explicit MGConnHandle(uv_tcp_t* client,MGServerBase* server);
    virtual ~MGConnHandle();
    const std::string& clientId();
    bool onDataAvailable(const char* buffer,size_t datalen)override;  
protected:
    std::string m_id;
    MGServerBase* m_server;
    MGRemoteBuffer* m_buffer;
};

#endif // MGCONNHANDLE_H
