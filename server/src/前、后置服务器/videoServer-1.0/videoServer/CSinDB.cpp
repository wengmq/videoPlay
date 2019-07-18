#include "CSinDB.h"
CSinDB * CSinDB::pSinDB = NULL;
sqlite3 *CSinDB::db = NULL;


//��Ϊһ������ֻ��һ�����ݿ⣬���Կ���д��
CSinDB::CSinDB(const char *acName, sqlite3 **d)
{
    int iResult = sqlite3_open(acName, d);
    if (iResult == SQLITE_OK)
    {
        printf("sqllite db open successs\n");
    }
    else
    {
        printf("%s",sqlite3_errmsg(db));
    }
}

CSinDB::~CSinDB()
{
    sqlite3_close(CSinDB::db);
}


//����ֻ���һ��ʵ��
CSinDB *CSinDB::GetSinDB()
{
    if (CSinDB::pSinDB == NULL)
    {
        CSinDB::pSinDB = new CSinDB("./data/mydb.db3",&CSinDB::db);
    }
    //	printf("get singledb");
    return CSinDB::pSinDB;
}

int CSinDB::DoOpera(const char *sql, sqlite3_callback CallBack, void *canshu)
{
    return sqlite3_exec(db,sql,CallBack,canshu,&errmsg);
}
char *CSinDB::GetErrmsg()
{
    return errmsg;
}

////////////////////
CGarbo::~CGarbo()
{
    if (CSinDB::pSinDB != NULL)
    {
        delete CSinDB::pSinDB;
        //	printf("xigou");
    }
}

sqlite3 *CSinDB::Getdb()
{

    return db;
}
