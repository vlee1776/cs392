#include <stdio.h>
#include "my.h"
#include <unistd.h>

int main(){
	int ctr=0;
	while(1){
		my_printf("%d\n", ctr );
		sleep(1);
		ctr++;
	}
}
