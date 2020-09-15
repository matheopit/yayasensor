#ifndef SENSOR_SERVER_H
#define SENSOR_SERVER_H


#include <iostream>
#include <mgserverbase.h>

using namespace std;

class SensorServer : public MGServerBase
{
public:
    SensorServer(uv_loop_t* uv);
    void onDisconnect(const std::string & ClientID);
    void onNewConnection(int status, const std::string & clientID) override;
    void onClientDisconnected(ssize_t status,const std::string &/*clientID*/)override;
    MGConnHandle* createNewConnection(uv_tcp_t *client)override;

};


#endif
