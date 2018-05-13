#include "list.h"

void add_node(struct s_node* node, struct s_node** head)
{
	if (node==NULL || node->elem==NULL || head==NULL){
		return;
	}
	//if you have no list yet make the node a list
	if (*head==NULL){
		*head=node;
		node->next=NULL;
		node->prev=NULL;
		return;
	}
	//adding to an already created list
	s_node* temp= *(head);
	temp->prev=node;
	*head= node;
	node->prev=NULL;
	node->next= temp;
}
