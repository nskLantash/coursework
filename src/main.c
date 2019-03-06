#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "game.h"
#include "design.h"
#include "terminal.h"
#include "readkey.h"

int cursor(int fl);
int enter_data(int fl);

int main(int argc, char *argv[])
{
    int WIDTH = 40, HEIGHT = 22, cycles = 5, tmp;
    enum keys key;
    
    clrscr();
    my_term_save();
	cursor(1);		//терминал в неканонический режим и курсор невидим
	
	draw_screen();
	
	while(1) { 
		int flag = read_key(&key);
		if (flag) continue;
		if (key == SIX) {
			break;
		}
		switch (key) {
		case ONE: 
			tmp = enter_data(1);
			if (tmp) {
				HEIGHT = tmp;
			}
			break;
		case TWO:
			tmp = enter_data(2);
			if (tmp) {
				WIDTH = tmp;
			}
			break;
		case THREE:
			tmp = enter_data(3);
			if (tmp) {
				cycles = tmp;
			}
			break;
		case FOUR:
			clear_world();
			start_game(WIDTH, HEIGHT, cycles, 1);
			break;
		case FIVE:
			clear_world();
			WIDTH = 40, HEIGHT = 22;
			int tmp_cycle = cycles;
			start_game(WIDTH, HEIGHT, cycles, 2);
			cycles = tmp_cycle;
			break;
		default: 
			break;
		}
    }

	cursor(0);				//видимый курсор и канонический режим терминала
	write(1, "\E[0m", 5) ;	//цвета по умолчанию
	clrscr();

    return 0;
}

int cursor(int fl)
{
	if (fl == 1) {
		write(1, "\E[?25l", 7);				//невидимый курсор
		my_term_regime(1, 0, 1, ECHO, ISIG);
	}
	else {
		write(1, "\E[?12;25h", 10);			//видимый курсор
		my_term_regime(2, 0, 0, 0, 0);
	}
}

int enter_data(int fl)
{
	int value;
	char buf[10] = "";
	write_str("Enter value: ", 23, 2, 32, 1);
	cursor(0);
	read(0, buf, 10);
	cursor(1);
	value = atoi(buf);
	switch (fl) {
	case 1:
		if (value < 4 || value > 22) {
			write_str("HEIGHT in range 4-22", 23, 2, 32, 1);
			return 0;
		}
	case 2:
		if (value < 4 || value > 40) {
			write_str("WIDTH in range 4-40", 23, 2, 32, 1);
			return 0;
		}
	case 3:
		if (value < 0) {
			write_str("Cycles should be positive", 23, 2, 32, 1);
			return 0;
		}
	}
	return value;
}
