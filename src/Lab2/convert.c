#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main(){ 
	char buffer[100];
	int fd=open("encrypted.txt",O_RDONLY);
	int nread= read(fd,buffer,100);
	int w=open("output.txt", O_WRONLY);
	int i=0;
	int add=3;
	while (buffer[i]!='\0'){
		if (i%3==0){
			add=add+2;
		}	
		if (buffer[i]>='a' && buffer[i]<='z'){
			for (int z=0; z<add; z++){
				buffer[i]=buffer[i]-1;
				if (buffer[i]<'a'){
					buffer[i]='z';
				}			
			}
		}
		if (buffer[i]>='A' && buffer[i]<='Z'){
			for (int z=0; z<add; z++){
				buffer[i]=buffer[i]-1;
				if (buffer[i]<'A'){
					buffer[i]='Z';
				}			
			}
		}	
		write (w, &buffer[i], 1);
		i++;
	}
}
