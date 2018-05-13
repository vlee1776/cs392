#include "my.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>


char* directory;

void parent(int sig){
	if (sig==SIGINT){
		my_printf("\nMINISHELL:  %s$:",directory);	
	}
}


int main(int arg, char* argv[]){
	//program is always running
	while (1){
		signal(SIGINT, parent);
		my_str ("MINISHELL:  ");
		int buf=255;
		char* dir= (char*)malloc(buf*sizeof(char));
		while (getcwd(dir,buf)==NULL){
			buf=buf*2;
			free(dir);
			dir= (char*)malloc(buf*sizeof(char));	//make sure you have enough space
		}
		directory=dir;
		my_str(dir);
		my_str("$:");
	
		size_t size=300;
		char* input= (char*)malloc(size*sizeof(char));
		int end=read(0,input,size);
		input[end]='\0';	


		char** command=my_str2vect(input);		
		if (command!=NULL && command[0]!=NULL){
			if (my_strcmp(command[0],"exit")==0){
				my_str("LEAVING NOW\n");
				exit(0);
			}
			else if(my_strcmp(command[0],"cd")==0){
				char* address= command[1];
				if (chdir(address)==-1){
					my_str("Error this directory doesn't Exist\n");
				}			
			}
			else if (my_strcmp(command[0],"help")==0){
				my_str("ls: displays files in current directory\n");
				my_str("cd: change current directory\n");
				my_str("help: displays builtin commands and uses\n");	
			}
			else{
				int pc[2];
				pipe(pc);
				pid_t child=fork();
				if (child<0){
					my_printf("error");
				}		
				if (child>0){
					signal(SIGINT, SIG_IGN);
					char cmessage[200];
                			close(pc[1]);
        			        read(pc[0],cmessage,200);
					wait(NULL);
				}
				else{
					signal(SIGINT, SIG_DFL);
					char* message="just to synchronize";				
					close(pc[0]);
					write(pc[1], message, 200);
					if(execvp(command[0], command)==-1){
						my_str("Bad function call, bad\n");
					}
					exit(0);	
				}	
			}
		}		
		free(command);
		free(input);
		free(dir);
	}
}

