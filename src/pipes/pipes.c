#include "my.h"
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

//I pledge my honor that I have abided by the Stevens Honor System. -Vincent Lee

int main(int argc, char* argv[]){
	//parent process
	if (argc==1){
		my_str("ERROR: add more arguments after the system call\n");
		exit(0);
	}
	//get the message
	char **str= &(argv[1]);	
	char* message= my_vect2str(str);

	//create pipe from parent to child
	int pc[2];
	if (pipe(pc)==-1){
		perror("parent2child pipe");
		exit(1);
	}

	//print parent
	my_str("Parent: ");
	my_str(message);
	my_char ('\n');
	/*	
	my_str("ParentID:");
	my_int(getpid());
	my_str("\n");
	*/

	//create fork 
	pid_t child= fork();	
	//parent
	if (child>0){	
		//parent passes the message
		close(pc[0]);
		write(pc[1], message, 200); 
		wait(NULL);
		exit(0);
	}
	
	//child
	else if (child==0){
		//read and do the child printing
		char cmessage[200];
		close(pc[1]);
		read(pc[0],cmessage,200);
		my_str("Child: ");
		my_str(cmessage);
		my_char ('\n');	
		/*
		my_str("ChildID:");
		my_int(getpid());
		my_str("\n");
		*/

		//make child to grandchild pipe 
		int cg[2];
		if (pipe(cg)==-1){
			perror("child2grand pipe");
			_exit(1);
		}	
		//make grandchild
		pid_t grand= fork();
		//child
		if (grand>0){	
			//pass the message to grandchild	
			close(cg[0]);
			write(cg[1],cmessage,200);
			wait(NULL);
			_exit(0);
		}
		//grandchild
		else if (grand==0){
			//do the grand child printing	
			char gmessage[200];
			close(cg[1]);
			read(cg[0],gmessage,200);
			my_str("Grandchild: ");
			my_str(gmessage);
			my_char ('\n');	
			/*
			my_str("GrandChildID:");
			my_int(getpid());
			my_str("\n");
			*/
			_exit(0);	
		}
		else{	
			perror("grandchild");
			exit(1);
		}
	
	}
	//child failed
	else{
		perror("child");
		exit(1);
	}	
}
