#ifndef CT_MGR_INSERER_HPP
#define CT_MGR_INSERER_HPP
#include <string>
#include <set>
#include <map>
#include "ctmgrdatabase.hpp"


struct sqlite3;
struct sqlite3_stmt;

class CommandBuilder;

struct TDBVersionInfo
{
    int m_numversion;
    std::string m_szintescript;
};

class CTManagerDataBase : public CTAbsManagerDataBase
{
public:
    virtual ~CTManagerDataBase();
    CTManagerDataBase(const char* szDataBaseName);
    int readVersion(TDBVersionInfo& pversion);
    int getLastAutoInc(const char* ptablename,int nlen)const;
    bool insertMeasure(int idsonde,double temperature,double humididty);
    bool Measure(int idsonde,double temperature,double humididty);
    CommandBuilder* getMeasure(const std::string& startDate,const std::string& endDate,int idsensor=-1);
private:
    CTManagerDataBase();
    CTManagerDataBase(const CTManagerDataBase&);
    CTManagerDataBase& operator=(const CTManagerDataBase&);
private:
    sqlite3_stmt * m_statement;
};


#endif /* CT_MGR_INSERER_HPP */
