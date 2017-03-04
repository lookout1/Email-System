#include"sockutil.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<unistd.h>
#include<errno.h>

int connectSock(char* host,char* service,char* protocol)
{
        struct hostent*         pHost;
        struct servent*         pServ;
        struct protoent*        pProto;
        struct sockaddr_in      addr;
        int    s,type;
        memset(&addr,0,sizeof(addr));
        addr.sin_family=AF_INET;
        if((pHost=gethostbyname(host))!=NULL)
                memcpy(&addr.sin_addr,pHost->h_addr,pHost->h_length);
        else if((addr.sin_addr.s_addr=inet_addr(host))==INADDR_NONE)
                errexit("can't get \"%s\" host entry",host);
        if((pServ=getservbyname(service,protocol))!=NULL)
                addr.sin_port=pServ->s_port;
        else if((addr.sin_port=htons((unsigned short)atoi(service)))==0)
                errexit("can't get \"%s\" service entry",service);
        if((pProto=getprotobyname(protocol))==0)
                errexit("can't get \"%s\" protocol entry",protocol);
        if(strcmp(protocol,"tcp")==0)
                type=SOCK_STREAM;
        else
                type=SOCK_DGRAM;
        s=socket(PF_INET,type,pProto->p_proto);
        if(s<0)
                errexit("can't create socket");
        if(connect(s,(struct sockaddr*)&addr,sizeof(addr))<0)
                errexit("can't connect to %s:%s",host,service);
        return s;
}

int passiveSock(char* service,char* protocol,int qlen)
{
        struct servent*         pServ;
        struct protoent*        pProto;
        struct sockaddr_in      addr;
        int        s,type,reuse=1;
        memset(&addr,0,sizeof(addr));
        addr.sin_family=AF_INET;
        addr.sin_addr.s_addr=INADDR_ANY;
        if((pServ=getservbyname(service,protocol))!=NULL)
                addr.sin_port=pServ->s_port;
        else if((addr.sin_port=htons((unsigned short)atoi(service)))==0)
                errexit("can't get \"%s\" service entry",service);
        if((pProto=getprotobyname(protocol))==0)
                errexit("can't get \"%s\" protocol entry",protocol);
        if(strcmp(protocol,"tcp")==0)
                type=SOCK_STREAM;
        else
                type=SOCK_DGRAM;
        s=socket(PF_INET,type,pProto->p_proto);
        if(s<0)
                errexit("can't create socket");
        if(setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int))<0)
                errexit("setsockopt err");
        if(bind(s,(struct sockaddr*)&addr,sizeof(addr))<0)
                errexit("can't bind to %s port",service);
        if(type==SOCK_STREAM && listen(s,qlen)<0)
                errexit("can't to listen on %s port",service);
        return s;
}

void errexit(char* fmt,...)
{
        va_list arg_ptr;
        va_start(arg_ptr,fmt);
        vfprintf(stderr,fmt,arg_ptr);
        fprintf(stderr,":%s.\n",strerror(errno));
        va_end(arg_ptr);
        exit(errno);
}

int connectTCP(char *host,char *service)
{
  return connectSock(host,service,"tcp");
}

