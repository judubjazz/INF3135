/*
 * Copyright 2017 Alexandre Terrasa <alexandre@moz-code.org>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * This program generates random pandemic grids for testing purpose.
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// Constants
static const char DEAD = '.';
static const char HEALTHY = 'H';
static const char INFECTED = 'X';
static const char QUARANT = 'Q';

// Program status
enum STATUS {
    GENERATOR_OK               = 0,
    GENERATOR_ARGC_ERROR       = 1,
    GENERATOR_ARGV_NONPOSITIVE = 2,
};

/*
 * Prints the program usage on stdout.
 */
void print_usage()
{
	fprintf(stdout, "Usage: generator <lines> <columns>\n");
}

/*
 * Generates and returns a random cell.
 *
 * Probabilities:
 * * 20% of HEALTHY
 * * 20% of INFECTED
 * * 60% of DEAD
 *
 * @return  the cell char
 */
char gen_cell()
{
	int r = rand() % 100;
	if (r > 80) {
		return HEALTHY;
	} else if (r > 60) {
		return INFECTED;
	}else if (r > 30) {
		return QUARANT;
	}
	return DEAD;
}

/*
 * Prints a random grid of `height` rows and `width` columns on stdout.
 *
 * @param height  number of lines in the grid
 * @param width   number of columns in the grid
 */
void gen_grid(int height, int width)
{
	int i;
	int j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			char cell = gen_cell();
			printf("%c", cell);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[])
{
	int height, width;
	time_t t;

	if (argc != 3) {
		fprintf(stderr, "Error: two arguments respectively the lines and columns of the grid.\n");
		print_usage();
		exit(GENERATOR_ARGC_ERROR);
	}

	height = atoi(argv[1]);
	width = atoi(argv[2]);
	if (height < 0 || width < 0) {
		fprintf(stderr, "Error: the number of lines and columns must be positive.\n");
		print_usage();
		exit(GENERATOR_ARGV_NONPOSITIVE);
	}

	srand((unsigned) time(&t));
	gen_grid(height, width);

	return GENERATOR_OK;
}
