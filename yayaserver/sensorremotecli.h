#ifndef SENSOR_REMOTECLIENT_H
#define SENSOR_REMOTECLIENT_H


#include <iostream>
#include <uv.h>
#include <mgconnhandle.h>

using namespace std;
class MGServerBase;

class RemoteSensorClient : public MGConnHandle
{
public:
    RemoteSensorClient(uv_tcp_t* client,MGServerBase *server);
    bool onTriggerCompleteData(const char* buffer,size_t datalen);
    void onClientConnected();
    void onClientDisconnected(ssize_t status);
};



#endif
