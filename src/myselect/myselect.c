#define _GNU_SOURCE
#include <ncurses.h>
#include "my.h"
#include "list.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

/*
I pledge my honor that I have abided by the Stevens Honor System. -Vincent Lee
*/
int maxx,maxy,column,tmp,maxcolumns,columns,lastcol,elements,longest;
char ** list;
int* chosen2;


//resize the window handler
void resize(int sig){
	//endwin to let ncurses recognize change in screen size
	clear();
	refresh();
	def_prog_mode();
	endwin();
	reset_prog_mode();
	refresh();
	//get the maximum number of columns
	getmaxyx(stdscr,maxy,maxx);	
	maxcolumns= maxx/longest;
	columns=elements/maxy;
	lastcol=elements%maxy;
	if (lastcol>0){
		columns++;
	}
	else{
		lastcol=maxy;
	}
	int totalelements= (maxy-1)*maxcolumns;
	//screen not big enough
	if (elements>totalelements){
		printw("please enlarge the window");
		refresh();
	}
	//print the words onto screen
	else{
		tmp=0;
		int x,y;
		column=0;
		getyx(stdscr, y,x);
		//print columns first
		while (tmp!=elements){
			if (chosen2[tmp]==1){
				attron(A_STANDOUT);
			}
			printw(list[tmp]);
			attroff(A_STANDOUT);
			refresh();	
			tmp++;
			if (y==(maxy-1)){
				column++;
				y=0;
				x=column*longest;
				move(y,x);
				refresh();
			}
			else{
				y++;
				move(y,x);
				refresh();
			}
		}
		//reset to 0 and start
		tmp=0;
		y=0;
		x=0;
		column=0;
		move(y,x);
		attron(A_UNDERLINE);
		if (chosen2[tmp]==1){
			attron(A_STANDOUT);
		}
		printw(list[tmp]);
		attroff(A_UNDERLINE);
		attroff(A_STANDOUT);
		move(y,x);
		refresh();
	}
}


int main(int argc, char* argv[]){
	signal(SIGWINCH,resize);
	//the ls command according to the vector in arguments
	if (argc<2){
		printf("please input a parameter to select\n");
		exit(0);
	}
	char* command[argc];
	int pos=1;
	command[0]="ls";
	while (pos!=argc){
		command[pos]=argv[pos];
		pos++;
	}
	command[pos]=NULL;
	
	int pc[2];
	int p2[2];
	pipe(p2);
	pipe(pc);
	//fork twice one to check for error the other to call exec
	pid_t child= fork();
	if (child<0){
		perror("forking first child");
		exit(1);
	}
	//second child that does the work
	else if(child>0){
		pid_t child2=fork();
		if (child2<0){
			perror("forking second child");
			exit(1);
		}
		//successful exec
		else if (child2>0){
			close(pc[1]);
			char temp[1];
			int len=10;
			char* message=(char*)malloc(len*sizeof(char));
			int ctr=0;
			//read from the pipe and kill the error child
			while( read(pc[0],temp,1)>0){
				kill(child2,SIGINT);
				message[ctr]=temp[0];
				ctr++;
				if (ctr==len-1){
					message[ctr]='\0';
					len= len*2;
					char* tp=(char*)malloc(len*sizeof(char));
					strcpy(tp,message);
					free(message);
					message=tp;
				}
			}
			//get data
			list= my_str2vect(message);	
			int size=0;
			longest=strlen(list[size]);
			//get the length words and the longest string
			while(list[size]!=NULL){
				if (strlen(list[size])>longest){
					longest=strlen(list[size]);
				}
				size++;
			}
			longest++;
			//hold which files have been selected
			int chosen[size];
			for (int i=0;i<size;i++){
				chosen[i]=0;
			}
			chosen2=chosen;
			//time for ncurses
			initscr();
			curs_set(0);
			noecho();
			raw();

			refresh();
			elements= size;
			//get the maximum number of columns
			getmaxyx(stdscr,maxy,maxx);	
			maxcolumns= maxx/longest;
			columns=elements/maxy;
			lastcol=elements%maxy;
			if (lastcol>0){
				columns++;
			}
			else{
				lastcol=maxy;
			}
			int totalelements= (maxy-1)*maxcolumns;
			//loop if the screen is too small
		
			if(elements>totalelements){
				printw("please enlarge the window");
				refresh();
				//handle resizing here
				//once its big enough break
				while(elements>totalelements){
					getmaxyx(stdscr,maxy,maxx);
					maxcolumns= maxx/longest;	
					totalelements=(maxy-1)*maxcolumns;
					timeout(50);
					char c= getch();
					if (c=='\n'){
						endwin();
						exit(0);
					}
					if (c==27){
						timeout(50);
						c=getch();
						if (c==-1){
							endwin();
							exit(0);
						}
					}
				}
			}
			tmp=0;
			int x,y;
			column=0;
			getyx(stdscr, y,x);
			//print the elements column first
			while (tmp!=elements){
				printw(list[tmp]);
				refresh();	
				tmp++;
				if (y==(maxy-1)){
					column++;
					y=0;
					x=column*longest;
					move(y,x);
					refresh();
				}
				else{
					y++;
					move(y,x);
					refresh();
				}
			}
			//reset to 0 and start
			tmp=0;
			y=0;
			x=0;
			move(y,x);
			attron(A_UNDERLINE);
			printw(list[tmp]);
			attroff(A_UNDERLINE);
			move(y,x);
			refresh();
			//read keyboard input
			int flag=0;
			column=0;
			while(1){
				attroff(A_STANDOUT);
				attroff(A_UNDERLINE);
				getyx(stdscr,y,x);
				char c=getch();
				//if enter exit but print the works out first
				if (c=='\n'){
					flag=1;
					break;
				}	
				//if space mark that it was marked in the array and highlight it
				else if (c==' '){
					if (chosen[tmp]==0){
						attron(A_STANDOUT);
						chosen[tmp]=1;
						printw(list[tmp]);
						attroff(A_STANDOUT);
						if (y==maxy-1){
							y=0;
							tmp=tmp-(maxy-1);
						}
						else if (y==lastcol-1 && column==(columns-1)){
							y=0;
							tmp=tmp-(lastcol-1);
						}
						else{
							y++;
							tmp++;
						}	
						move(y,x);
						attron(A_UNDERLINE);
						if (chosen[tmp]==1){
							attron(A_STANDOUT);
						}
						printw(list[tmp]);
						move(y,x);
						refresh();	
					}
					else{
						attroff(A_STANDOUT);
						attron(A_UNDERLINE);
						printw(list[tmp]);
						chosen[tmp]=0;
						move(y,x);
						refresh();
					}
				}
				//esacpe keys
				else if (c==27){
					//timeout the escape so if its no timeout then its an arrow
					timeout(50);
					char s=getch();
					//escape key
					if (s==-1){
						break;
					}
					//arrows
					else{
						c=getch();
						//if up
						if(c=='A'){
							//general function 
							if (chosen[tmp]==1){
								attron(A_STANDOUT);
							}
							printw(list[tmp]);
							attroff(A_STANDOUT);
							move(y,x);
							//regular movement
							if (y!=0){
								y--;
								tmp--;
							}
							//loop to bottom
							else{
								
								tmp=column*(maxy)+maxy-1;
								y=maxy-1;
								//loop to bottom of last column	
								if (column==columns-1){
									y=lastcol-1;
									tmp=column*(maxy)+lastcol-1;
								} 
							}
							move(y,x);
							if (chosen[tmp]==1){
								attron(A_STANDOUT);
							}
							attron(A_UNDERLINE);
							printw(list[tmp]);
							move(y,x);
							refresh();
                                                } 
						//down button
						else if (c=='B'){	
							if (chosen[tmp]==1){
								attron(A_STANDOUT);
							}
							printw(list[tmp]);
							attroff(A_STANDOUT);
							move(y,x);
							//loop to top
							if (y==maxy-1){
								y=0;
								tmp=tmp-(maxy-1);
							}
							//last column loop to top
							else if (y==lastcol-1 && column==(columns-1)){
								y=0;
								tmp=tmp-(lastcol-1);
							}
							//regular movement
							else{
								y++;
								tmp++;
							}
							move(y,x);
							attron(A_UNDERLINE);
							if (chosen[tmp]==1){
								attron(A_STANDOUT);
							}
							printw(list[tmp]);
							move(y,x);
							refresh();
						}	
						//left movement
						else if(c=='D'){
							if (chosen[tmp]==1){
								attron(A_STANDOUT);
							}
							printw(list[tmp]);
							attroff(A_STANDOUT);
							//general movement
							if (x!=0){
								x=x-longest;		
								tmp=tmp-maxy;
								column--;
							}
							//leftmost condition
							else{
								x=0;
								y=0;
								tmp=0;
							}
							move(y,x);
							if (chosen[tmp]==1){
								attron(A_STANDOUT);
							}
							attron(A_UNDERLINE);
							printw(list[tmp]);
							move(y,x);
							refresh();
                                                }
						//right movement
						else if (c=='C'){
							if (chosen[tmp]==1){
								attron(A_STANDOUT);
							}
							printw(list[tmp]);
							attroff(A_STANDOUT);
							//regular column
							if (column!=columns-1){
								if (tmp+maxy<size){
									x=x+longest;	
									tmp=tmp+maxy;
									column++;
								}
							}
							//rightmost conditon
							else{
								y=lastcol-1;
								tmp=size-1;
							}
							move(y,x);
							attron(A_UNDERLINE);
							if (chosen[tmp]==1){
								attron(A_STANDOUT);
							}
							printw(list[tmp]);
							move(y,x);
							refresh();
						}
					}
				}				
				else {
				//do nothing ok great
				}
				timeout(-1);
			}
			endwin();
			//printing 
			if (flag==1){
				for (int i=0; i<size; i++){
					if (chosen[i]==1){
						printf("%s ",list[i]);
					}
				}
				printf("\n");
                        }
			exit(0);
		}
		//if a pipe reads error exit
		else{	
			close(p2[1]);
			char temp[1];
			read(p2[0],temp,1);
			printf("Error no files exist");
			kill (getppid(),SIGINT);
			exit(0);
		}
	}
	//exec and output goes to pipes
	else{
		close(pc[0]);
		close(p2[0]);
		dup2(pc[1],1);
		dup2(p2[1],2);
		execvp(command[0],command);
	}
}
