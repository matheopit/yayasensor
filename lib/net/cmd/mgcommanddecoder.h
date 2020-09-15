#ifndef MGCOMMANDDECODER_H
#define MGCOMMANDDECODER_H

#include <jansson.h>
#include "mgcommand.h"
#include <map>
#include "mgbasicsingleton.h"
#include <jansson.h>

typedef BaseCommandPtr (*createCmd_cb)(const std::string&,json_t * t);
typedef std::map<std::string,createCmd_cb> TCmdTable;

class MGCommandDecoder :public  MGBasicSingleton<MGCommandDecoder>
{
    friend class MGBasicSingleton<MGCommandDecoder>;
 MGCommandDecoder();
public:   
    BaseCommandPtr unserializeCommand(const char*, size_t commandlen);
    void registerCommand(const std::string& cmd,createCmd_cb func);
    void triggerUnknowCommand();
private:
    createCmd_cb findCommand(const std::string&);
    TCmdTable m_cmdTable;
};

#endif // MGCOMMANDDECODER_H
