#include "game.h"

/*
 * Инициализация первого поколения игры псевдослучайными значениями
 */
void init_world(int **world, int WIDTH, int HEIGHT)
{
    unsigned int i, j;
    srand (time(NULL));

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            unsigned int num = rand() % 1000 + 1;
            if (num % 2 == 0) {
                world[i][j] = 1;
            } else {
                world[i][j] = 0;
            }
        }
    }
}

/*
 * Количество живых клеток на игровом поле
*/
unsigned int get_live_count(int **world, int WIDTH, int HEIGHT)
{
    unsigned int count = 0;
    unsigned i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (world[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}

/*
 * Получение координат соседей точки (окрестность мура 1 порядка)
*/
void read_point_neighbors(signed int nb[][2], unsigned int x, unsigned int y)
{
    unsigned int i, j;
    unsigned int k = 0;

    for (i = x - 1; i <= x + 1; i++) {
        for (j = y - 1; j <= y + 1; j++) {
            if (i == x && j == y) {
                continue;
            }
            nb[k][0] = i;
            nb[k][1] = j;
            k++;
        }
    }
}

/*
 * Количество живых соседей у клетки с координатами x, y
 */
unsigned int count_live_neighbors(int **world, unsigned int x, 
									unsigned int y, int WIDTH, int HEIGHT)
{
    unsigned int count = 0;
    unsigned int i;
    signed int nb[8][2];
    signed int _x, _y;

    read_point_neighbors(nb, x, y);

    for (i = 0; i < 8; i++) {
        _x = nb[i][0];
        _y = nb[i][1];

        if (_x < 0 || _y < 0) {
            continue;
        }
        if (_x >= HEIGHT || _y >= WIDTH) {
            continue;
        }

        if (world[_x][_y] == 1) {
            count++;
        }
    }

    return count;
}

/*
 * Сгенерировать следующее поколение игрового мира
 */
void next_generation(int **world, int **prev_world, int WIDTH, int HEIGHT)
{
    unsigned int i, j;
    unsigned int live_nb;
    int p;

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            p = prev_world[i][j];
            live_nb = count_live_neighbors(prev_world, i, j, WIDTH, HEIGHT);

            if (p == 0) {
                if (live_nb == 3) {
                    world[i][j] = 1;
                }
            } else {
                if (live_nb < 2 || live_nb > 3) {
                    world[i][j] = 0;
                }
            }
        }
    }
}

/*
 * Копирование игрового мира. Используется для сохранения предыдущего поколения
*/
void copy_world(int **src, int **dest, int WIDTH, int HEIGHT)
{
    unsigned int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

/*
 * Сравнение игровых миров текущего и предыдущего поколения
 */
int cmp_world(int **w1, int **w2, int WIDTH, int HEIGHT)
{
    unsigned int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (w1[i][j] != w2[i][j]) {
                return -1;
            }
        }
    }
    return 0;
}

/*
 * Игровой процесс
 */
void start_game(int WIDTH, int HEIGHT, int cycles, int mode)
{
	int i, slp = 1000;
    int **world, **prev_world;
    
    // Выделение памяти под указатели на строки
    world = (int**)malloc(HEIGHT * sizeof(int*));
    prev_world = (int**)malloc(HEIGHT * sizeof(int*));
    for (i = 0; i < HEIGHT; i++) {  // цикл по строкам 
    	// Выделение памяти под хранение строк
    	world[i] = (int*)malloc(WIDTH * sizeof(int));
    	prev_world[i] = (int*)malloc(WIDTH * sizeof(int));
	}

    if (mode == 1) {
    	init_world(world, WIDTH, HEIGHT);
    } 
    if (mode == 2) {
    	WIDTH = 40, HEIGHT = 22, cycles = 300, slp = 250;
    	glider(world);
    }

    unsigned int live_points = -1;
    int is_optimal = 0;
    int count = 0;

    do {
        draw_world(world, WIDTH, HEIGHT);   // вывод из design.h
        //printf(ESC "[%d;%dH%s", 15, 15, "@");	// временно
        copy_world(world, prev_world, WIDTH, HEIGHT);
        next_generation(world, prev_world, WIDTH, HEIGHT);

        is_optimal = cmp_world(world, prev_world, WIDTH, HEIGHT) == 0;
        live_points = get_live_count(world, WIDTH, HEIGHT);

        if (is_optimal) {
            printf("Optimal configuration detected\n");
        }

        if (live_points == 0) {
            printf("All points died\n");
        }
        fflush (stdout);
        msleep(slp);
        count ++;
    } while (live_points != 0 && !is_optimal && count < cycles);
    
    for (i = 0; i < HEIGHT; i++) {  // цикл по строкам
    	free(world[i]);   // освобождение памяти под строку
    	free(prev_world[i]);
    }
    free(world);
  	free(prev_world);
}
void glider(int **world)
{
	world[5][1] = 1; world[6][1] = 1; world[5][2] = 1; world[6][2] = 1;
	world[5][11] = 1; world[6][11] = 1; world[7][11] = 1;
	world[4][12] = 1; world[8][12] = 1;
	world[3][13] = 1; world[9][13] = 1;
	world[3][14] = 1; world[9][14] = 1;
	world[6][15] = 1;
	world[4][16] = 1; world[8][16] = 1;
	world[5][17] = 1; world[6][17] = 1; world[7][17] = 1;
	world[6][18] = 1;
	world[3][21] = 1; world[4][21] = 1; world[5][21] = 1;
	world[3][22] = 1; world[4][22] = 1; world[5][22] = 1;
	world[2][23] = 1; world[6][23] = 1;
	world[1][25] = 1; world[2][25] = 1; world[6][25] = 1; world[7][25] = 1;
	world[3][35] = 1; world[3][36] = 1; world[4][35] = 1; world[4][36] = 1;
}
