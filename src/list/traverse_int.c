#include "list.h"

void traverse_int(struct s_node* head){
	if (head==NULL){
		my_str("");
	}
	s_node* temp= head;
	while (temp!=NULL){
		if (temp->elem!=NULL){
			my_int(*(int*)temp->elem);
			my_char(' ');
		}
		else{
			my_str("NULL ");
		}
	temp=temp->next;
	}
}
