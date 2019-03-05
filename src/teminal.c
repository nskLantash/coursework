#include "terminal.h"

int clrscr(void) 
{
	if (!isatty(1)) {
		fprintf(stderr, "Поток вывода не связан с терминалом\n");
		return -1 ;
	} 
	write(1, "\E[H\E[J", 7);
	return 0;
}

int goto_XY(int x, int y)
{
	if (!isatty(1)) {
		fprintf(stderr, "Поток вывода не связан с терминалом\n");
		return -1;
	} 
	char str[15] = "";
	int len = sprintf(str, "\E[%d;%dH", x, y);
	write(1, str, len);
	return 0;
}

int set_fg_color(enum colors color) 
{
	if (!isatty(1)) {
		fprintf(stderr, "Поток вывода не связан с терминалом\n");
		return -1;
	} 
	char str[10] = "";
	int len = sprintf(str, "\E[3%dm", color);
	write(1, str, len);
	return 0;
}

int set_bg_color(enum colors color) 
{
	if (!isatty(1)) {
		fprintf(stderr, "Поток вывода не связан с терминалом\n");
		return -1;
	} 
	char str[10] = "";
	int len = sprintf(str, "\E[4%dm", color);
	write(1, str, len);
	return 0;
}

void write_str(char *str, int x, int y, int len, int fl) 
{
	int i ;
	goto_XY(x, y);
	write(1, "\E[0m", 5);
	for (i = 0; i < len; i++) {
		print_char(" ");
	}
	if (fl) {
		goto_XY(x, y);
		write(1, str, strlen(str));
	}
}



