#include "my.h"

void my_char(char c)
	{
		/*Write the contents of c to standard out, which is file descriptor 1*/
		write(1, &c, 1);
	}
