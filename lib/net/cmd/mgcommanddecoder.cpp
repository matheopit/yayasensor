#include "mgcommanddecoder.h"



MGCommandDecoder::MGCommandDecoder()
{

}

BaseCommandPtr MGCommandDecoder::unserializeCommand(const char* buffer, size_t commandlen)
{
    BaseCommandPtr cmd;
    json_error_t err;
    json_t* root = json_loadb(buffer,commandlen,0,&err);
    if (!root)
        return cmd;
    json_t * t  = json_object_get(root,"cmd");
    if (json_is_string(t))
    {
        const char* p =   json_string_value(t);
        std::string command(p);
        createCmd_cb func =  findCommand(command);
        if (func)
        {
            json_t * jdata  = json_object_get(root,"data");
            if (jdata)
                cmd = (func)(command,jdata);
            return cmd;
        }

    }
    json_decref(root);
    return cmd;
}

void MGCommandDecoder::registerCommand(const std::string &cmd, createCmd_cb func)
{
    m_cmdTable[cmd] = func;
}

void MGCommandDecoder::triggerUnknowCommand()
{

}

createCmd_cb MGCommandDecoder::findCommand(const std::string& command)
{
    createCmd_cb func = nullptr;
    TCmdTable::const_iterator it = m_cmdTable.find(command);
    if (it != m_cmdTable.end())
        func  = it->second;
    return func;
}



