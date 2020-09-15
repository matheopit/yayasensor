#ifndef CMD_BUILDER_H
#define CMD_BUILDER_H

#include <string>
#include <jansson.h>
#include <string>

class CommandBuilder
{
public:
    CommandBuilder(const std::string& command);
    virtual ~CommandBuilder();
    void addMeasurement(int id, float t ,float h,time_t timestamp);
    void addMeasurement(int id, float t ,float h,const std::string& timestamp);
    void getTemp(int id,const std::string& startdate,const std::string& endDate);
    std::string buildcmd();
private:
    json_t * m_root;
    json_t *m_json_arr;
};


#endif
