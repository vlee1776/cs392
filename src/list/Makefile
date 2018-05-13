objects= new_node.o add_node.o add_elem.o append.o add_node_at.o remove_node.o\
remove_last.o remove_node_at.o count_s_nodes.o empty_list.o node_at.o elem_at.o\
elem_at.o traverse_int.o traverse_char.o traverse_string.o debug_int.o\
debug_char.o debug_string.o print_int.o print_char.o print_string.o

CC=gcc -std=c99 -g
CFLAGS=-Wall -Werror --pedantic
INCLUDES=-I../../include

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(objects)	
	ar -rc liblist.a $(objects) && ranlib liblist.a
	mv liblist.a ../../lib

clean:
	rm *.o

fclean: clean
	cd ../../lib && rm liblist.a

re: fclean all
		
run:
	cd ../../test && $(CC) -g -o testlist testlist.c -I../include -L../lib -llist -lmy
	cd ../../test && ./testlist
