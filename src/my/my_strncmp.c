#include "my.h" 
int my_strncmp(char* a, char* b, int n){
	if (a==NULL && b==NULL){
		return 0;
	}
	if (a==NULL){
		return -1;
	}
	if (b==NULL){
		return 1;
	}
	if (n<=0){
		n=0;
	}
	int i=0; 
	while (a[i]!='\0' && b[i]!='\0' && i<n){
		int dif= (int)a[i]-(int)b[i];
		if (dif!=0){
			return dif;
		}
	i++;	
	}
	if (i==n){
		return 0;
	}
	else{	
		return a[i]-b[i];
	}
}
