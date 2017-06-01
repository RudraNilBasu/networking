#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
void error(char *msg)
{
    perror(msg);
    exit(1);
}
int main(int argc,char* argv[])
{
    int sockfd,newsockfd,clilen,n,portno;
    char buf[256];
    struct sockaddr_in serv_addr,cli_addr;
    if(argc<2){
	fprintf(stderr,"No port provided!!\n");
	exit(1);
    }
    portno=atoi(argv[1]);
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)error("Error opening socket");
    bzero((char *)&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port=htons(portno);
    if(bind(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)error("Error on bind!!");
    listen(sockfd,5);
    clilen=sizeof(cli_addr);
    newsockfd=accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
    if(newsockfd<0)error("Error on accept!!");
    while(1){
	bzero(buf,256);
	n=read(newsockfd,buf,256);
	if(n<0)error("Error on read");
	printf("Message %s\n",buf);
	n=write(newsockfd,"I got your message",18);
    }
    return 0;
}

