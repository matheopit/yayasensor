#include "sensorremotecli.h"
#include <mgcommanddecoder.h>

RemoteSensorClient::RemoteSensorClient(uv_tcp_t* client,MGServerBase *server)
    :MGConnHandle(client,server)
{

}

bool RemoteSensorClient::onTriggerCompleteData(const char* buffer,size_t datalen)
{
    BaseCommandPtr cmd = MGCommandDecoder::Instance()->unserializeCommand(buffer,datalen);
    if (cmd)
    {
        cmd->execute(this);
    }
    return true;
}

void RemoteSensorClient::onClientConnected()
{


}

void RemoteSensorClient::onClientDisconnected(ssize_t status)
{

}

