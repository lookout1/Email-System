#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void conMysql(MYSQL **conn);
void closeMysql(MYSQL **conn);
int idenUser(MYSQL *conn,char* username,char* password);
void getUserID(MYSQL *conn,char* username,char* userID);
void addFiletoSend(MYSQL *conn,char* userID,char* path,char* name);
void addFiletoRec(MYSQL *conn,char* userID,char* path,char* name);
void getFileSum(MYSQL *conn,char* userID,char* fileSum);
void getFileName(MYSQL *conn,char* userID,char file[50][30]);
void deleteFile(MYSQL *conn,char* filepath);

