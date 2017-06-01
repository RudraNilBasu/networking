#include<stdio.h> 
#include<sys/types.h> 
#include<netinet/in.h> 
#include<string.h> 
#include<stdlib.h>

int main(int argc,char *argv[])
{
	FILE *fp,*fp2;
	int sockfd,newsockfd,portno,clilen,n,i;
	size_t  max = 100;
	char fname[100],name[100],fname1[100],arg[100],arg1[100];
	struct sockaddr_in serv_addr,cli_addr;
	if (argc < 2) 
	{
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd<0)
		printf("error on accept\n");
	//memset(fname,'\0',100);
	//memset(name,'\0',100);
	memset(fname1,'\0',100);
	memset(arg,'\0',100);
	memset(arg1,'\0',100);
	n=recv(newsockfd,fname,100,0);
	fname[n]='\0';
	//system("read -r line");
	strcpy(fname1,"find . -name ");
	strcat(fname1,fname);
	printf("%s\n",fname1);
	system(fname1);
	strcat(fname1," >> 11.txt");
	printf("%s\n",fname1);
	system(fname1);
	system("cat 11.txt");
	fp2=fopen("11.txt","r");
	fgets(arg,100,fp2);
	//arg[]='\0';
	arg[strlen(arg)-1]='\0';
	printf("%s\n",arg);
	//printf("%s\n",arg);
	//freopen("NUL", "a", stdout);
	//freopen("/dev/null", "a", stdout);
	//setbuf(stdout, arg);
	//system("read -r line");
	//printf("\n %s \n",arg);
	if(n<0)
		printf("error on read");
	else
	{
		fp=fopen(arg,"r"); //read mode
		if(fp==NULL)
		{
			send(newsockfd,"error",5,0);
			close(newsockfd);
		}
		else
		{
			while(fgets(name,100,fp))
			{
				if(write(newsockfd,name,100)<0)
				{
					printf("can't send\n");
				}
			}
			if(!fgets(name,sizeof(name),fp)) 
	  		{	 
	   			send(newsockfd,"Done",4,0);
	  		} 
			return 0;
		}
	}
}
	
	
