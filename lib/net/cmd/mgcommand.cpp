#include "mgcommand.h"

BaseCommand::BaseCommand(const std::string& name,const json_t*/*jdata*/)
    :m_cmdname(name)
{

}

BaseCommand::~BaseCommand()
{

}

std::string BaseCommand::commandName()
{
    return m_cmdname;
}



