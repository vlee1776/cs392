#include "list.h" 

void print_string(struct s_node *node){
	if (node==NULL){
		return;
	}
	if (node->elem==NULL){
		my_str("NULL");
	}
	else{
		my_str((char*)node->elem);
	}
	
}
