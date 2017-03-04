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

void idenUser(MYSQL *conn,MYSQL_RES **res,char* username,char* password)
{
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

    *res = mysql_use_result(conn);
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
      printf("%s",sql);
    if (mysql_query(conn,sql))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    if((row = mysql_fetch_row(res)) == NULL)
{strcpy(userID,"-1");
     return;
      }
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

void getUserIDMax(MYSQL *conn,char* userID)
{
      MYSQL_RES *res;
      MYSQL_ROW row;
      char sql[129]="select userID from user order by userID desc";
    if (mysql_query(conn,sql))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    if((row = mysql_fetch_row(res)) == NULL)
    {strcpy(userID,"0");
     return;
    }
    strcpy(userID,row[0]);
    mysql_free_result(res);
}

void addUser(MYSQL *conn,char* username,char* pass,char* userID)
{
    char sql[129]="insert into user value('";
    strcat(sql,userID);
    strcat(sql,"','");
    strcat(sql,username);
    strcat(sql,"','");
    strcat(sql,pass);
    strcat(sql,"')");
    printf("%s",sql);
    if (mysql_query(conn,sql))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

