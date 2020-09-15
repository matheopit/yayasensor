#ifndef MGCLIENT_H
#define MGCLIENT_H

#include <uv.h>
#include <string>
#include <core/mgclientbase.h>
#include <core/mgbufferclient.h>

class MGRemoteBuffer;
class MGClient : public MGClientBase
{
public:
    MGClient(uv_loop_t * loop);
    virtual ~MGClient();
    void onTriggerDataAvailable(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf);
    bool onTriggerCompleteData(const char* pzData, size_t nLen)override;
    void close();
private:
   uv_connect_t m_cliconnect;
   MGRemoteBuffer* m_buffer;
};

#endif // MGCLIENT_H
