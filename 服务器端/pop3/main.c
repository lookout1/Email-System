#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include"sockutil.h"
#include"db.h"
#define BUFSIZE 30


void TCPpop3(int fd);


int main()
{
        struct sockaddr_in fsin;
        char *service="pop3";
        int msock,ssock;
        unsigned int alen;
        msock=passiveSock(service,"tcp",32);
        while(1){
          alen=sizeof(fsin);
          ssock=accept(msock,(struct sockaddr *)&fsin,&alen);
          printf("%d",ssock);
          if(ssock<0)
             errexit("accept failed");
          TCPpop3(ssock);
          close(ssock);
          }
          (void)close(msock);
          printf("ok");
}

void TCPpop3(int fd)
{
  char from[129],to[129],to1[129];
  char buf[129]="",path[129]="",filepath[129]="",tim[20]="\0",username[129],pass                        word[129];
  char command1[129]="helo ",host[129]="smtp";
  char *temp1,*temp2,userID[20],fileSum[20],statAns[30]="+OK ";
  char file1[30]="1463217252",file[50][30];
  int n,p,s,outchars,i;
  time_t now;
  MYSQL *conn;

  strcat(path,"/root/mail/");

  (void)write(fd,"+OK\r\n",5);

  n=read(fd,buf,128);              //PACA
  buf[n]='\0';
  printf("%s",buf);

  (void)write(fd,"+OK\r\n",5);
  (void)write(fd,".\r\n",strlen(".\r\n"));

  n=read(fd,buf,128);                //USER
  buf[n]='\0';
    printf("%s",buf);
  temp1=strchr(buf,' ');
  temp2=strchr(buf,'\r');
  *temp2='\0';
  strcpy(username,temp1+1);

  strcat(path,username);
  strcat(path,"/rec/");

  (void)write(fd,"+OK\r\n",5);


  n=read(fd,buf,128);                   //PASS
  buf[n]='\0';
    printf("%s",buf);
  temp1=strchr(buf,' ');
  temp2=strchr(buf,'\r');
  *temp2='\0';
  strcpy(password,temp1+1);

  conMysql(&conn);
 if(idenUser(conn,username,password)==0)return;

  (void)write(fd,"+OK\r\n",5);

  n=read(fd,buf,128);                  //STAT
  buf[n]='\0';
  printf("%s\n",buf);

  getUserID(conn,username,userID);
  printf("%s\n",userID);
  getFileSum(conn,userID,fileSum);
  printf("%s\n",fileSum);
  strcat(statAns,fileSum);
  strcat(statAns,"\r\n");
  printf("%s\n",statAns);

  (void)write(fd,statAns,strlen(statAns));
  //(void)write(fd,"+OK 2\r\n",strlen("+OK 2\r\n"));

  n=read(fd,buf,128);                  //NOOP
  buf[n]='\0';
  printf("%s",buf);

  (void)write(fd,"+OK\r\n",5);

 getFileName(conn,userID,file);  //get user'sall filename

  for(i=0;i<atoi(fileSum);i++)
{

  n=read(fd,buf,128);                 //retr
  buf[n]='\0';
  printf("%s",buf);

  (void)write(fd,"+OK\r\n",5);

  strcpy(filepath,path);
  strcat(filepath,file[i]);
  printf("%s",filepath);

 if((p=open(filepath,O_RDONLY))<1)return;
  while(n!=0)
  {
     n=read(p,buf,128);
     printf("%s",buf);
     if((temp1=strstr(buf,"\r\n.\r\n"))!=NULL)
     {
     (void)write(fd,buf,temp1-buf+5);
     break;
     }
     (void)write(fd,buf,n);
  };
  deleteFile(conn,filepath);
  close(p);
  remove(filepath);
}
closeMysql(&conn);

  n=read(fd,buf,128);         //quit
  buf[n]='\0';
  printf("%s",buf);

  (void)write(fd,"+OK\r\n",5);
 
}

