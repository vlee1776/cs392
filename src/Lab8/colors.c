#include <ncurses.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unctrl.h>

int main(){
	initscr();
	raw();
	int x;
	int y;
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
	while(1){
	//	getyx(stdscr, y,x);
		noecho();
		char c=getch();
		char ret=c;
		if (strcmp(keyname(c), "^B")==0){
			attron(A_BOLD);
		}
		else if (strcmp(keyname(c), "^C")==0){
			endwin();
			exit(0);
		}
		else if(strcmp(keyname(c), "^I")==0){
			attron(A_ITALIC);
		}
		else if(strcmp(keyname(c), "^L")==0){
			attron(A_BLINK);
		}
		else if(strcmp(keyname(c), "^U")==0){
			attron(A_UNDERLINE);
		}
		else if(strcmp(keyname(c), "^G")==0){
			attron(COLOR_PAIR(1));
		}
		else if(strcmp(keyname(c), "^K")==0){
			attron(COLOR_PAIR(3));
		}
		else if(strcmp(keyname(c), "^W")==0){
			attron(COLOR_PAIR(2));
		}
		else if(strcmp(keyname(c), "^R")==0){
			attroff(COLOR_PAIR(1));
			attroff(COLOR_PAIR(2));
			attroff(COLOR_PAIR(3));
			attroff(A_UNDERLINE);
			attroff(A_BLINK);
			attroff(A_ITALIC);
			attroff(A_BOLD);
		}	
		else{
			printw("%c", ret);
		}	
		refresh();		
	}		
	endwin();	
}
