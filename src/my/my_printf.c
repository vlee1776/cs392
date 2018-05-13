#include "my.h"
#include <stdio.h>
#include <stdarg.h>

void my_octal(int i){

}

void my_float(float in){
	int big= in;
	my_int(big);
	in=in- big;
	while(in>0){
		in=in*10;
		int f= (int)in;
		my_int(f);
		in= in-f;	
	}	
}
int my_printf(char* format, ...){
	int size=0;
	va_list args;
	int len=0;
	va_start(args, format);
	while (format[size]!='\0'){
		if (format[size]!='%'){
			my_char(format[size]);
			len++;
		}
		else{
			size++;
			if (format[size]==' '){
			my_char('%');
			len++;
			}
			else if (format[size]=='i' || format[size]=='d'){
			int i=va_arg(args,int);
			my_int(i);
				while (i!=0){
					i=i/10;
					len++;	
				}
			}
			else if (format[size]=='c'){
			char ret= va_arg(args,int);
			my_char(ret);
			len++;
			}
			else if (format[size]=='s'){
			char* ret= va_arg(args,char*);
			my_str(ret);
			len=len+my_strlen(ret);
			}
			else if(format[size]=='f'){
			float ret= va_arg(args,double);
			my_float(ret);
			}
			else if (format[size]=='o' || format[size]=='O'){
			int ret= va_arg(args,int);
			my_num_base(ret,"01234567");
				while (ret!=0){
					ret=ret/8;
					len++;
				}	
			}
			else if (format[size]=='x' ||format[size]=='p'){
			long ret= va_arg(args,long);
			if (format[size]=='p'){
				my_str("0x");
			}
			my_num_base(ret,"0123456789abcdef");	
				while (ret!=0){
					ret=ret/16;
					len++;
				}	
			}
			else if (format[size]=='X'){
			long ret= va_arg(args,long);
			my_num_base(ret,"0123456789ABCDEF");	
				while (ret!=0){
					ret=ret/16;
					len++;
				}	
			}
		}
		size++;
	}
	return len;
}
