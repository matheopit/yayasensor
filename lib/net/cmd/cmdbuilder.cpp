#include "cmdbuilder.h"
#include <string>
#include <jansson.h>



CommandBuilder::CommandBuilder(const std::string &command)
    :m_root(nullptr)
    ,m_json_arr(nullptr)
{
    m_root = json_object();
    m_json_arr = json_array();
    json_object_set_new( m_root, "cmd", json_string(command.c_str()));
    json_object_set_new( m_root, "data", m_json_arr );
}

CommandBuilder::~CommandBuilder()
{
    json_decref(m_root);
}

void CommandBuilder::addMeasurement(int id, float t, float h, time_t timestamp)
{
    json_t *jmesure = json_object();
    json_object_set_new( jmesure, "id", json_integer(id));
    json_object_set_new( jmesure, "d", json_integer(timestamp));
    json_object_set_new( jmesure, "t", json_real(t));
    json_object_set_new( jmesure, "h", json_real(h));
    json_array_append( m_json_arr,jmesure);
}

void CommandBuilder::addMeasurement(int id, float t, float h, const std::string &timestamp)
{
    json_t *jmesure = json_object();
    json_object_set_new( jmesure, "id", json_integer(id));
    json_object_set_new( jmesure, "d", json_string(timestamp.c_str()));
    json_object_set_new( jmesure, "t", json_real(t));
    json_object_set_new( jmesure, "h", json_real(h));
    json_array_append( m_json_arr,jmesure);
}

void CommandBuilder::getTemp(int id, const std::string &startdate, const std::string &endDate)
{
    json_t *getTempj = json_object();
    json_object_set_new( getTempj, "id", json_integer(id));
    json_object_set_new( getTempj, "start", json_string(startdate.c_str()));
    json_object_set_new( getTempj, "end", json_string(endDate.c_str()));
    json_array_append( m_json_arr,getTempj);
}

std::string CommandBuilder::buildcmd()
{
    char* s = NULL;
     s = json_dumps(m_root, 0);
     std::string result(s);
     if (s)
         free(s);
     return result;
}
