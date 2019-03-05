#ifndef _DESIGN_H
#define _DESIGN_H
#include "terminal.h"

int print_char(char *str);
int draw_box(int x1, int y1, int x2, int y2);
void clear_world();
int draw_world(int **world, int WIDTH, int HEIGHT);
void draw_screen();

#endif // _DESIGN_H
