#ifndef _CSDB_H
#define _CSDB_H
#include <sqlite3.h>


//数据库单例
class CSDB
{
public:
	~CSDB();
	static CSDB *Getdata(char *name);
	int Get_table(char *sql,char ***presult,int *row,int *col);
	int Free_table(char** pResult);
	int CloseDB();
private:
	CSDB(char *name);
	static CSDB *csdb;
	sqlite3 *db;
};
#endif

