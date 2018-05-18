#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "list.h"
#include "my.h"
#include <sys/select.h>

//I pledge my honor that I have abided by the Stevens Honor System- Vincent Lee


char* appendpre(char* string){
	int len=my_strlen(string);
	char ret[11];
	char temp[11]="0";
	sprintf(ret, "%i", len);
	while (my_strlen(ret)!=10){
		my_strcat(temp,ret);
		my_strcpy(ret, temp);
		bzero((char*)temp,10);
		temp[0]='0';
	}
	return (my_strconcat(ret,string));	
}

int whitespace(char *string){
	int i=0;
	while (string[i]!='\0'){
		if (string[i]=='\t' || string[i]==' '){
			i++;
		}
		else
			return 0;
	}
	return 1;
}
int main(int argc, char* argv[]){
	int socketfd; 
	int  port;
	struct sockaddr_in serv_addr;	
	//set of file descriptors
	fd_set fdset;
	fd_set temp;

	//simulate dictionary
	//linked list
	struct s_node* first;
	struct s_node** head= &first;
	//corresponding name	
	struct s_node* str;
	struct s_node** strhead= &str;
		
	if (argc!=2){
		printf("Useage: give me a port\n");
		exit(1);
	}

	//create socket with stream
	socketfd=socket(AF_INET, SOCK_STREAM, 0);
	first=new_node(&socketfd,NULL,NULL);
	char* s= "server";
	str= new_node(s, NULL,NULL);
	if (socketfd<0){
		perror ("Error making socket\n");
		exit(1);
	}
	//clear buffer
	bzero((char *)&serv_addr,sizeof(serv_addr));
	
	//port number
	port=atoi(argv[1]);

	//fill in server information
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(port);

	//bind socket to server
	if (bind(socketfd,(struct sockaddr*) &serv_addr, sizeof(serv_addr))<0){
		perror("Error binding\n");
		exit(1);
	}
	//listen for connections
	listen(socketfd,5);

	/* Figure out how to accept multiple clients without blocking: SELECT!*/
	FD_ZERO(&fdset);
	FD_SET(socketfd, &fdset);
	//int max=socketfd;
	//max++;
	// run all the time	
	while(1){
		temp=fdset;
		//select changes
		if (select(FD_SETSIZE, &temp, NULL, NULL,NULL)<0){
			perror("Select()");
			exit(1);
		}
		//check the set for changes
		for (int i=0; i<FD_SETSIZE; i++){
			int flag=0;
			if (FD_ISSET(i, &temp)){
				//new socket connection
				if (i==socketfd){
					struct sockaddr_in client_addr;
					socklen_t clientlen=sizeof(struct sockaddr_in);
					int* newfd= (int*)malloc(sizeof(int));
					*newfd=accept(socketfd, (struct sockaddr *)&client_addr, &clientlen);
					if (*newfd<0){
						perror("Accept");
						exit(1);
					}
					//read the first 10 number into a buffer
					FD_SET(*newfd,&fdset);
					char *buffer=(char*)malloc(11*sizeof(char));
					int n= read(*newfd, buffer, 10);
					if (n<0){
						perror("Error with first read");
						exit(1);
					}
					buffer[10]='\0';
					//get the length and create a proper char size
					int len=atoi(buffer)+1;
					free(buffer);
					buffer= (char*)malloc(len*sizeof(char));
					bzero((char*)buffer,len);
					n= read(*newfd, buffer, len-1);	
					if (n<0){
						perror("Error with second read");
						exit(1);
					}
					buffer[len-1]='\0';
					//print the new user
					printf ("New User: %s\n", buffer);
					s_node* add= new_node(buffer,NULL, NULL);
					s_node* add2= new_node(newfd,NULL,NULL);
					//add the name and int into a "dictionary"
					append(add2,head);
					append(add,strhead);	
					//debug_string(*strhead);
					char *buf=(char*)malloc((my_strlen(buffer)+9)*sizeof(char));
					sprintf(buf, "Welcome %s", buffer);
					char *string =appendpre(buf);
					write(*newfd, string, my_strlen(string));
					free(string);
					free(buf);
					//max++;
				}
				else{	
					//message from existing user
					s_node* temp=*head;
					s_node* strtemp= *strhead;
					char* buff=(char*)malloc(11*sizeof(char));
					int s= read(i, buff, 10);
					if (s<0){
						perror("First Reading");
						exit(1);
					}
					buff[10]='\0';
					int len=atoi(buff)+1;
					free(buff);
					buff=(char*)malloc(len*sizeof(char));
					bzero((char*)buff,len);
					s= read(i, buff, len-1);		
					if (s<0){
						perror("Second Reading");
						exit(1);
					}
					buff[len-1]='\0';
					//exit	
					//int l=my_strlen(buff);
					if (my_strcmp(buff, "/exit")==0){
						int ctr=0;
						char* exit="exit";	
						write(i, exit,10);
						while (temp!=NULL && *(int*)temp->elem!=i){
							temp=temp->next;
							strtemp=strtemp->next;	
							ctr++;
						}
						printf ("User %s left\n", (char*)strtemp->elem);
						void* point=remove_node_at(head,ctr);
						void* string=remove_node_at(strhead,ctr);
						free(string);
						free(point);
						shutdown(i,2);	
						FD_CLR(i, &fdset);
						free(buff);	
					}
					//change name
					else if(my_strncmp(buff, "/nick ",6)==0){
						char *total;
						char* ret= (buff+6);
						int ctr=0;
						while (temp!=NULL && *(int*)temp->elem!=i){
							temp=temp->next;
							strtemp=strtemp->next;
							ctr++;	
						}
						if (whitespace(ret)==0){
							//remove nodes from linked list 
							printf("User %s changed name to %s\n",(char*)strtemp->elem,ret); 
							void* point=remove_node_at(head,ctr);
							void* string=remove_node_at(strhead,ctr);
							free(string);
							char* charstr=my_strdup(ret);
							s_node* a= new_node(point, NULL, NULL);
							s_node* b= new_node(charstr, NULL, NULL);
							//re add the nodes with new name
							append(a,head);	
							append(b,strhead);
							//send message to user of change name		
							char mess[30]= "Changed name to ";
							char* message=my_strconcat(mess,charstr);
							total= appendpre(message);
							write(i, total ,my_strlen(total));	
							free(message);
						}
						else{
							//tell user to not change name to empty
							char mess[30]= "Can't change name to empty ";
							total= appendpre(mess);
							write(i, total ,my_strlen(total));

						}
						free(buff);
						free(total);
					}
					//else if its not a special command print error to user
					else if(my_strncmp(buff,"/me ",4)!=0 && my_strncmp(buff,"/",1)==0){
						char message[30]="Not a special command";	
						char* ret=appendpre(message);
						write(i,ret, my_strlen(ret));
						free(ret);
						free(buff);
					}
					//print to everyone
					else{	
						//check to see if its "me" condition"
						if(my_strncmp(buff,"/me ", 4)==0){
							flag=1;
							char* ret=(buff+4);
							my_strcpy(buff,ret);
						}
						//get the name
						while (temp->next!=NULL && *(int*)temp->elem!=i){
							temp=temp->next;
							strtemp=strtemp->next;	
						}
						char *name = (char*)strtemp->elem;
						temp=*head;
						char message[len+my_strlen(name)];
						if (flag==0){
							sprintf(message, "%s: %s", name ,buff);
						}
						else{
							sprintf(message, "%s %s", name ,buff);
							flag=0;
						}
						puts(message);
						char* ret=appendpre(message);	
						//send to all users
						while (temp!=NULL){
							if (*(int*)temp->elem!=socketfd){
								write(*(int*)(temp->elem),ret, my_strlen(ret));
							}
							temp=temp->next;
						}
						free(buff);
						free(ret);
					}
				}
			}
		}
		
	}

}

