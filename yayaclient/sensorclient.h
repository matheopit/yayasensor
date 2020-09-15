#ifndef SENSOR_CLIENT_H
#define SENSOR_CLIENT_H


#include <iostream>
#include <mgclient.h>

using namespace std;

class SensorClient;



class SensorClient: public MGClient
{
public:
    SensorClient(uv_loop_t * loop);
    ~SensorClient();
    bool onDataAvailable(const char* buffer,size_t datalen);
    virtual void onClientConnected();
    virtual void onClientDisconnected(ssize_t status);
    void getTemp();
    void setTemp();
protected:
    virtual void onClientWrite();
};




#endif
