#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h> 
#include "readkey.h"

int my_term_save()
{
	if (!isatty(0)) { 
		fprintf(stderr, "stdin not terminal\n") ; 
		return -1 ;
	}
	tcgetattr(0, &tty);              // получили состояние терминала 
	savetty = tty ; 
	return 0 ;
}
int my_term_restore() 
{
	tcsetattr(0, TCSAFLUSH, &savetty) ; // восстановили состояние терминала 
}
int my_term_regime(int regime, int vtime, int vmin, int echo, int sigint) 
{
	if (regime == 1) {
		tty.c_lflag &= ~(ICANON | echo | sigint) ; 
		tty.c_cc[ VMIN ] = vmin; 
		tty.c_cc[ VTIME ] = vtime; 
		tcsetattr(0, TCSAFLUSH, &tty) ; // изменили состояние терминала 
	} else {
		my_term_restore() ;
	}
}

