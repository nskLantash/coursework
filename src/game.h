#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "design.h"
#include "readkey.h"
#include <unistd.h>
#define msleep(x) usleep(x * 1000)

void init_world(int **world, int WIDTH, int HEIGHT);
void glider(int **world, int WIDTH, int HEIGHT);
unsigned int get_live_count(int **world, int WIDTH, int HEIGHT);
void read_point_neighbors(signed int nb[][2], unsigned int x, unsigned int y);
unsigned int count_live_neighbors(int **world, unsigned int x, 
									unsigned int y, int WIDTH, int HEIGHT);
void next_generation(int **world, int **prev_world, int WIDTH, int HEIGHT);
int cmp_world(int **w1, int **w2, int WIDTH, int HEIGHT);
void copy_world(int **src, int **dest, int WIDTH, int HEIGHT);
void start_game(int WIDTH, int HEIGHT, int cycles, int mode);

#endif // GAME_H
