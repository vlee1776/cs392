#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "my.h"
#include <strings.h>
#include <signal.h>

//I pledge my honor that I have abided by the Stevens Honor System

//append 10 digits which indicate length of message
char* appendpre(char* string){
	int len=my_strlen(string);
	char ret[11];
	char temp[11]="0";
	sprintf(ret, "%i", len);
	while (my_strlen(ret)!=10){
		my_strcat(temp,ret);
		my_strcpy(ret, temp);
		bzero((char*)temp,10);
		temp[0]='0';
	}
	return (my_strconcat(ret,string));	
}

int whitespace(char *string){
	int i=0;
	while (string[i]!='\0'){
		if (string[i]=='\t' || string[i]==' '){
			i++;
		}
		else
			return 0;
	}
	return 1;
}

int main(int argc, char* argv[]){
	int sockfd; 
	int portnum;
	struct sockaddr_in serv_addr;
	struct hostent *server;
 
	if (argc<3){
		printf("hostname & port pls\n");
		exit(0);
	}
	//get the portnum and make the socket
	portnum =atoi(argv[2]);
	sockfd= socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd<0){
		printf("Error opening socket\n");
		exit(1);
	}
	//set up the server values
	server= gethostbyname(argv[1]);
	bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family= AF_INET;
	bcopy((char *)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port=htons(portnum);
	
	//Input name
	char buffer[255];
	char* line=(char*)malloc(30*sizeof(char));
	size_t size =30;
	bzero ((char*)buffer, 256);
	printf("Please enter UserName:\n");
	
	//getline is unlimited buffer
	int status= getline(&line, &size, stdin);
	int len= my_strlen(line)-1;
	line[len]='\0';
	while (whitespace(line)){
		printf("Please enter UserName:\n");
		status= getline(&line, &size, stdin);
		len= my_strlen(line)-1;
		line[len]='\0';
	}
	//connect after the name is inputter so that no delay in server	
	//connect the socket to the server
	if (connect (sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
		printf("Error connecting\n");
		exit(1);
	}
	//add the length 
	char* string= appendpre(line);
	len= my_strlen(string);
	status=write(sockfd, string, my_strlen(string));
	if (status < 0){
    		perror("ERROR writing to socket\n");
  		exit (1);
	}
	//read the Welcome Message
	status= read(sockfd,buffer,10);
	buffer[10]='\0';
	if (status < 0){
    		perror("ERROR reading first part from socket\n");
  		exit (1);
		}
	len=atoi(buffer)+1;		
	free(line);
	line=(char*)malloc((len)*sizeof(char));
	status= read(sockfd, line, len-1);
	if (status < 0){
    		perror("ERROR reading second part from socket\n");
  		exit (1);
	}
	line[len-1]='\0';
	free(string);
	printf ("%s\n",line);
	free(line);
	
	//fork into two children one who reads and one who writes
	pid_t child=fork();
	//read input	
	if (child>0){
		while (1){
			//read the first 10 chars in that signifys the length of the string	
			char b[11];	
			int s = read(sockfd,b,10);
			if (s < 0){
    				perror("ERROR first reading from socket\n");
  				exit (1);
			}
			//make the char an int and allocate the memory
			int len= atoi(b)+1;
			char* buff=(char*)malloc(len*sizeof(char));
			s= read(sockfd, buff, len-1);	
			if (s < 0){
    				perror("ERROR second reading from socket\n");
  				exit (1);
			}
			buff[len-1]='\0';
			//if youre supposed to exit
			if (my_strcmp(b,"exit")==0){
				printf("%s\n", "EXITING");	
				free(buff);	
				kill(0,SIGINT);
				_exit(0);
			}
			//print the string without the buffer
			printf("%s\n",buff);
			free(buff);	
		}
	}
	//write to server
	else if (child==0){
		while(1){
			//allocate some memory and getline
			char* b=(char*)malloc(30*sizeof(char));	
			int s= getline(&b, &size, stdin);
			if (s<0){
				perror("Error on reading input\n");
				exit(1);
			}	
			b[s-1]='\0';
			//attach the length of the string as a prefix
			char* buff= appendpre(b);
			//write that to the socket
			s=write(sockfd, buff, my_strlen(buff));
			if (s<0){
				perror("Writing to socket\n");
				exit(1);
			}
			bzero((char*)buff,my_strlen(buff));
			free(buff);
			free(b);
		}
	}
	else{
		perror("Failure on Fork\n");
		exit(0);
	}
	
}
