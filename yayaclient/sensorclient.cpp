#include "sensorclient.h"


#ifdef __arm__
#include <pi_2_dht_read.h>
#endif
#include "cmdbuilder.h"
#include  <time.h>

#ifndef __arm__
#define  DHT_SUCCESS 0
static int gettemp()
{
    return (rand() %  (37 - 9 + 1)) + 9;
}
static int gethumid()
{
    return (rand() %  (100 - 10 + 1)) + 10;
}

static int pi_2_dht_read(int /*type*/, int /*pin*/, float* humidity, float* temperature)
{
     *humidity = gettemp();
    *temperature = gethumid();
    return 0;
}

#endif

SensorClient::SensorClient(uv_loop_t * loop)
    :MGClient(loop)
{

}
SensorClient::~SensorClient()
{

}
bool SensorClient::onDataAvailable(const char* buffer,size_t datalen)
{
    std::string s(buffer,datalen);
    std::cout << s << std::endl;
}

void SensorClient::onClientConnected()
{
    getTemp();
}

void SensorClient::onClientDisconnected(ssize_t status)
{

}

void SensorClient::getTemp()
{
    CommandBuilder c("gettemp");
    c.getTemp(1,"2020-09-13 20:12:40","2020-09-13 20:14:40");
    this->sendData(c.buildcmd());
}

void SensorClient::setTemp()
{
    float humidity = 0.0;
    float temperature = 0.0;
    if (DHT_SUCCESS == pi_2_dht_read(22, 4,  &humidity,  &temperature))
    {
        CommandBuilder c("settemp");
        c.addMeasurement(1,humidity,temperature,time(NULL));
        this->sendData(c.buildcmd());
    }
}


void SensorClient::onClientWrite()
{
  //close();
}
