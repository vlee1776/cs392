#include "list.h"

void* remove_node(struct s_node** node){
	if (node==NULL || *(node)==NULL){
		return NULL;
	}
	s_node* temp= *node;
	void* ret=temp->elem;
	if (temp->prev==NULL && temp->next==NULL){	
		free(temp);
		*(node)=NULL;
	}
	//last node
	else if (temp->next==NULL){
		s_node* previous=temp->prev;
		previous->next=NULL;
		temp->prev=NULL;
		free(temp);
		*node=NULL;
	}
	//head
	else if (temp->prev==NULL){
		s_node* nxt= temp->next;
		nxt->prev=NULL;
		temp->next=NULL;
		*(node)=nxt;
		free(temp);
	}
	//middle
	else{
		s_node* nxt= temp->next;
		s_node* previous= temp->prev;
		nxt->prev=previous;
		previous->next=nxt;
		temp->next=NULL;
		temp->prev=NULL;
		free(*node);
		*node=NULL;
	}
	return ret;
}
