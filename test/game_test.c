#include <stdlib.h>
#include "ctest.h"
#include "../src/game.h"
#include "../src/terminal.h"
#include "../src/design.h"

void init_matrix(int **world)
{
	world[0][0] = 0; world[0][1] = 1; world[0][2] = 1; world[0][3] = 0; 
	world[1][0] = 0; world[1][1] = 1; world[1][2] = 0; world[1][3] = 1; 
	world[2][0] = 0; world[2][1] = 0; world[2][2] = 0; world[2][3] = 0; 
	world[3][0] = 1; world[3][1] = 0; world[3][2] = 1; world[3][3] = 0; 
}

CTEST(suite1, test1) {
	int **matrix;
	int i;
	matrix = (int**)malloc(4 * sizeof(int*));
    for (i = 0; i < 4; i++) {  // цикл по строкам 
    	// Выделение памяти под хранение строк
    	matrix[i] = (int*)malloc(4 * sizeof(int));
	}
	init_matrix(matrix);

	unsigned int real = get_live_count(matrix, 4, 4);
	unsigned int expected = 6;
	ASSERT_EQUAL(real, expected);
}

CTEST(suite2, test2) {
	int **matrix;
	int i;
	matrix = (int**)malloc(4 * sizeof(int*));
    for (i = 0; i < 4; i++) {  // цикл по строкам 
    	// Выделение памяти под хранение строк
    	matrix[i] = (int*)malloc(4 * sizeof(int));
	}
	init_matrix(matrix);

	unsigned int real = count_live_neighbors(matrix, 1, 1, 4, 4);
	unsigned int expected = 2;
	ASSERT_EQUAL(real, expected);
}

CTEST(suite2, test3) {
	int i;
	int **matrix, **prev_matrix;
	matrix = (int**)malloc(4 * sizeof(int*));
	prev_matrix = (int**)malloc(4 * sizeof(int*));
    for (i = 0; i < 4; i++) {  // цикл по строкам 
    	// Выделение памяти под хранение строк
    	matrix[i] = (int*)malloc(4 * sizeof(int));
    	prev_matrix[i] = (int*)malloc(4 * sizeof(int));
	}
	init_matrix(matrix);
	copy_world(matrix, prev_matrix, 4, 4);

	unsigned int real = cmp_world(matrix, prev_matrix, 4, 4);
	unsigned int expected = 0;
	ASSERT_EQUAL(real, expected);
}

