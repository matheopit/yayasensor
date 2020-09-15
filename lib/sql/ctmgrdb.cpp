#include "ctmgrdb.hpp"
#include <assert.h>
#include <sqlite3.h>
#include <set>
#include <time.h>
#include <cmdbuilder.h>


CTManagerDataBase::CTManagerDataBase(const char* szDataBaseName)
    : CTAbsManagerDataBase(szDataBaseName)
{
    open();
}

CTManagerDataBase::~CTManagerDataBase()
{
}

int CTManagerDataBase::readVersion(TDBVersionInfo& pversion)
{
    pversion.m_numversion = 0;
    pversion.m_szintescript = "";
    sqlite3_stmt* oQuery = nullptr;
    const std::string szQuery = "SELECT version, FROM wbd_version";
    int res = sqlite3_prepare_v2(m_dbDataBase,szQuery.c_str(),szQuery.size(),&oQuery,  NULL);
    if (SQLITE_OK != res)
    {
        if (oQuery)
            sqlite3_finalize(oQuery);
        return -1;
    }
    res = sqlite3_step(oQuery);
    if (SQLITE_ROW == res)
    {
        pversion.m_numversion = sqlite3_column_int(oQuery,0);
    }

    if (oQuery)
    {
        sqlite3_reset(oQuery);
        sqlite3_finalize(oQuery);
    }
    return res;
}


int CTManagerDataBase::getLastAutoInc(const char* ptablename,int nlen)const
{
    int pkey= -1;
    std::string szQuery = "SELECT seq from SQLITE_SEQUENCE WHERE name=?";
    sqlite3_stmt* oQuery = nullptr;
    int res = sqlite3_prepare_v2(m_dbDataBase,szQuery.c_str(),szQuery.size(),&oQuery,  NULL);
    if (SQLITE_OK != res)
    {
        if (oQuery)
            sqlite3_finalize(oQuery);
        trapSqliteError(res);
        return -1;
    }
    sqlite3_bind_text(oQuery,1,ptablename,nlen, NULL);
    res = sqlite3_step(oQuery);
    if (SQLITE_ROW == res)
    {
        pkey = sqlite3_column_int(oQuery,0);
    }
    if (oQuery)
    {
        sqlite3_reset(oQuery);
        sqlite3_finalize(oQuery);
    }
    if (SQLITE_ROW != res &&  SQLITE_OK != res && SQLITE_DONE != res)
    {
        trapSqliteError(res);
    }
    return pkey;
}

bool CTManagerDataBase::insertMeasure(int idsonde,double temperature,double humididty)
{
    std::string szQuery = "INSERT INTO wbd_weather (idsensor,temperature,humidity) VALUES(?,?,?)";
    sqlite3_stmt* oQuery = nullptr;
    int nres  = sqlite3_prepare_v2(m_dbDataBase,szQuery.c_str(),szQuery.size(),&oQuery,  NULL);
    if (SQLITE_OK != nres)
    {
        if (oQuery)
        {
            sqlite3_finalize(oQuery);
        }
        trapSqliteError(nres);
        return false;
    }
    sqlite3_bind_int(oQuery,1,idsonde);
    sqlite3_bind_double(oQuery,2,temperature);
    sqlite3_bind_double(oQuery,3, humididty);
    nres = sqlite3_step(oQuery);
    if (oQuery)
    {
        sqlite3_reset(oQuery);
        sqlite3_finalize(oQuery);
    }
    return (nres == SQLITE_OK) ;
}

CommandBuilder *CTManagerDataBase::getMeasure(const std::string &startDate, const std::string &endDate, int idsensor)
{

    std::string szQuery;
    if (idsensor != -1 )
        szQuery = "SELECT idsensor,temperature,humidity,stamp from wbd_weather where stamp >= ? AND stamp <= ? AND idsensor = ? ORDER BY stamp";
    else
        szQuery = "SELECT idsensor,temperature,humidity,stamp from wbd_weather where stamp >= ? AND stamp <= ? ORDER BY stamp";

    sqlite3_stmt* oQuery = nullptr;
    int nres  = sqlite3_prepare_v2(m_dbDataBase,szQuery.c_str(),szQuery.size(),&oQuery,  NULL);
    if (SQLITE_OK != nres)
    {
        if (oQuery)
        {
            sqlite3_finalize(oQuery);
        }
        trapSqliteError(nres);
        return nullptr;
    }

    sqlite3_bind_text(oQuery,1,startDate.c_str(), startDate.length(),NULL);
    sqlite3_bind_text(oQuery,2,endDate.c_str(), endDate.length(),NULL);
    if (idsensor != -1 )
        sqlite3_bind_int(oQuery,3, idsensor);

    CommandBuilder * c = new CommandBuilder("gettemp");

    while (SQLITE_ROW == (nres = sqlite3_step(oQuery)))
    {
        int nid  = sqlite3_column_int(oQuery,0);
        double temp = sqlite3_column_double(oQuery,1);
        double hum = sqlite3_column_double(oQuery,2);
        std::string stamp = (char*)sqlite3_column_text(oQuery,3);
        c->addMeasurement(nid,temp,hum,stamp);
    }
    if (oQuery)
    {
        sqlite3_reset(oQuery);
        sqlite3_finalize(oQuery);
    }
    return c;
}






