#include"BackServerFunction.h"

int login( char *name, char*pwd)
{
    char *sql ="select * from user";
    //�������ļ�
    //CSinDB::GetSinDB();

    char **dbresult;

    int rows,cols;
        sqlite3_get_table(CSinDB::GetSinDB()->Getdb(),sql,&dbresult,&rows,&cols,NULL);
        //��������ͷһ���ӡ����,ȫ��������dbresult������
        for(int i=0;i<rows+1;i++)//��
        {

            if(strcmp(dbresult[i*cols+0],name)==0  && strcmp(dbresult[i*cols+1],pwd)==0)
                return 1;
//            for(int j=0;j<cols;j++)//��
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
//  // ÿ����¼�ص�һ�θú���,�ж������ͻص����ٴ�
//  int i;
//  for( i=0; i < col_count; i++){
//    printf( "%s = %s\n", col_Name[i], col_values[i] == 0 ? "NULL" : col_values[i] );
//  }

//  return 0;
//}
