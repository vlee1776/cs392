#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <ncurses.h>
#include "list.h"
#include "my.h"
#include <strings.h>
#include <string.h>

char* directory;
int flag=0;
int y,x;
int maxx;
int maxy;
int none=1;	
pid_t child2;

/*
I pledge my honor that I have abided by the Stevens Honor System. -Vincent Lee
*/

//check if a string is only whitespace
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

//signal handling fo ctrl c
void parent(int sig){
	if (sig==SIGINT){
		//set up the colors 	
		init_pair(1,COLOR_GREEN,-1);
		init_pair(2,COLOR_CYAN, -1);
		init_pair(3,COLOR_RED,-1);
		getyx(stdscr, y,x);
		printw("^C");
		//turn off the one that was on you know it was on
		attroff(COLOR_PAIR(1));
		//make a new line
		y+=1;
		//scroll up if youre at the end
		if (y==maxy){
			scroll(stdscr);
			y--;
		}
		x=0;
		move(y,x);
		refresh();
		//turn on colors and print the shell
		attron(COLOR_PAIR(3));
		printw ("MINISHELL:  %");
		attroff(COLOR_PAIR(3));
		attron(COLOR_PAIR(2));
		printw("%s$:",directory);	
		refresh();
		//turn on flag saying ctrl c was pressed
		flag=1;
		//get the maximum x you can be at
		getyx(stdscr,y,x);
		move(y,x);
		maxx=x;
		signal(SIGINT, parent);
		attroff(COLOR_PAIR(2));
		attron(COLOR_PAIR(1));
		nodelay(stdscr,TRUE);
	}
}

void endchild(int sig){
	kill(SIGINT,child2);
}

//empty linked list into a file
void save(s_node** head){
	FILE* file= fopen(".nsmshistory","w+");
	s_node* temp=*head;
	while (temp!=NULL){
		char* string=(char*)temp->elem;
		fprintf(file,"%s\n",string);
		bzero((char*)string,strlen(string));	
		temp=temp->next;
	}
	fclose(file);				 
}

//input is never freed because it is put into the nodes of the list
int main(int arg, char* argv[]){
	//program is always running
	s_node **history=NULL;
	int histpos=0;
	//so much easier to load here then in a function
	//function was giving me bad output
	FILE* file= fopen(".nsmshistory","r");
	size_t strl=10;
	char* string=(char*)malloc(strl*sizeof(char));
	while (getline(&string,&strl,file)>0){
		char* word=my_strdup(string);
		word[strlen(string)-1]='\0';
		if (none==1){	
			s_node* add=new_node(word,NULL,NULL);
			history=&add;
			none=0;
		}
		else{
			s_node* add=new_node(word,NULL,NULL);
			append(add,history);
		}
	}
	bzero((char*)string,strlen(string));
	free(string);
	string=NULL;
	fclose(file);
	if(history!=NULL){	
		histpos=count_s_nodes(*history);
	}
	//end of loading
	initscr();
	cbreak();
	noecho();
	scrollok(stdscr,TRUE);
	getyx(stdscr, y,x);
	//default colors to get terminal backrground as color
	use_default_colors();	
	start_color();
	init_pair(1,COLOR_GREEN,-1);
	init_pair(2,COLOR_CYAN, -1);
	init_pair(3,COLOR_RED,-1);
	char *temp= NULL;	
	char* clipboard=NULL;
	int copy=0;
	//get the max y to check if your over the screen
	maxy=getmaxy(stdscr);	
	//loop the program
	while (1){	
		signal(SIGINT, parent);	
		getyx(stdscr, y,x);
		attron(COLOR_PAIR(3));
		printw ("MINISHELL:  ");
		attroff(COLOR_PAIR(3));
		int buf=255;
		char* dir= (char*)malloc(buf*sizeof(char));
		while (getcwd(dir,buf)==NULL){
			buf=buf*2;
			free(dir);
			dir= (char*)malloc(buf*sizeof(char));	//make sure you have enough space
		}
		attron(COLOR_PAIR(2));
		directory=dir;
		printw(dir);
		printw("$:");
		refresh();
		attroff(COLOR_PAIR(2));
		attron(COLOR_PAIR(1));
		//get string from stdin 	
		int size=10;
		char *input=(char*)malloc(size*sizeof(char));	
		bzero((char*)input,size);
		input[0]='\0';
		int pos=0;
		char* buffer=(char*)malloc(size*sizeof(char));
		buffer[0]='\0';
		bzero((char*)buffer,size);
		getyx(stdscr,y,x);
		maxx=x;
		//this is for the clear line call
		if (temp!=NULL){
			input=my_strdup(temp);
			free(temp);
			temp=NULL;
			buffer=my_strdup(input);
			printw(input);
			refresh();		
		}
		while (1){
			nodelay(stdscr,FALSE);
			char c=getch();	
			//if ctrl c was pressed while input
			if (flag==1){
				flag=0;	
				free(input);
				size=10;
				input=(char*)malloc(size*sizeof(char));
				pos=0;
				getyx(stdscr,y,x);
				move(y,x);
				copy=0;
			}
			//clear everything but the current line
			if (strcmp(keyname(c), "^L")==0){
				copy=0;
				temp=my_strdup(input);
				free(input);
				input="clear";
				getyx(stdscr, y,x);
				y+=1;
				x=0;
				if (y==maxy){
					scroll(stdscr);		
					y--;
				}
				x=0;
				move(y,x);
				refresh();
				break;	
			}
			//move to the start of line
			else if (strcmp(keyname(c), "^A")==0){
				copy=0;
				getyx(stdscr, y,x);
				x=maxx;
				move(y,x);
				refresh();	
			}
			//move to the end of line
			else if (strcmp(keyname(c), "^E")==0){
				copy=0;
				getyx(stdscr, y,x);
				x=maxx+pos;
				move(y,x);
				refresh();
			}
			//clipboard a word
			else if (strcmp(keyname(c), "^W")==0){
				getyx(stdscr,y,x);
				int total=strlen(input);
				int ipos=x-maxx;
				int last=x-maxx;
				if (x!=maxx){
					int cursor=x;//cursor of where you took the word from
					char first[strlen(input)+1];
					char second[strlen(input)+1];
					char ret[strlen(input)+1];
					bzero((char*)ret,strlen(input+1));
					bzero((char*)second,strlen(input+1));
					bzero((char*)first,strlen(input+1));	
					if (clipboard!=NULL && copy==0){
						free(clipboard);
						clipboard=NULL;
					}
					//if this is the first copy take the word and fix the input find the start and last
					if (ipos!=0){
						ipos--;
					}
					while (ipos>0 && (input[ipos]==' '|| input[ipos]=='\0')){
						ipos--;	
					}
					while (ipos>0 && input[ipos]!=' '){
						ipos--;
					}
					if (ipos!=0){
						ipos++;
					}
					my_strncpy(first,input,ipos);
					int secpos=0;
					int retpos=0;
					first[ipos]='\0';
					while (ipos!=last){
						ret[retpos]=input[ipos];
						ipos++;
						retpos++;
					}
					ret[retpos]='\0';
					cursor=cursor-strlen(ret);//find the place where your cursor is after subtracting word
					while(last!=total){
						second[secpos]=input[last];
						secpos++;
						last++;
					}
					second[last]='\0';
					x=total+maxx;
					//clear output
					while (x!=maxx){
						x--;
						move(y,x);
						printw(" ");
						refresh();
						move(y,x);
					}
					free(input);
					input=my_strconcat(first,second);
					size=strlen(input);
					pos=size;
					//if copy is 0 just make the word the clipboard
					if (copy==0){
						clipboard=my_strdup(ret);
					}
					//append the word if you should add it
					else{
						char* t=my_strconcat(ret,clipboard);
						free(clipboard);
						clipboard=t;
					}
					copy=1;	
					printw(input);
					refresh();
					x=cursor;
					move(y,x);
					refresh();
				}
			}
			//clipboard a line
			else if (strcmp(keyname(c), "^U")==0){
				getyx(stdscr,y,x);
				int total=strlen(input);
				int last=x-maxx;
				if (x!=maxx){
					int cursor=x;//cursor of where you took the word from
					char first[strlen(input)+1];
					char second[strlen(input)+1];
					bzero((char*)second,strlen(input+1));
					bzero((char*)first,strlen(input+1));	
					if (clipboard!=NULL && copy==0){
						free(clipboard);
						clipboard=NULL;
					}	
					my_strncpy(first,input,last);
					int secpos=0;
					first[last]='\0';
					cursor=cursor-last;//find the place where your cursor is after subtracting word
					while(last!=total){
						second[secpos]=input[last];
						secpos++;
						last++;
					}
					second[secpos]='\0';
					x=total+maxx;
					while (x!=maxx){
						x--;
						move(y,x);
						printw(" ");
						refresh();
						move(y,x);
					}
					free(input);
					input=my_strdup(second);
					size=strlen(second);
					pos=size;
					//if copy is 0 just make the word the clipboard
					if (copy==0){
						clipboard=my_strdup(first);
					}
					//append the word if you should add it
					else{
						char* t=my_strconcat(first,clipboard);
						free(clipboard);
						clipboard=t;
					}
					copy=0;	
					printw(input);
					refresh();
					x=cursor;
					move(y,x);
					refresh();
				}
				copy=0;
			}
		
			//paste the clipboard
			else if (strcmp(keyname(c), "^Y")==0){
				copy=0;
				getyx(stdscr, y,x);
				int str= x-maxx;
				int cursor=x;
				if (clipboard!=NULL){
					cursor=x+strlen(clipboard);
				}
				char first[strlen(input)+1];
				char second[strlen(input)+1];
				bzero((char*)first,strlen(input)+1);
				bzero((char*)second,strlen(input)+1);
				int ct=0;
				my_strncpy(first,input,str);
				while (input[str]!='\0'){
					second[ct]=input[str];
					str++;
					ct++;	
				}	
				char* add=my_strconcat(first,clipboard);
				free(input);
				input=my_strconcat(add,second);
				size=my_strlen(input);
				pos=size;
				free(add);
				while (x!=maxx){
					x--;
					move(y,x);
					printw(" ");
					refresh();
					move(y,x);
				}
				printw(input);
				refresh();
				x=cursor;
				move(y,x);
				refresh();	
				if ( (histpos==0 && none==1) || histpos==count_s_nodes(*history)){
					free(buffer);
					buffer=my_strdup(input);
				}	
			}
			//input was an arrow key
			else if (strcmp(keyname(c),"^[")==0){
				c=getch();
				c=getch();
				//input was up arrow
				copy=0;
				if (c=='A'){	
					refresh();
					getyx(stdscr,y,x);	
					x=strlen(input)+maxx;	
					move(y,x);
					refresh();
					while (x!=maxx){
						x--;
						move(y,x);
						printw(" ");
						refresh();
						move(y,x);
					}
					//load buffer if nothing is entered previously
					if (histpos==0 && none==1){		
						printw(input);
						histpos=0;
					}	
					//load previous never go above first entry
					else{
						histpos--;
						if (histpos==-1){
							histpos=0;
						}
						char* val=(char*)(elem_at(*history,histpos));		
						size= strlen(val);
						char* string=my_strdup(val);
						free(input);
						input=string;
						pos=size;
						printw(val);
						refresh();
					}
				}
				//if arrow was down
				else if (c=='B'){
					getyx(stdscr,y,x);
					x=strlen(input)+maxx;
					move(y,x);
					refresh();
					while (x!=maxx){
						x--;
						move(y,x);
						printw(" ");
						refresh();
						move(y,x);
					}
					//if your at the end load the buffer
					if( (histpos==0 && none==1) || histpos==count_s_nodes(*history) ){
						free(input);
						input= my_strdup(buffer);
						size=strlen(buffer);
						pos=size;
						printw(input);
						refresh();
					}
					//if your going to the end print buffer
					else if (histpos+1==count_s_nodes(*history)){
						histpos++;
						free(input);
						input= my_strdup(buffer);
						size=strlen(buffer);
						pos=size;
						printw(input);
						refresh();
					}
					//just get the next string
					else{
						histpos++;
						char* val=(char*)(elem_at(*history,histpos));	
						size= strlen(val);
						refresh();
						char* string=my_strdup(val);
						free(input);
						input=string;
						pos=size;	
						printw(val);
						refresh();
					}
				}
				//go left
				else if (c=='D'){
					getyx(stdscr,y,x);
					if (x!=maxx){
						x--;
						move(y,x);	
						refresh();
					}
				}//go right
				else if (c=='C'){
					getyx(stdscr,y,x);
					if (x<maxx+strlen(input)){
						x++;
						move(y,x);
						refresh();
					}
				}
			}
			//delete button	
			else if (strcmp(keyname(c),"^?")==0){
				copy=0;	
				getyx(stdscr,y,x);
				int cursor=x;
				int postemp=x-maxx;
				int total=strlen(input)+maxx;
				if (cursor!=maxx){
					if (pos==(x-maxx)){
						pos--;
						input[pos]='\0';
					}
					else{
						postemp--;
						while (input[postemp]!='\0'){
							input[postemp]=input[postemp+1];
							postemp++;
						}
						pos-=1;
						input[pos]='\0';
					}
					x=total;
					while (x!=maxx){
						x--;
						move(y,x);
						printw(" ");
						refresh();
						move(y,x);
					}	
					printw(input);
					refresh();
					cursor--;
					x=cursor;
					move(y,x);
					refresh();
					if ( (histpos==0 && none==1) || histpos==count_s_nodes(*history)){
						if (buffer!=NULL){
							free(buffer);
						}
					buffer=my_strdup(input);
					}	
				}	
							
			}
			//enter into linked list
			else if (c=='\n'){
				copy=0;
				free(buffer);
				//input[pos]='\0';
				getyx(stdscr,y,x);
				y+=1;
				x=0;
				if (y==maxy){
					scroll(stdscr);	
					y--;
				}
				x=0;
				move(y,x);
				refresh();
				//store input into linked list
				if (none==1 && whitespace(input)==0){
					s_node* first=new_node(input, NULL,NULL);
					history=&first;
					none=0;
					histpos=1;
				}
				else if (whitespace(input)==0){
					s_node* add=new_node(input,NULL, NULL);
					append(add, history);
					histpos=count_s_nodes(*history);
				}
				
				break;
			}
			//add to working word
			else if (c!='\t'){
				copy=0;	
				getyx(stdscr,y,x);
				int cursor=x+1;
				int postemp=pos;
				int currx=x-maxx;
				refresh();
				if (currx!=(pos)){
					postemp++;
					while (currx!=postemp){
						input[postemp]=input[postemp-1];
						postemp--;
					}
					input[postemp]=c;
					pos++;
				}
				else{
					input[pos]=c;
					pos++;
					cursor=maxx+pos;
				}
				while (x!=maxx && x>=maxx){
					x--;
					move(y,x);
					printw(" ");
					refresh();
					move(y,x);
				}
				if (pos==size-1){
					size=size*3;
					char* str= (char*)malloc(size*sizeof(char));
					bzero((char*)str, size);
					my_strcpy(str,input);
					free(input);
					input=str;	
					input[size-1]='\0';
				}
				input[pos]='\0';
				printw(input);
				if ( (histpos==0 && none==1) || histpos==count_s_nodes(*history)){
					if (buffer!=NULL){
						free(buffer);
					}
					buffer=my_strdup(input);
				}
				refresh();
				x=cursor;
				move(y,x);
			}	
		}

		//set color and work as minishell does!
		attroff(COLOR_PAIR(1));
		char** command=my_str2vect(input);
		char *enter= my_vect2str(command);
		attron(COLOR_PAIR(2));		
		if (command!=NULL && command[0]!=NULL){
			if (my_strcmp(command[0],"exit")==0){
				endwin();
				free(enter);
				free(command);
				free(dir);
				if (none==0){
					save(history);
				}
				empty_list(history);
				exit(0);
			}
			else if(my_strcmp(command[0],"cd")==0){
				char* address= command[1];
				if (chdir(address)==-1){
					printw("Error this directory doesn't Exist");		
					getyx(stdscr, y,x);
					y+=1;
					if (y==maxy){
						scroll(stdscr);	
						y--;
					}
					x=0;
					move(y,x);
					refresh();
				}			
			}
			else if (my_strcmp(command[0],"help")==0){
				printw("ls: displays files in current directory");
				getyx(stdscr, y,x);
				y+=1;
				if (y==maxy){
					scroll(stdscr);	
					y--;
				}
				x=0;
				move(y,x);
				refresh();
				printw("cd: change current directory");
				y+=1;
				if (y==maxy){
					scroll(stdscr);	
					y--;
				}
				x=0;
				move(y,x);
				refresh();
				printw("help: displays builtin commands and uses");	
				getyx(stdscr, y,x);
				y+=1;
				if (y==maxy){
					scroll(stdscr);	
					y--;
				}
				x=0;
				move(y,x);
				refresh();	
			}
			else if (my_strcmp("clear",command[0])==0){
				clear();
				x=0;
				y=0;
				refresh();
			}
			else{	
				int pc[2];
				int std[2];
				int block[2];
				pipe(std);
				pipe(pc);
				pipe(block);
				/*fork twice 
				first child runs the program and sets its stdin to a pipe
				parent reads input from child and prints it out
				second child reads input from stdin and writes it to the second child
				second child will be killed by first parent when first child dies dies 
				*/
				pid_t child=fork();
				if (child<0){
					printw("error");
					exit(0);
				}	
				//parent	
				else if (child>0){
					child2=fork();
					if (child2<0){
						perror("child2 fork()");
					}
					//parent
					else if (child2>0){	
						signal(SIGCHLD, endchild);
						signal(SIGINT, SIG_IGN);
						char cmessage[2];
						close(pc[1]);
						cmessage[1]='\0';
						//reads the input from exec	
						while(read(pc[0],cmessage,1)>0){	
							
							//kill the child if exec is done; that is dont let it wait to getch	
							if (cmessage[0]!='\n'){
								printw(cmessage);
								refresh();
							}	
							else{
								getyx(stdscr,y,x);
								y+=1;
								if (y==maxy){
									scroll(stdscr);	
									y--;
								}
								x=0;
								move(y,x);	
								refresh();
								
							}
							if (waitpid(child,NULL,WNOHANG)!=0 && waitpid(child2,NULL,WNOHANG)==0){
								kill(child2,SIGINT);
							}
						}
						close(pc[0]);
						wait(NULL);		
					}
					
					//child2 run while exec is still going on that is the programing is waiting for input
					else{	
						signal(SIGCHLD, endchild);
						signal(SIGINT, SIG_DFL);
						size_t len=200;
						char* send=(char*)malloc(len*sizeof(char));
						bzero((char*)send,len);
						int ctr=0;
						close(block[1]);
						close(std[0]);	
						char nonsense[200];
						read(block[0],nonsense,9);
						while(1){
							char c=getch();	
							printw("%c",c);
							refresh();
							send[ctr]=c;
							ctr++;
							if (c=='\n'){
								ctr++;
								send[ctr]='\0';
								write(std[1],send,200);
								ctr=0;
								bzero((char*)send,200);	
							}
							
						}
						close(std[1]);
						close(block[0]);
						exit(0);
					}
				}
				//child that execs
				else{
					signal(SIGINT, SIG_DFL);
					echo();
					close(0);
					dup2(pc[1],1);	
					dup2(pc[1],2);
					dup2(std[0],0);
					char* ok[4];
					if (strcmp(command[0],"ls")==0){	
						enter[0]=' ';
						enter[1]=' ';
						char* add="ls -C";
						char* swap=my_strconcat(add,enter);
						free(enter);
						enter=swap;
						refresh();	
					}
					ok[0]="sh";
					ok[1]="-c";
					ok[2]=enter;
					ok[3]=NULL;
					write(block[1],"nonsense",9);	
					execvp(ok[0],ok);	
				}	
			}
		}
		free(enter);
		attroff(COLOR_PAIR(2));	
		free(command);
		free(dir);
	}
}

