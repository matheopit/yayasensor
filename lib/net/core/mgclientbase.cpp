#include "mgclientbase.h"
#include "mgutils.h"
#include <exception>
#include <cstdlib>
#include <cstring>
#include  "mgremotebuffer.h"
#define DBG printf

struct exchange_t
{
    void* tofree;
    void* client;
};

class MGClientBasePriv
{
public:
    static void on_client_write(uv_write_t *req, int /*status*/)
    {
        exchange_t * e = (exchange_t*)req->data;
        MGClientBase* cli = (MGClientBase*)e->client;
        cli->onClientWrite();
        free(e->tofree);
        if (req->data)
            free(req->data);
        free(req);
    }
};

MGClientBase::MGClientBase()
    :m_client(nullptr)
{

}

MGClientBase::~MGClientBase()
{

}

void MGClientBase::doSendData(const char* data, size_t nlen)
{
    if (nlen > 0 && data)
    {
        char* pzOutputData;
        uint32_t nOutputLen;
        MGRemoteBuffer::createChunckData(data, nlen, &pzOutputData, nOutputLen);
        uv_buf_t buf = uv_buf_init(pzOutputData,nOutputLen);
        uv_write_t *req = (uv_write_t *) malloc(sizeof(uv_write_t));
        exchange_t *e = (exchange_t *) malloc(sizeof(exchange_t));
        e->client = this;
        e->tofree = pzOutputData;
        req->data = e;
        uv_write(req,(uv_stream_t*)m_client, &buf, 1, MGClientBasePriv::on_client_write);
    }
}

void MGClientBase::sendData(const char* data, size_t nlen)
{
    doSendData(data,nlen);
}

void MGClientBase::sendData(const std::string& data)
{   
    size_t nlen = data.size();
    const char *p = data.c_str();
    doSendData(p,nlen);
}

bool MGClientBase::onTriggerCompleteData(const char* /*pzData*/, size_t/* nLen*/)
{
    return true;
}
