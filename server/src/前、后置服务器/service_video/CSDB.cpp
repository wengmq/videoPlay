#include "CSDB.h"

#include <iostream>
#include <stdio.h>

using namespace std;

CSDB *CSDB::csdb=NULL;  //静态成员变量初始化
	
CSDB::CSDB(char *name)
{
	int ret=sqlite3_open(name,&db);
	if (ret != 0)
	{
		printf("打开数据库失败\n");
	}
	//cout<<"Open sqlite3 database"<<endl;
}
CSDB::~CSDB()
{
	sqlite3_close(db);
}

int CSDB::CloseDB()
{
	 printf("Close sqlite3 database\n");
    sqlite3_close(db);	
    return 0;
}

//静态成员函数实现静态成员变量单例化
CSDB *CSDB::Getdata(char *name)
{
	if (csdb==NULL)
	{
		csdb=new CSDB(name);
	}
	return csdb;
}

//执行sql语句，获取查询结果
int CSDB::Get_table(char *sql,char ***presult,int *row,int *col)
{
	char *err=NULL;
	sqlite3_get_table(this->db,sql,presult,row,col,&err);
	if (err != NULL)
	{
		printf("%s\n",err);
		return  -1;
	}
	return 0;
}

//释放查询后的数据指针
int CSDB::Free_table(char** pResult)
{
    sqlite3_free_table(pResult);    
    return 0;
}


