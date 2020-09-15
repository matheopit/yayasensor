#ifndef SENSOR_CMD_DB_H
#define SENSOR_CMD_DB_H


#include <iostream>
#include <mgcommand.h>


class SensorDBCmd : public BaseCommand
{
public:
    SensorDBCmd(const std::string& cmdname,const  json_t  * jdata);
    virtual ~SensorDBCmd();
    virtual bool execute(IMGBufferClient*cli);
private:
    double m_t;
    double m_h;
    int m_idprobe;
};

class SensorQueryDBCmd : public BaseCommand
{
public:
    SensorQueryDBCmd(const std::string& cmdname,const  json_t  * jdata);
    virtual ~SensorQueryDBCmd();
    virtual bool execute(IMGBufferClient*cli);
private:
    std::string m_startdate;
    std::string m_enddate;
    int m_idprobe;
};


BaseCommandPtr SensorDBCmdCreate(const std::string&,json_t * t);
BaseCommandPtr SensorDBQueryCreate(const std::string&,json_t * t);
#endif
