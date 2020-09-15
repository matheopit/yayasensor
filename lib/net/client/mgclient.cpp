#include "mgclient.h"
#include <core/mgutils.h>
#include <exception>
#include <cstdlib>
#include <cstring>
#include  <core/mgremotebuffer.h>


static void on_dataAvailable(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf)
{
    MGClient* cli =  static_cast<MGClient*>(stream->data);
    cli->onTriggerDataAvailable(stream, nread, buf);
}

static void on_connect(uv_connect_t* req, int status)
{
    if (status < 0)
    {
        char p[100] = "";
        sprintf(p, "%s, error:[%d]\n", uv_strerror(status),status);
        throw MGErrorBase(p);
    }
    MGClientBase* cli =  static_cast<MGClientBase*>(req->data);
    cli->onClientConnected();
    uv_read_start( req->handle, mg_alloc_buffer,on_dataAvailable);
}


MGClient::MGClient(uv_loop_t * loop)
    :MGClientBase()
{
    m_buffer = new MGRemoteBuffer(this);
    try
    {
        m_client =(uv_tcp_t*)malloc(sizeof(uv_tcp_t));
        uv_tcp_init(loop, m_client);
        m_client->data = this;
        m_cliconnect.data = this;
        struct sockaddr_in dest;
        uv_ip4_addr(DEFAULT_SRV_ADDR, DEFAULT_PORT, &dest);
        uv_tcp_connect(&m_cliconnect, m_client, (const struct sockaddr*)&dest, on_connect);
    }
    catch (MGErrorBase& e)
    {
        abort();
    }
}

MGClient::~MGClient()
{
    close();

}

void MGClient::onTriggerDataAvailable(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf)
{
    if (nread < 0)
    {
        onClientDisconnected(nread);
        uv_close((uv_handle_t*)stream, nullptr);
    }
    else
    {
        if (stream->data && buf->base)
        {

            if (! m_buffer->decodeChunckData(buf->base,nread))
            {
                //kick client
                printf("Client proto read error\n");
                uv_close((uv_handle_t*)stream, nullptr);

            }
        }
    }
    if (buf->len > 0 && buf->base)
        free(buf->base);
}

bool MGClient::onTriggerCompleteData(const char* pzData, size_t nLen)
{
    onDataAvailable(pzData,nLen);

}
void MGClient::close()
{
    if (m_client)
    {
        uv_close(( uv_handle_t*)m_client,NULL);
        free(m_client);
        m_client = nullptr;
    }
}

