#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int num;

void parent(int sig){
	if (sig==SIGTSTP){
		if(kill(num,0)!=-1){ 
			kill(num,SIGUSR1);
		}
	}
	if (sig==SIGINT){
		if (kill(num, 0)!=-1){
			kill(num, SIGUSR2);
		}
		else{
		printf("GOODBYE\n");
		exit(0);}
	}
}

void child(int sig){
	if (sig==SIGTSTP){
		signal(SIGTSTP, SIG_IGN);
	}
	if (sig==SIGINT){
		signal(SIGINT, SIG_IGN);
	}
	if (sig==SIGUSR1){
		printf("Signal Received %d \n" , getpid());
	}
	if (sig==SIGUSR2){
		printf ("Child exiting\n");
		exit(0);
	}
}

int main(){
	int pc[2];
	if(pipe(pc)==-1){	
		perror("fork");
		exit(1);
	}

	pid_t pid=fork();
	if (pid<0){
		perror("fork");
		exit(1);
	}	
	if (pid==0){
		signal(SIGTSTP, child);
		signal(SIGUSR1, child);
		signal(SIGINT,child);
		signal(SIGUSR2,child);
		char string[200];
		sprintf(string, "%d", getpid() );
		close(pc[0]);
		write(pc[1], string, 200);
		while(1){
		}
	}
	if (pid>0){
		char string[200];
		close(pc[1]);
		read(pc[0], string, 200);
		num= atoi(string);
		printf("%d\n",num); 
		printf("Parent pid %d\n", getpid());	
		signal(SIGTSTP, parent);
		signal(SIGINT, parent);
		wait(NULL);
		while(1){
		}
		exit(0);
	}	

}
