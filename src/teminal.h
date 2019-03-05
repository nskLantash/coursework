#ifndef _TERM_H
#define _TERM_H

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "design.h"

enum colors {BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE};

int clrscr(void);
int goto_XY(int, int);
int set_fg_color(enum colors color);
int set_bg_color(enum colors color);

#endif 
