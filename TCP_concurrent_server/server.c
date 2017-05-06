/*
 * Concurrent Server: server.c
 *
 * Copyright(c): Rudra Nil Basu <rudra.nil.basu.1996@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

int main()
{
	int sockfd, newsockfd;
	int clilen;
	struct sockaddr_in cli_addr, serv_addr;
	int i;
	char buff[100];
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Cannot create socket\n");
		exit(1);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(6000); // port: 6000
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("Unable to bind local address\n");
		exit(1);
	}
	listen(sockfd, 5); // upto 5 concurrent clients
	while (1) {
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) {
			printf("Accept error\n");
			exit(1);
		}
		if (fork() == 0) {
			close(sockfd);
			while (1) {
				strcpy(buff, "Message from server");
				send(newsockfd, buff, strlen(buff) + 1, 0);
				for (i = 0;i < 100;i++) {
					buff[i] = '\0';
				}
				recv(newsockfd, buff, 100, 0);
				//send(newsockfd, buff, strlen(buff) + 1, 0);
				printf("%s\n",buff);
			}
			close(newsockfd);
			exit(0);
		}
		close(newsockfd);
	}
}
