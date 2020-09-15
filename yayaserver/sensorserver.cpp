#include "sensorserver.h"
#include  "sensorremotecli.h"
#include "mgcommanddecoder.h"
#include "sensorcmddb.h"
SensorServer::SensorServer(uv_loop_t* uv):MGServerBase(uv)
{
    MGCommandDecoder::Instance()->registerCommand("settemp",SensorDBCmdCreate);
    MGCommandDecoder::Instance()->registerCommand("gettemp",SensorDBQueryCreate);
}

void SensorServer::onDisconnect(const std::string & ClientID)
{

}

void SensorServer::onNewConnection(int status, const std::string & clientID)
{
    printf("onNewConnection [%d,%s]\n",status,clientID.c_str());
}

void SensorServer::onClientDisconnected(ssize_t status,const std::string &/*clientID*/)
{
    printf("Disconnected %d\n",status);
}

MGConnHandle* SensorServer::createNewConnection(uv_tcp_t *client)
{
    return new RemoteSensorClient(client,this);
}





