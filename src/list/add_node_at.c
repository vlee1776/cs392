#include "list.h"

void add_node_at(struct s_node* node, struct s_node** head, int n)
{
	if (node ==NULL || node->elem==NULL || head==NULL){
		return;
	}
	if (n<=0 || *head==NULL){
		add_node(node,head);
		return;
	}
	int i=0;
	s_node* temp= *(head);
	s_node* previous= *(head);
	while (i<n && temp->next!=NULL){
		previous=temp;
		temp=temp->next;
		i++;
	}
	if (i==n){
		node->prev=previous;
		node->next=temp;
		temp->prev=node;
		previous->next=node;
	}
	else{
		temp->next=node;
		node->next=NULL;
		node->prev=temp;
	}
}
