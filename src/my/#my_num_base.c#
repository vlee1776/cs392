#include "my.h"
/* I pledge my honor that I have abdided by the Stevens Honor System -Vincent Lee
*/
void my_num_base(int x, char* str){
	//empty and null string	
	if (str==NULL || str[0]=='\0'){
		my_str("Error: empty or NULL char*");
		return;
	}
	int base=my_strlen(str);//base is string length	
	if (x==0 && base==1){
		return;
	}
	if (x==0 && base!=1){
		my_char(str[0]);
		return;
	}
	//positive number
	if (x>0){
		x=x*-1;
	}
	else{
		my_char('-');
	}
	//unary condition
	if (base==1){
		x=x*-1;
		for (int z=0; z<x; z++){
			my_char(str[0]);
		}
		return;
	}
	int power=0;
	int tmp=x;
	//what power is your number
	int flag=0;
	while (tmp<0){
		tmp=tmp/base;
		if (flag==0){
			power=1;
			flag=1;
		}
		else{
		power=power*base;
		}
	}
	while (power>=1){
		int num= x/power;//get first number
		if (num<0){
			my_char(str[num*-1]); 
			x=x-(num*power); //truncate the start
		}
		else{
			my_char(str[0]);
		}
		power=power/base;
	}
}


