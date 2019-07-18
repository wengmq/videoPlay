#include"BackServerFunction.h"

int login( char *name, char*pwd)
{
    char *sql ="select * from user";
    //打开数据文件
    //CSinDB::GetSinDB();

    char **dbresult;

    int rows,cols;
        sqlite3_get_table(CSinDB::GetSinDB()->Getdb(),sql,&dbresult,&rows,&cols,NULL);
        //这里会把列头一起打印出来,全部保存在dbresult数组里
        for(int i=0;i<rows+1;i++)//行
        {

            if(strcmp(dbresult[i*cols+0],name)==0  && strcmp(dbresult[i*cols+1],pwd)==0)
                return 1;
//            for(int j=0;j<cols;j++)//列
//            {
//                printf("%s\t",dbresult[i*cols+j]);

//            }
//            printf("\n");
        }
        sqlite3_free_table(dbresult);

       return 0;

}

//int login_select_callback(void * data, int col_count, char ** col_values, char ** col_Name)
//{
//  // 每条记录回调一次该函数,有多少条就回调多少次
//  int i;
//  for( i=0; i < col_count; i++){
//    printf( "%s = %s\n", col_Name[i], col_values[i] == 0 ? "NULL" : col_values[i] );
//  }

//  return 0;
//}
