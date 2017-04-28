/*
 * server.c
 *
 * Copyright (C) 2017 Rudra Nil Basu <rudra.nil.basu.1996@gmail.com>
 *
 * Authors:
 *    Rudra Nil Basu <rudra.nil.basu.1996@gmail.com>
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 3 of the License, or
 *     (at your option) any later version.
 * 
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 * 
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int string_to_int(char *);
float calculate(int,int,char);

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	if (argc < 2) {
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
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
				sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	printf("-------------------------\n");
	printf("Copyright (c): Rudra Nil Basu <rudra.nil.basu.1996@gmail.com>\n");
	printf("Authors:\nRudra Nil Basu\n");
	printf("-------------------------\n");
	printf("Running server\n");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	printf("accepting\n");
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	printf("accepted\n");
	if (newsockfd < 0) 
		error("ERROR on accept");
	int num, first_num, second_num;
	float result;
	char operation;
	for(int i = 0; i < 3; i++) {
		bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if (n < 0) error("ERROR reading from socket");
		if (i == 0 || i == 2) {
			num = string_to_int(buffer);
			printf("We got: %d\n", num);
			if (i == 0) {
				first_num = num;
			} else {
				second_num = num;
			}
		} else {
			operation = buffer[0];
			printf("Operation: %c\n",operation);
		}
		if (i != 2) {
			n = write(newsockfd, "Recieved", 8);
		} else {
			result = calculate(first_num, second_num, operation);
			char msg[] = "Result: ";
			char final_msg[100];
			sprintf(final_msg, "%s%f", msg, result);
			n = write(newsockfd, final_msg, sizeof(final_msg));
		}
		if (n < 0) error("ERROR writing to socket");
	}

	return 0; 
}

int string_to_int(char *str)
{
	int num = 0, len = strlen(str), i;
	for(i = 0;i < len;i++) {
		if(str[i] == '\n') {
			break;
		}
		num = (num * 10) + (str[i] - '0');
	}
	return num;
}

float calculate(int a, int b, char op)
{
	if (op == '+') {
		return a+b;
	} else if (op == '-') {
		return a-b;
	} else if (op == '*') {
		return a*b;
	} else if (op == '/') {
		return ((float)(a * 1.0)/b);
	}
}
