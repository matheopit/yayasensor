#ifndef CTMGR_DATABASEABS_HPP
#define CTMGR_DATABASEABS_HPP

#include <string>

struct sqlite3;
struct sqlite3_stmt;


class CTAbsManagerDataBase
{
public:
    CTAbsManagerDataBase(const char* szDataBaseName);
    virtual ~CTAbsManagerDataBase();
    void close();
    void cleanError();
    void open();
    bool commitTransaction();
    bool beginTransaction();
    bool rollBackTransation();
    int ExecQuery(const char* szQuery);
    void trapSqliteError(int)const;
    sqlite3* dBHandle(){ return m_dbDataBase; }
protected:
    mutable bool m_aborted;
    mutable int m_lastErrorCode;
    sqlite3 *m_dbDataBase;
    std::string m_szdatabasefile;
};


#endif /* CTMGR_DATABASEABS_HPP */
