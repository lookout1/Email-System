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

void TCPsmtp(int fd);
void base64enc(char *instr,char *outstr);
int base64_decode( const char * base64, unsigned char * bindata );

const char * base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main()
{
        struct sockaddr_in fsin;
        char *service="smtp";
        int msock,ssock;
        unsigned int alen;
        msock=passiveSock(service,"tcp",32);
        while(1){
          alen=sizeof(fsin);
          ssock=accept(msock,(struct sockaddr *)&fsin,&alen);
          if(ssock<0)
             errexit("accept failed");
          printf("%d",ssock);
          TCPsmtp(ssock);
        }
          (void)close(msock);
          printf("ok");
}

void TCPsmtp(int fd)
{
  char from[129],to[129],to1[129];
  char buf[129]="",path[129]="",tim[20]="\0",username[129],password[129];
  char command1[129]="helo ",host[129]="smtp";
  char *temp1,*temp2,userID[20];
  int n,p,s,outchars;
  time_t now;
  MYSQL *conn;

  strcat(path,"/root/mail/");

  (void)write(fd,"220\r\n",strlen("220\r\n"));

  n=read(fd,buf,128);
  buf[n]='\0';
  printf("%s",buf);

  (void)write(fd,"250-mail\r\n",strlen("250-mail\r\n"));
  /*(void)write(fd,"250-PIPELINING\r\n",strlen("250-PIPELINING\r\n"));*/
  (void)write(fd,"250-AUTH LOGIN PLAIN\r\n",strlen("250-AUTH LOGIN PLAIN\r\n"));
  (void)write(fd,"250-AUTH=LOGIN PLAIN\r\n",strlen("250-AUTH=LOGIN PLAIN\r\n"));
 /* (void)write(fd,"250-coremail 1Uxr2xKj7kG0xkI17xGrUDI0s8FY2U3Uj8Cz28x1UUUUU7Ic2I0Y2UFFa5-HUCa0xDrUUUUj\r\n",strlen("250-coremail 1Uxr2xKj7kG0xkI17xGrUDI0s8FY2U3Uj8Cz28x1UUUUU7Ic2I0Y2UFFa5-HUCa0xDrUUUUj\r\n"));
  (void)write(fd,"250-STARTTLS\r\n",strlen("250-STARTTLS\r\n"));*/
  (void)write(fd,"250 OK\r\n",strlen("250 OK\r\n"));

  n=read(fd,buf,128);
  buf[n]='\0';
  printf("%s",buf);

  if(strcmp(buf,"AUTH LOGIN\r\n")==0)
{
  (void)write(fd,"334\n",4);

  n=read(fd,username,128);       //username
  username[n-2]='\0';
  n=base64_decode(username,username);
  username[n]='\0';

  strcat(path,username);
  strcat(path,"/send/");

  (void)write(fd,"334\n",4);

  n=read(fd,password,128);        //password
  password[n-2]='\0';
  n=base64_decode(password,password);
  password[n]='\0';

  (void)write(fd,"235\n",4);

  conMysql(&conn);
  //idenUser(conn,&res,username,password);
  //if((row = mysql_fetch_row(res)) == NULL)exit(0);
  //closeMysql(conn,res);
  getUserID(conn,username,userID);
  printf("%s",userID);

  n=read(fd,from,128);
  from[n]='\0';

  (void)write(fd,"250\n",4);

  n=read(fd,to,128);
  to[n]='\0';
  strcpy(to1,to);

  (void)write(fd,"250\n",4);

  n=read(fd,buf,128);
  buf[n]='\0';

  (void)write(fd,"354\n",4);

  (void)time(&now);
  sprintf(tim,"%ld",now);
  strcat(path,tim);

  addFiletoSend(conn,userID,path,tim);     //filepath save in mysql
  closeMysql(&conn);

  p=creat(path,0644);

  while(1)    //mail content saved in path
 {
  n=read(fd,buf,128);
  write(p,buf,n);
  if(strstr(buf,"\r\n.\r\n")!=NULL)break;
 }
  close(p);
  (void)write(fd,"250\n",4);

  n=read(fd,buf,128);       // quit
  buf[n]='\0';
  printf("%s",buf);

  (void)write(fd,"221\n",4);
  close(fd);

  //serve to serve

  temp1=strchr(to,'@');
  temp2=strchr(to,'>');
  *temp1='.';
  *temp2='\0';
  printf("%s",temp1);
  strcat(host,temp1);
  printf("%s",host);

  s=connectTCP(host,"smtp");

  n=read(s,buf,128);
  buf[n]='\0';
//  *temp2='\n';
//  *(temp2+1)='\0';
  strcpy(command1,"helo hnu.edu.cn\n");
  printf("%s\n",buf);
  printf("%s\n",command1);
  outchars=strlen(command1);
  (void)write(s,command1,outchars);

  n=read(s,buf,128);
  buf[n]='\0';
  printf("%s",buf);
  outchars=strlen(from);
  (void)write(s,from,outchars);

  n=read(s,buf,128);
  buf[n]='\0';
  printf("%s",buf);
  outchars=strlen(to1);
  (void)write(s,to1,outchars);

  n=read(s,buf,128);
  buf[n]='\0';
  printf("%s",buf);
  outchars=strlen("data\n");
  (void)write(s,"data\n",outchars);

  n=read(s,buf,128);
  buf[n]='\0';
  printf("%s",buf);

  p=open(path,O_RDONLY);
  while(n!=0)
  {
     n=read(p,buf,128);
     printf("%s",buf);
     (void)write(s,buf,n);
     if(strstr(buf,"\r\n.\r\n")!=NULL)break;
  }
  close(p);
  n=read(s,buf,128);
  buf[n]='\0';
  printf("%s",buf);
  outchars=strlen("quit\n");
  (void)write(s,"quit\n",outchars);
  close(s);
}
else
{
  /*(void)write(fd,"250\r\n",5);

  n=read(fd,buf,128);
  buf[n]='\0';
  printf("%s111",buf);

  (void)write(fd,"334\r\n",5); */

  strcpy(from,buf);
  printf("%s",from);

  (void)write(fd,"250\r\n",5);

  n=read(fd,to,128);
  to[n]='\0';
  printf("%s",to);
  strcpy(to1,to);
  temp1=strchr(to,'<');
  temp2=strchr(to,'@');
  *temp2='\0';
  conMysql(&conn);
  getUserID(conn,temp1+1,userID);
  strcat(path,temp1+1);
  strcat(path,"/rec/");

  (void)write(fd,"250\r\n",5);

  n=read(fd,buf,128);
  buf[n]='\0';

  (void)write(fd,"354\r\n",5);

  (void)time(&now);
  sprintf(tim,"%ld",now);
  strcat(path,tim);

  addFiletoRec(conn,userID,path,tim);      //filepath save in mysql
  closeMysql(&conn);

  p=creat(path,0644);

  while(1)    //mail content saved in path
 {
  n=read(fd,buf,128);
  write(p,buf,n);
  if(strstr(buf,"\r\n.\r\n")!=NULL)break;
 }
  close(p);

  (void)write(fd,"250\r\n",5);

  n=read(fd,buf,128);       // quit
  buf[n]='\0';
  printf("%s",buf);

  (void)write(fd,"221\r\n",5);
  close(fd);
}
}


void base64enc(char *instr,char *outstr)
{
     char * table="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
     int instr_len=0;
     instr_len=strlen(instr);
     while(instr_len>0){
       *outstr++=table[(instr[0]>>2) & 0x3f];
      if(instr_len>2){
     *outstr++= table[((instr[0] & 0x03)<<4) | (instr[1] >>4)];
     *outstr++= table[((instr[1] & 0x0f)<<2) | (instr[2] >>6)];
     *outstr++= table[(instr[2] & 0x3f)];
        }
    else{
       switch(instr_len){
       case 1:
        *outstr++= table[((instr[0] & 0x03)<<4)];
        *outstr ++ = '=';
        *outstr ++ = '=';
        break;
        case 2:
        *outstr++= table[((instr[0] & 0x03)<<4) | (instr[1] >>4)];
        *outstr++= table[((instr[1] & 0x0f)<<2) | (instr[2] >>6)];
        *outstr++ = '=';
        break;
         }
        }
      instr += 3;
      instr_len -= 3;
      }
   *outstr = 0;
}

int base64_decode( const char * base64, unsigned char * bindata )
{
    int i, j;
    unsigned char k;
    unsigned char temp[4];
    for ( i = 0, j = 0; base64[i] != '\0' ; i += 4 )
    {
        memset( temp, 0xFF, sizeof(temp) );
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i] )
                temp[0]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i+1] )
                temp[1]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i+2] )
                temp[2]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i+3] )
                temp[3]= k;
        }

        bindata[j++] = ((unsigned char)(((unsigned char)(temp[0] << 2))&0xFC)) |
                ((unsigned char)((unsigned char)(temp[1]>>4)&0x03));
        if ( base64[i+2] == '=' )
            break;

        bindata[j++] = ((unsigned char)(((unsigned char)(temp[1] << 4))&0xF0)) |
                ((unsigned char)((unsigned char)(temp[2]>>2)&0x0F));
        if ( base64[i+3] == '=' )
            break;

        bindata[j++] = ((unsigned char)(((unsigned char)(temp[2] << 6))&0xF0)) |
                ((unsigned char)(temp[3]&0x3F));
    }
    return j;
}

