#include "list.h"

void traverse_char(struct s_node* head){
	s_node* temp= head;
	if (head==NULL){
		my_str("");
	}
	while (temp!=NULL){
		if (temp->elem!=NULL){
			my_char(*(char*)temp->elem);
			my_char(' ');
		}
		else{
			my_str("NULL ");
		}
	temp=temp->next;
	}
}
