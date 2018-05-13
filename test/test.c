#include "my.h"
#include <stdio.h>
#include <stdlib.h>
int main(){
	//char* x= "hello";
	//printf ("\n %p \n", &x);
	//my_printf("Hello %d %c %s %o %x %p \n",10, 'a', "awesome", 16, 16, &x);
	char** hi=my_str2vect("hello \t\t\n class,\nhow are you?");
	int i=0;
	while (hi[i]!=NULL){
		my_printf("%s",hi[i]);
		i++;
	}
}
	/*my_str(hi[0]);
	my_str(hi[1]);
	my_str(hi[2]);
	my_str(hi[3]);
	my_str(hi[4]);
	my_char('\n');*/
//	char* he=my_vect2str(hi);
//	my_str(he);
	/*
	my_str("my_strfind:");
	my_str(my_strfind ("Hello", 'l'));
	my_char ('\n');
	my_str(" my_strrfind:");
	my_str(my_strrfind ("Hello", 'l')); 
	my_char ('\n');
	my_str ("my_strcmp:");
	my_int (my_strcmp("zebra","zebras"));
	my_char ('\n');
	my_str("my_strncmp:");
	my_int (my_strncmp("zebra" ,"zebra",-1 ));
	my_char ('\n');
	my_str("my_strcpy:");
	char a[20]="hello";
	//char b[]="everybody";
	my_str (my_strcpy(a,a));
	my_char ('\n');
	my_str("my_strncpy:");
	char* c=(char*)malloc(5*sizeof(char));
	char d[]="this work";
	my_str(my_strncpy(c,d,6));
	my_str(c);
	my_char('\n');
	//char one[30]="does";
	char two[30]="Hello";
	my_str("my_strcat:");
	my_str(my_strcat(two,"world"));
	my_char ('\n');
	my_str("my_strdup");
	my_str (my_strdup("HELLO"));
	my_char ('\n');
	my_str("my_strconcat:");
	char test[]= "hello";
	my_str(my_strconcat(test,"this"));
	my_char ('\n');
	my_str("my_strnconcat: ");
	my_str (my_strnconcat("hi", "everyone",3 ));
	my_char ('\n');
	my_int(my_atoi("asdasd-sasd-2147483647-asd123"));
	//my_int(my_atoi(NULL));
		my_alpha();
	my_char('\n');
	my_digits();
	my_char('\n');
	my_str("Does this work");
	my_char('\n');
	my_int(2147483647);
	my_str("\n");
	my_str("my_num_base:");
	my_num_base(9,"RTFM");
	my_char('\n');
	my_str("my_strlen");
	my_int(my_strlen("hello "));
	my_char('\n');
	my_str("my_strindex");
	my_int(my_strindex(NULL, 'l'));
	my_char('\n');
	my_str("my_strrindex:");
	my_int(my_strrindex("hello", 'l'));
	my_char('\n');
	char hi[]= "hi"; 
	my_str("my_revstr on mutable string");
	my_int(my_revstr(hi));
	my_str(hi);
	my_char ('\n');
	my_str ("my_int:");
	my_int(30100);
	my_char ('\n');
	my_int(-2147483648);
	my_char('\n');
	my_int(-2);
	my_char('\n');
	my_str("print nothing:");
	my_num_base(-2147483648, "0123456789");
	my_num_base(0,"ASD");
	*//*
	my_str("\n");
	char* arg[4];
	arg[0]="hello";
	arg[1]="world";
	arg[2]=NULL;	
	char* hello=my_vect2str(arg);
	//hello[2]='\0';
	my_str(hello);*//*
void *ptr = malloc(1);
my_printf("A string: %s\n", "A string");
printf("Stdlib ptr: %p\n", ptr);
my_printf("my_lib ptr: %p\n", ptr);                                                                              
my_printf("Number sixes: %i %d\n", 6, 6);
my_printf("255 in hex: %x\n", 255);
my_printf("255 in hex: %X\n", 255);
my_printf("16 in octal: %o\n", 16);
my_printf("Not 16 in octal: %O\n", 16);
my_printf("The letter q: %c\n", 'q');
my_printf("%s %s%x, the universe, and everything is %d\n", "The answer to", "lif", 14, 42);
int n = my_printf("%s %x\n", "I sleep in a", 0xbed);
my_printf("Number of chars in previous: %i (expected: %i)\n", n, 15);
}
*/
