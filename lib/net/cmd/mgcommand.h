#ifndef MGCOMMAND_H
#define MGCOMMAND_H

#include <string>
#include <memory>
#include <jansson.h>
#include <core/mgbufferclient.h>

class BaseCommand;
typedef std::shared_ptr<BaseCommand> BaseCommandPtr;

class BaseCommand
{
    friend class MGCommandDecoder;
public:   
    BaseCommand(const std::string& cmdname,const  json_t  * jdata);
     virtual ~BaseCommand();
    virtual bool execute(IMGBufferClient*cli)=0;
    std::string commandName();
private:
    std::string m_cmdname;
};



#endif // MGCOMMAND_H
