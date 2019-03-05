#include <stdio.h>
#include <string.h>
#include "design.h"

int print_char(char *str)
{
	if (!isatty(1)) {
		fprintf(stderr, "Поток вывода не связан с терминалом\n");
		return -1 ;
	} 
	write(1, "\E(0", 3);
	write(1, str, strlen(str));
	write(1, "\E(B", 3);
	return 0;
}
