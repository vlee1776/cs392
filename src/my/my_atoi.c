#include "my.h"
#include <assert.h>
int my_atoi(char* str){
	int nxt=0;
	int ret=0;
	int sign=1;
	int i=0;
	assert(str!=NULL);
	while (str[i]!='\0'){
		int go= str[i]>='0' && str[i]<='9';
		if (nxt==1 && go==0){
			break;
		}
		if (str[i]=='-'){
			sign= sign*-1;
		}
		if (go!=0){
			nxt=1;
			if (-2147483648/10<=ret){ 
				if(-214748364==ret && str[i]>'8'){
					break;
				}
				ret= (ret*10)-(int)(str[i]-'0');
			}
			else{
				break;
			}
		}
		i++;
	}
	if (sign==1){
		if (ret==-2147483648){
			ret=ret/10;
		}
		ret=ret*-1;
	}
	return ret;
}
