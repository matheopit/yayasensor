#include "ctmgrdatabase.hpp"
#include <sqlite3.h>
#include <string>
#include <cstdio>
#include <cstring>


CTAbsManagerDataBase::CTAbsManagerDataBase(const char* szDataBaseName)
    :m_aborted(true)
     , m_lastErrorCode(SQLITE_OK)
     , m_dbDataBase(nullptr)
     , m_szdatabasefile(szDataBaseName)

{

}


CTAbsManagerDataBase::~CTAbsManagerDataBase()
{
    close();
}

int CTAbsManagerDataBase::ExecQuery(const char* szQuery)
{
    int res = SQLITE_ERROR;
    sqlite3_stmt* oQuery = nullptr;
    res = sqlite3_prepare_v2(m_dbDataBase,szQuery,strlen(szQuery),&oQuery,  nullptr);
    if (SQLITE_OK != res)
    {
#if 0    
        const char* p =sqlite3_errmsg(m_dbDataBase);
        fprintf(stderr,"Error while binding variable.[%s]\n",p );
#endif
        if (oQuery)
            sqlite3_finalize(oQuery);
        return res;
    }
    res = sqlite3_step(oQuery);
    if (oQuery)
    {
        sqlite3_reset(oQuery);
        sqlite3_finalize(oQuery);
    }
    return res;
}

bool CTAbsManagerDataBase::beginTransaction()
{
    if (!m_aborted)
    {
        int res = sqlite3_exec(m_dbDataBase,"BEGIN TRANSACTION",nullptr, nullptr, nullptr);
        if (SQLITE_OK != res)
            m_aborted = true;
    }
    return m_aborted == false;
}

bool CTAbsManagerDataBase::rollBackTransation()
{
    int res = sqlite3_exec(m_dbDataBase,"ROLLBACK TRANSACTION",nullptr, nullptr, nullptr);
    if (SQLITE_OK != res)
        m_aborted = true;
    return m_aborted == false;
}

bool CTAbsManagerDataBase::commitTransaction()
{
    if (!m_aborted)
    {
        int res = sqlite3_exec(m_dbDataBase,"COMMIT TRANSACTION",nullptr, nullptr, nullptr);
        if (SQLITE_OK != res)
            m_aborted = true;
    }
    return m_aborted == false;
}

void CTAbsManagerDataBase::close()
{
    if (m_dbDataBase)
    {
        sqlite3_close(m_dbDataBase);
        m_dbDataBase = nullptr;
    }
}

void CTAbsManagerDataBase::open()
{
    if (!m_dbDataBase)
    {
        int res = sqlite3_open_v2(m_szdatabasefile.c_str(),&m_dbDataBase,SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,nullptr);
        m_aborted = (SQLITE_OK != res);
        if (m_aborted)
            trapSqliteError(res);
    }
}

void CTAbsManagerDataBase::cleanError()
{
    m_aborted = false;
    m_lastErrorCode = SQLITE_OK;
}

void CTAbsManagerDataBase::trapSqliteError(int nsqlerror)const
{

    switch (nsqlerror)
    {
    case SQLITE_INTERNAL:
    case SQLITE_IOERR:
    case SQLITE_CORRUPT:
    case SQLITE_FULL:
    case SQLITE_CANTOPEN:
    case SQLITE_FORMAT:
    case SQLITE_NOTADB:
    case SQLITE_NOMEM:
    case SQLITE_PERM:
    {
        printf("Sqlite Error Code [%d]",nsqlerror);
        m_aborted = true;
        m_lastErrorCode = nsqlerror;
    }
   // default:break;
    };
}
