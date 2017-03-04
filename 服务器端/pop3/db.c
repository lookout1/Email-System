#include"db.h"

void conMysql(MYSQL **conn)
{
    char server[] = "localhost";
    char user[] = "root";
    char password[] = "123";
    char database[] = "mail";

    *conn = mysql_init(NULL);

    if (!mysql_real_connect(*conn, server,user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(*conn));
        exit(1);
    }
}

void closeMysql(MYSQL **conn)
{
    mysql_close(*conn);
}

int idenUser(MYSQL *conn,char* username,char* password)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char sql[129]="select * from user where username='";
    strcat(sql,username);
    strcat(sql,"' and password='");
    strcat(sql,password);
    strcat(sql,"'");
    printf("%s",sql);
    if (mysql_query(conn,sql))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    if((row = mysql_fetch_row(res)) == NULL)
     {
      mysql_free_result(res);
      return 0;
     }
    mysql_free_result(res);
    return 1;
}

void addFiletoSend(MYSQL *conn,char* userID,char* path,char* name)
{
    char sql[129]="insert into sender value('";
    strcat(sql,userID);
    strcat(sql,"','");
    strcat(sql,name);
    strcat(sql,"','");
    strcat(sql,path);
    strcat(sql,"')");
    printf("%s",sql);
    if (mysql_query(conn,sql))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

void getUserID(MYSQL *conn,char* username,char* userID)
{
      MYSQL_RES *res;
      MYSQL_ROW row;
      char sql[129]="select userID from user where username='";
      strcat(sql,username);
      strcat(sql,"'");
    if (mysql_query(conn,sql))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    if((row = mysql_fetch_row(res)) == NULL)exit(0);
    strcpy(userID,row[0]);
    mysql_free_result(res);
}

void addFiletoRec(MYSQL *conn,char* userID,char* path,char* name)
{
    char sql[129]="insert into recver value('";
    strcat(sql,userID);
    strcat(sql,"','");
    strcat(sql,name);
    strcat(sql,"','");
    strcat(sql,path);
    strcat(sql,"')");
    printf("%s",sql);
    if (mysql_query(conn,sql))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

void getFileSum(MYSQL *conn,char* userID,char* fileSum)
{
      MYSQL_RES *res;
      MYSQL_ROW row;
      char sql[129]="select count(*) from recver where userID='";
      strcat(sql,userID);
      strcat(sql,"'");
      printf("%s\n",sql);
    if (mysql_query(conn,sql))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    strcpy(fileSum,row[0]);
    mysql_free_result(res);
}

void getFileName(MYSQL *conn,char* userID,char file[50][30])
{
      int i=0;
      MYSQL_RES *res;
      MYSQL_ROW row;
      char sql[129]="select filename from recver where userID='";
      strcat(sql,userID);
      strcat(sql,"' order by filename");
      printf("%s",sql);
    if (mysql_query(conn,sql))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    while((row=mysql_fetch_row(res))!=NULL)
   {
      strcpy(file[i],row[0]);
      i++;
   }
    mysql_free_result(res);
}

void deleteFile(MYSQL *conn,char* filepath)
{
    char sql[129]="delete from recver where filepath='";
    strcat(sql,filepath);
    strcat(sql,"'");
    if (mysql_query(conn,sql))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
   }

}

