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

int draw_box(int x1, int y1, int x2, int y2) 
{
	int i, j ;
	for (i = 1; i < x2+1; i++) {
		goto_XY(x1+i, y1);
		if (i == 1) {
			print_char("l");
			for (j = 2; j < y2; j++) {
				print_char("q");
			}
			print_char("k");
		}
		if (i > 1 && i < x2) {
			print_char("x");
			for (j = 2; j < y2; j++) {
				print_char(" ");
			}
			print_char("x");
		}
		if (i == x2) {
			print_char("m");
			for (j = 2; j < y2; j++) {
				print_char("q");
			}
			print_char("j");
		}
	}
}

void draw_screen()
{
	set_fg_color(CYAN);
	draw_box(0, 0, 21, 34);
	draw_box(0, 35, 24, 46);
	draw_box(21, 0, 24, 34);

	set_fg_color(BLUE);
	goto_XY(5, 3);
	write(1, "1 - Enter world's height", 24);
	goto_XY(7, 3);
	write(1, "2 - Enter world's width", 23);
	goto_XY(9, 3);
	write(1, "3 - Enter the ammount of cycles", 31);
	goto_XY(11, 3);
	write(1, "4 - Start game with random world", 14);
	goto_XY(13, 3);
	write(1, "5 - Start game with Gosper gun", 8);
	goto_XY(15, 3);
	write(1, "6 - Exit", 8);
}

void clear_world()
{
	int i;
	for (i = 2; i < 24; i++) {
		write_str("", i, 38, 40, 0);
	}
}

int draw_world(int **world, int WIDTH, int HEIGHT)
{
	unsigned int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
			if (world[i][j] == 0) {
				set_fg_color(RED);
			}
    		else {
    			set_fg_color(GREEN);
    		}
    		goto_XY(i+2, j+38);
    		write(1, "@", 1);
		}
	}
}





