#ifndef _csinDB_20140528_h
#define _csinDB_20140528_h

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

//数据库单例
class CSinDB
{
public:
    static CSinDB *GetSinDB();

    int DoOpera(const char *sql,sqlite3_callback CallBack, void *);
    char *GetErrmsg();
    sqlite3 *Getdb();
protected:
private:
    CSinDB(const char *,sqlite3 **db);
    virtual ~CSinDB();
    char *errmsg;

    static CSinDB *pSinDB;
    static sqlite3 *db;

    friend class CGarbo;
};


//垃圾回收类
class CGarbo
{
public:
    static CGarbo cGar;

    ~CGarbo();

protected:
private:
};

#endif
