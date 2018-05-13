#include "list.h" 

void print_char(struct s_node *node){
	if (node==NULL){
		return;
	}
	if (node->elem==NULL){
		my_str("NULL");
	}
	else{
		my_char(*(char*)node->elem);	
	}
}
