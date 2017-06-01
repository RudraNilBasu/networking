#include<stdio.h>
#include<stdlib.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<stdlib.h>
#include<string.h>
int main(int argc,char *argv[]) 
{ 
	FILE *fp;
	int sockfd,newsockfd,portno,r;
	char fname[100],fname1[100],text[100];
	struct sockaddr_in serv_addr;
	portno = atoi(argv[2]);
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("Error on socket creation\n");
		exit(0);
	}
	else
		printf("socket created\n");
	serv_addr.sin_family=AF_INET; 
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(portno); 
	if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0) 
	{
		printf("Error in Connection...\n"); 
		exit(0);
	}
	else 
		printf("Connected...\n"); 
	//memset(fname,'\0',100);
	//memset(fname1,'\0',100);
	//memset(text,'\0',100);
	printf("Enter the filename existing in the server:\n");
	scanf("%s",fname);
	printf("Enter the filename to be written to:\n");
	scanf("%s",fname1);
	fp=fopen(fname1,"w");
	send(sockfd,fname,100,0);
	while(1)
	{
		r=recv(sockfd,text,100,0);
		text[r]='\0';
		fprintf(fp,"%s",text);
		if(strcmp(text,"error")==0)
			printf("file not available\n");
		if(strcmp(text,"Done")==0)
		{
			printf("file is transferred\n");
			fclose(fp);
			close(sockfd);
			break;
		}
		else
			fputs(text,stdout);
	}
	return 0;
}
		
	
	
	
