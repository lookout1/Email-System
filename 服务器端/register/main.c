#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include"sockutil.h"
#include <sys/types.h>
#include"db.h"
#define BUFSIZE 30

void Register(int fd);


int main()
{
        struct sockaddr_in fsin;
        char *service="7000";
        int msock,ssock;
        unsigned int alen;
        msock=passiveSock(service,"tcp",32);
        while(1){
          alen=sizeof(fsin);
          ssock=accept(msock,(struct sockaddr *)&fsin,&alen);
          if(ssock<0)
             errexit("accept failed");
          printf("%d",ssock);
          Register(ssock);
        }
          (void)close(msock);
          printf("ok");
}

void Register(int fd)
{
       char username[50],password[50],repassword[50],userID[10];
       char buf[129];
       MYSQL *conn;
       int n;
       write(fd,"hello\n",sizeof("hello\n"));
       n=read(fd,buf,129);
       buf[n]='\0';
       strcpy(username,buf);
       write(fd,username,sizeof(username));

       n=read(fd,buf,129);
       buf[n]='\0';
       strcpy(password,buf);
       write(fd,password,sizeof(password));

       n=read(fd,buf,129);
       buf[n]='\0';
       strcpy(repassword,buf);
       write(fd,repassword,sizeof(repassword));

       conMysql(&conn);
       getUserID(conn,username,userID);
       if(strcmp(userID,"-1")!=0)
       {
          write(fd,"100",sizeof("100"));
          closeMysql(&conn);
          close(fd);
          return;
       }
       if(strcmp(password,repassword)!=0)
       {
          write(fd,"101",sizeof("101"));
          closeMysql(&conn);
          close(fd);
          return;
       }
       getUserIDMax(conn,userID);
       n=atoi(userID);
       n=n+1;
       sprintf(userID,"%d",n);
       printf("%s",userID);
       addUser(conn,username,password,userID);
       write(fd,"102",sizeof("102"));
       closeMysql(&conn);
       close(fd);

       char filepath[100]="/root/mail/";
       strcat(filepath,username);
       mkdir(filepath,0777);
       char file[100];
       strcpy(file,filepath);
       strcat(file,"/send");
       mkdir(file,0777);
       strcpy(file,filepath);
       strcat(file,"/rec");
       mkdir(file,0777);
}

