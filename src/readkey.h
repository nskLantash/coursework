#ifndef READKEY_H
#define READKEY_H

struct termios savetty, tty;

int my_term_save() ;
int my_term_restore() ;
int my_term_regime(int regime, int vtime, int vmin, int echo, int sigint) ;

#endif // READKEY_H
