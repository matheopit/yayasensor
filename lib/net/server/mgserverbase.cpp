#include "mgserverbase.h"
#include <uv.h>

#include <string>
#include <memory>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include  <mgconnhandle.h>
#include <vector>
#include  <exception>
#include  <mgconnhandle.h>


#define  DBG fprintf

class MGPrivServerBase
{
public:
    static void triggerNewConnection(uv_stream_t* server, int status);
    static void triggerDataAvailable(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf);
    static void closeConnection(uv_handle_t* handle);
};



void MGPrivServerBase::triggerNewConnection(uv_stream_t* server, int status)
{
    MGServerBase* serv = static_cast<MGServerBase*>(server->data);
    serv->onTriggerNewConnection(server,status);
}

void MGPrivServerBase::triggerDataAvailable(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf)
{

    MGConnHandle* conhandle = static_cast<MGConnHandle*>(stream->data);
    MGServerBase* serv = conhandle->m_server;
    serv->onTriggerDataAvailable(conhandle,stream, nread, buf);
}


void MGPrivServerBase::closeConnection(uv_handle_t* handle)
{
    free(handle);
}

void MGServerBase::onTriggerNewConnection(uv_stream_t* server, int status)
{
    if (status < 0)
    {
        char p[100] = "";
        sprintf(p, "%s, error:[%d]\n", uv_strerror(status),status);
        throw MGErrorBase(p);
    }
    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*)client) == 0)
    {
        MGConnHandle * conhandle = createNewConnection(client);
        this->m_clientlist.push_back(conhandle);
        client->data = conhandle;
        uv_read_start((uv_stream_t*) client, mg_alloc_buffer,MGPrivServerBase::triggerDataAvailable);
        onNewConnection(status,conhandle->clientId());
        conhandle->onClientConnected();
    }
    else {
        uv_close((uv_handle_t*) client, nullptr);
    }
}

bool MGServerBase::removeClient(MGConnHandle* conhandle)
{
    std::vector<MGConnHandle*>::iterator itb = m_clientlist.begin();
    std::vector<MGConnHandle*>::iterator ite = m_clientlist.end();
    while (itb != ite)
    {
        if ((*itb) == conhandle)
        {
            uv_close((uv_handle_t*)(*itb)->m_client, MGPrivServerBase::closeConnection);
            m_clientlist.erase(itb);
            delete conhandle;
            return true;
        }
        ++itb;
    }
    return false; //LEAK
}



void MGServerBase::onTriggerDataAvailable(MGConnHandle* conhandle,uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf)
{
    if (nread < 0)
    {     
        onClientDisconnected(nread,conhandle->clientId());
        conhandle->onClientDisconnected(nread);
        if (!removeClient(conhandle))
        {
            uv_close((uv_handle_t*)stream, MGPrivServerBase::closeConnection);
        }
    }
    else if (buf->base)
    {

        if (!conhandle->onDataAvailable(buf->base,nread))
        {
            //kick client
            printf("Client proto read error\n");
            if (!removeClient(conhandle))
            {
                uv_close((uv_handle_t*)stream, MGPrivServerBase::closeConnection);
            }
        }
    }
    if (buf->len > 0 && buf->base)
        free(buf->base);
}



size_t MGServerBase::clientCounts() const
{
    return m_clientlist.size();
}

MGConnHandle* MGServerBase::operator[](size_t i)
{
    if (i >= 0 && i < m_clientlist.size())
        return m_clientlist.at(i);
    return nullptr;
}

MGServerBase::MGServerBase(uv_loop_t* uv,const std::string& localaddr,int localport)
{
    try
    {
        uv_tcp_init(uv,&m_srvhandle);
        m_srvhandle.data = this;
        struct sockaddr_in addr;
        uv_ip4_addr(localaddr.c_str(), localport, &addr);
        uv_tcp_bind(&m_srvhandle, (const struct sockaddr*)&addr, 0);
        int r = uv_listen((uv_stream_t*) &m_srvhandle, 10, MGPrivServerBase::triggerNewConnection);
        if (r) {
            char p[100]="";
            sprintf(p,"Listen error %s", uv_strerror(r));
            throw MGErrorBase(p);

        }
    }
    catch (MGErrorBase& e)
    {
        DBG(stderr, "Error[%s]\n",  e.what());
        abort();
    }
}

MGServerBase::~MGServerBase()
{

}
