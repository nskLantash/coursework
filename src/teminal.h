#ifndef _TERM_H
#define _TERM_H

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "design.h"

int clrscr(void);
int goto_XY(int, int);

#endif 
