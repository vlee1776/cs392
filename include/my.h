/* Header for libmy (Part 1) assignment. */ 
#ifndef _MY_H_ 
#define _MY_H_

#ifndef NULL 
#define NULL ((void*)0) 
#endif

#include <unistd.h> 
#include <stdlib.h>

void my_char(char); 
void my_str(char*); 
void my_int(int); 
void my_num_base(int, char* base); 
void my_alpha(); 
void my_digits();
int my_strlen(char*); 
int my_revstr(char*); 
int my_strindex(char*, char); 
int my_strrindex(char*, char);
char* my_strfind(char* , char);
char* my_strrfind(char*, char);
int my_strcmp(char*, char* );
int my_strncmp(char *, char *, int );
char *my_strcpy(char*, char*);
char *my_strncpy(char *, char*, int);
char *my_strcat(char* , char*);
char *my_strdup(char*);
char *my_strconcat(char*, char*);
char *my_strnconcat(char*, char*, int);
int my_atoi(char*);
char *my_vect2str(char **x);
char **my_str2vect(char *x);
int my_printf(char *, ...); 
#endif
