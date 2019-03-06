#ifndef READKEY_H
#define READKEY_H

struct termios savetty, tty;
enum keys {ONE = 1, TWO, THREE, FOUR, FIVE, SIX };
static int peek_character = -1;

int read_key(enum  keys *);
int my_term_save() ;
int my_term_restore() ;
int my_term_regime(int regime, int vtime, int vmin, int echo, int sigint) ;
int kbhit();

#endif // READKEY_H
