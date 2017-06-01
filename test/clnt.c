#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
void error(char *msg)
{
    perror(msg);
    exit(1);
}
int main(int argc,char *argv[])
{
    int sockfd,portno,n;
    char buf[256];
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if(argc<3){
	fprintf(stderr,"usage %s hostname port",argv[0]);
	exit(1);
    }
    sockfd=socket(AF_INET, SOCK_STREAM,0);
    if(sockfd<0)error("error connecting to server");
    server=gethostbyname(argv[1]);
    if(server==NULL){
	fprintf(stderr,"No host found!!\n");
	exit(1);
    }
    portno=atoi(argv[2]);
    bzero((char *)&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port=htons(portno);
    if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)error("Error connecting");
    while(1){
	bzero(buf,256);
	printf("Enter message: ");
	fgets(buf,255,stdin);
	n=write(sockfd,buf,strlen(buf));
	bzero(buf,256);
	n=read(sockfd,buf,256);
	printf("%s\n",buf);
    }
    return 0;
}
