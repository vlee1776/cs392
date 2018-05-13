#include "list.h"

void append(struct s_node* node, struct s_node** head)
{
	if (node==NULL || node->elem==NULL || head==NULL){
		return;
	}
	//if list is empty
	if (*(head)==NULL){
		add_node(node,head);
		return;
	}
	//if node already exist
	s_node* temp=*(head);
	while (temp->next!=NULL){
		temp=temp->next;
	}
	temp->next=node;
	node->prev=temp;
	node->next=NULL;
}
