#include "my.h"
/*
	I pledge my honor that I have abided by the Stevens Honors System. -Vincent Lee
*/
void my_int(int x){
	if (x==0){
		my_char('0');
		return;
	}
	//positive condition
	if (x>0){	
		x=x*-1;
	}
	else{
		my_char('-');
	}
	//0 condition
	
	int power=0;
	int tmp=x;
	int flag=0;
	//find the power of the number
	while (tmp<0){
		tmp=tmp/10;
		if (flag==0){
			power=1;
			flag=1;
		}
		else{
		power=power*10;
		}
	}
	while (power>=1){
		int num= x/power;//get the first number in the number
		if (num<0){
			my_char('0'+ (num*-1));
			x=x-(num*power); //truncate the number from start}
		}
		else{
			my_char('0');
		}
		power=power/10;
	}
}
