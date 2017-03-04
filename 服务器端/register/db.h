#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void conMysql(MYSQL **conn);
void closeMysql(MYSQL **conn);
void idenUser(MYSQL *conn,MYSQL_RES **res,char* username,char* password);
void getUserID(MYSQL *conn,char* username,char* userID);
void addFiletoSend(MYSQL *conn,char* userID,char* path,char* name);
void addFiletoRec(MYSQL *conn,char* userID,char* path,char* name);

