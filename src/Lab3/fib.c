#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	if (argc==1){
		printf("input number");
		return -1;
	}
	if (argc==2){
		char* num[5];
		num[0]="0";
		num[1]="1";
		num[2]="0";
		num[3]=argv[1];
		num[4]=NULL;
		execvp("./fibo",num);
	}
	else{	
		if (atoi(argv[3])-1==atoi(argv[2])){
			printf ("Answer is: %s\n", argv[1]);
			return 0;
		}
		else{	
			char buffer[10];
			char buffer2[10];
			char* num[5];
			num[0]=argv[1];
			int next= atoi(argv[0])+atoi(argv[1]);
			sprintf(buffer, "%d", next);
			num[1]=buffer;
			int add=atoi(argv[2])+1;
			sprintf(buffer2, "%d", add);
			num[2]=buffer2;
			num[3]=argv[3];
			int i=0;
			num[4]=NULL;	
			execvp("./fibo", num);
		}
	}	
	return 0;
}

