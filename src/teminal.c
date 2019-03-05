#include "terminal.h"

int clrscr(void) 
{
	if (!isatty(1)) {
		fprintf(stderr, "Поток вывода не связан с терминалом\n") ;
		return -1 ;
	} 
	write(1, "\E[H\E[J", 7) ;
	return 0 ;
}
