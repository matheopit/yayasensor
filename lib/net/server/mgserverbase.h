#ifndef MGSERVERBASE_H
#define MGSERVERBASE_H

#include <string>
#include  <uv.h>
#include <vector>
#include <core/mgutils.h>
#include  <core/mgbufferclient.h>

class MGConnHandle;
class MGServerBase
{
public:
    friend class MGPrivServerBase;
    MGServerBase(uv_loop_t* uv,const std::string& localaddr="0.0.0.0",int localport=DEFAULT_PORT);
    virtual ~MGServerBase();
    virtual void onNewConnection(int status, const std::string & ClientID) = 0;
    virtual void onDisconnect(const std::string & ClientID) = 0;
    virtual void onClientDisconnected(ssize_t status, const std::string & ClientID)=0;
    size_t clientCounts() const;
    MGConnHandle *operator[](size_t i);
protected:
    virtual MGConnHandle* createNewConnection(uv_tcp_t *client)=0;
private:
    bool removeClient(MGConnHandle* conhandle);
    void onTriggerNewConnection(uv_stream_t* server, int status);
    void onTriggerDataAvailable(MGConnHandle* client,uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf);

private:    
    uv_tcp_t m_srvhandle;
    std::vector<MGConnHandle*>m_clientlist;    
};

#endif // MGSERVERBASE_H
