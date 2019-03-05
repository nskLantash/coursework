#ifndef READKEY_H
#define READKEY_H

struct termios savetty, tty;
enum keys {ONE = 1, TWO, THREE, FOUR, FIVE, SIX };

int read_key(enum  keys *);
int my_term_save() ;
int my_term_restore() ;
int my_term_regime(int regime, int vtime, int vmin, int echo, int sigint) ;

#endif // READKEY_H
