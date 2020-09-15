#include "sensorcmddb.h"
#include "ctmgrdb.hpp"
#include  "cmdbuilder.h"

#define DB_PATH "~/devel/raspdev/yayasensor/db/dbweather.db"

SensorDBCmd::SensorDBCmd(const std::string& cmdname,const  json_t  * jdata)
    :BaseCommand(cmdname,jdata)
{
    json_t* jarr = json_array_get(jdata,0);
    if (!jarr)
        return;
    json_t * jt  = json_object_get(jarr,"id");
    if (json_is_integer(jt))
    {
        m_idprobe  =  json_integer_value(jt);
    }
    jt  = json_object_get(jarr,"t");
    if (json_is_real(jt))
    {
        m_t  =   json_real_value(jt);
    }
    jt  = json_object_get(jarr,"h");
    if (json_is_real(jt))
    {
        m_h  =   json_real_value(jt);
    }
}

SensorDBCmd::~SensorDBCmd()
{

}

bool SensorDBCmd::execute(IMGBufferClient*cli)
{
    CTManagerDataBase d(DB_PATH);
    d.insertMeasure(m_idprobe,m_t,m_h);
    return true;
}



SensorQueryDBCmd::SensorQueryDBCmd(const std::string& cmdname,const  json_t  * jdata)
    :BaseCommand(cmdname,jdata)
    ,m_idprobe(-1)
{
    json_t* jarr = json_array_get(jdata,0);
    if (!jarr)
        return;
    json_t * jt = json_object_get(jarr,"id");
    if (jt && json_is_integer(jt))
    {
        m_idprobe =  json_integer_value(jt);
    }
    jt  = json_object_get(jarr,"start");
    if (json_is_string(jt))
    {
        m_startdate =  json_string_value(jt);
    }
    jt  = json_object_get(jarr,"end");
    if (json_is_string(jt))
    {
        m_enddate = json_string_value(jt);
    }
}

SensorQueryDBCmd::~SensorQueryDBCmd()
{

}

bool SensorQueryDBCmd::execute(IMGBufferClient*cli)
{
    CTManagerDataBase d(DB_PATH);
    CommandBuilder * c = d.getMeasure(m_startdate,m_enddate,m_idprobe);
    cli->sendData(c->buildcmd());
    return true;
}








BaseCommandPtr SensorDBCmdCreate(const std::string &cmd, json_t *t)
{
    return BaseCommandPtr(new SensorDBCmd(cmd,t));
}
BaseCommandPtr SensorDBQueryCreate(const std::string &cmd, json_t *t)
{
    return BaseCommandPtr(new SensorQueryDBCmd(cmd,t));
}
