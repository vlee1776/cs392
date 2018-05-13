#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

int main(int argc, char* argv[]){
	int socketfd;
	int portnum;
	struct sockaddr_in server_addr;
	struct hostent *server;
	int n;	
	if (argc <3){
		printf("IPAddress and Port\n");	
		exit(0);
	}	
	portnum= atoi(argv[2]);
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd< 0){
		printf("Error Opening Socket");
		exit(0);
	}
	server=gethostbyname(argv[1]);
	if (server ==NULL){
		printf("No host");
		exit(0);
	}
	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	bcopy((char *) server->h_addr, (char*)&server_addr.sin_addr.s_addr, server->h_length);
	server_addr.sin_port= htons(portnum);
	char buffer[256];
if (connect(socketfd,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
        printf("Error connecting");
	exit(0);}
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(socketfd,buffer,strlen(buffer));
    if (n < 0) 
         exit(0);
    bzero(buffer,256);
    n = read(socketfd,buffer,255);
    if (n < 0) 
         exit(0);
    printf("%s\n",buffer);
    return 0;}
