#include "mgconnhandle.h"
#include <cstdlib>
#include <cstring>
#include <core/mgutils.h>
#include "mgserverbase.h"
#include <core/mgremotebuffer.h>

MGConnHandle::MGConnHandle(uv_tcp_t* client,MGServerBase* server)
    :MGClientBase()
    ,m_server(server)

{
    m_buffer = new MGRemoteBuffer(this);
    m_client = client;   
}

MGConnHandle::~MGConnHandle()
{

}
bool MGConnHandle::onDataAvailable(const char* buffer,size_t datalen)
{
    return m_buffer->decodeChunckData(buffer,datalen);
}

const std::string& MGConnHandle::clientId()
{
    return m_id;
}



