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

void PlaceMines(Grid* Grid, int num_mines) {
	srand(time(NULL));

	int row;
	int col;
	int mines_placed = 0;

	while (mines_placed < num_mines) {
		row = rand() % Grid->row;
		col = rand() % Grid->col;

		if (Grid->tile[row][col].is_mine == 0) {
			Grid->tile[row][col].is_mine = 1;
			mines_placed++;
		}
	} 
}

void PrintGrid(Grid* Grid) {
	int tile_number = 1;

	for (int x = 0; x < Grid->row; x++) {
		for (int y = 0; y < Grid->col; y++) {

			if (Grid->tile[x][y].is_reveal == 1) {
				if (Grid->tile[x][y].is_mine == 1) {
					printf("* ");
				}
				else {
					printf("%d ", Grid->tile[x][y].close_mine);
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

void AskCoord(Grid* Grid, int* row, int* col) {
	int select_tile;

	while (1) {
		printf("Entrez un numero de tuile : ");
		if (scanf_s("%d", &select_tile) == 1) {
			if (select_tile >= 1 && select_tile <= Grid->row * Grid->col) {
				*row = (select_tile - 1) / Grid->col;
				*col = (select_tile - 1) % Grid->col;
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
}

int main() {
	Grid Grid;

	int rows = 16;
	int cols = 40;
	int num_mines = 99;

	InitGrid(&Grid, rows, cols);
	PlaceMines(&Grid, num_mines);
	PrintGrid(&Grid);


	int row;
	int col;

	AskCoord(&Grid, &row, &col);


	return 0;
}

