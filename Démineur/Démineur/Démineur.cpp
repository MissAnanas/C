#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
	int is_mine;
	int is_reveal;
	int close_mine;
} Tile;


typedef struct {
	int row;
	int col;
	Tile** tile; // Tableau 2D de cases
} Grid;


void InitTile(Tile* tile) {
	tile->is_mine = 0;
	tile->is_reveal = 0;
	tile->close_mine = 0;
}


void InitGrid(Grid* Grid, int row, int col) {
	Grid->row = row;
	Grid->col = col;

	Grid->tile = (Tile**)malloc(row * sizeof(Tile*));
	if (Grid->tile == NULL) exit(1);

	for (int i = 0; i < row; i++) {
		Grid->tile[i] = (Tile*)malloc(col * sizeof(Tile));
		if (Grid->tile[i] == NULL) exit(1);
	}

	for (int x = 0; x < row; x++) {
		for (int y = 0; y < col; y++) {
			InitTile(&(Grid->tile[x][y]));
		}
	}
}


void PlaceMines(Grid* grid, int num_mines) {
	srand(time(NULL));

	int row;
	int col;
	int mines_placed = 0;

	while (mines_placed < num_mines) {
		row = rand() % grid->row;
		col = rand() % grid->col;

		if (grid->tile[row][col].is_mine == 0) {
			grid->tile[row][col].is_mine = 1;
			mines_placed++;
		}
	} 
}


void PrintGrid(Grid* grid) {
	int tile_number = 1;

	for (int x = 0; x < grid->row; x++) {
		for (int y = 0; y < grid->col; y++) {

			if (grid->tile[x][y].is_reveal == 1) {
				if (grid->tile[x][y].is_mine == 1) {
					printf("  *  |");
				}
				else {
					if (grid->tile[x][y].close_mine == 0) {
						printf("     |");
					}
					else {
						printf(" %3d |", grid->tile[x][y].close_mine);
					}
				}
			}
			else {
				printf(" %3d |", tile_number);
			}
			tile_number++;
		}

		printf("\n");
	}
}


void RevealTile(Grid* grid, int rowx, int coly) {
	if (rowx < 0 || coly < 0 || rowx >= grid->row || coly >= grid->col) return;

	if (grid->tile[rowx][coly].is_reveal == 1) return;

	grid->tile[rowx][coly].is_reveal = 1;

	if (grid->tile[rowx][coly].close_mine > 0) return;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			RevealTile(grid, rowx + i, coly + j);
		}
	}
}


void AskCoord(Grid* grid, int* rowx, int* coly) {
	int select_tile;

	while (1) {
		printf("Entrez un numero de tuile : ");
		if (scanf_s("%d", &select_tile) == 1) {
			if (select_tile >= 1 && select_tile <= grid->row * grid->col) {
				*rowx = (select_tile - 1) / grid->col;
				*coly = (select_tile - 1) % grid->col;
				break;
			}
			else {
				printf("Tuile Invalide !\n");
			}
		}
		else {
			while (getchar() != '\n');
			printf("Saisie Invalide !\n");
		}
	}

	RevealTile(grid, *rowx, *coly);
}


int main() {
	Grid grid;

	int rows = 16;
	int cols = 40;
	int num_mines = 99;

	InitGrid(&grid, rows, cols);
	PlaceMines(&grid, num_mines);
	PrintGrid(&grid);

	while (1) {
		int rowx;
		int coly;
		AskCoord(&grid, &rowx, &coly);

		PrintGrid(&grid);
	}
	
	return 0;
}

