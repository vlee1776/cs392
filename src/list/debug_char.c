#include "list.h"

void debug_char(struct s_node* head){
	if (head==NULL){
		my_str("");
	}
	s_node* temp=head;
	while(temp!=NULL){
		my_char('(');
		if (temp->prev==NULL){
			my_str("NULL");
		}
		else{
			my_char(*(char*)temp->prev->elem);
		}
		if (temp->elem==NULL){
			my_str(" <- NULL ->");
		}
		else{
			my_str(" <- ");
			my_char(*(char*)temp->elem);
			my_str(" -> ");
		}
		if (temp->next==NULL){
			my_str("NULL");
		}
		else{
			my_char(*(char*)temp->next->elem);
		}
	my_str("),");
	temp=temp->next;
	}
}
