#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[]){
	int real= getuid();
	int euid= geteuid();
	printf("The real UID is: %d\n", real);
	printf("The effective UID is: %d\n", euid);
	//int status= seteuid(0);
	//printf("The effective UID is: %d\n", status);
	//char one[50]="/usr/bin/";
	//strcat(one,argv[1]);
	char* arg[10];
	int i=1;
	int pos=0;
	while (argv[i]!=NULL){
		arg[pos]=argv[i];
		i++;
		pos++;
	}
	arg[pos]=NULL;
	execvp(argv[1], arg);	
}
