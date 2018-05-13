objects= my_alpha.o my_digits.o my_str.o my_num_base.o my_strlen.o my_char.o\
my_int.o my_revstr.o my_strindex.o my_strrindex.o my_strfind.o my_strrfind.o\
my_strcmp.o my_strncmp.o my_strcpy.o my_strncpy.o my_strcat.o my_strdup.o \
my_strconcat.o my_strnconcat.o my_atoi.o my_vect2str.o my_str2vect.o my_printf.o

CC=gcc -std=c99
CFLAGS=-Wall -Werror --pedantic
INCLUDES=-I../../include

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(objects)	
	ar -rc libmy.a $(objects) && ranlib libmy.a
	mv libmy.a ../../lib

clean:
	rm *.o

fclean: clean
	cd ../../lib && rm libmy.a

re: fclean all
		
run:
	cd ../../test && $(CC) -o test test.c -I../include -L../lib -lmy
	cd ../../test && ./test
