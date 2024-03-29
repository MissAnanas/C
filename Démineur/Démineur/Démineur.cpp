#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define CYAN 11
#define DARKBLUE 9
#define YELLOW 14
#define PINK 13
#define RED 12
#define WHITE 15
#define GREEN 10

int COLORS[] = { CYAN, DARKBLUE, DARKBLUE, YELLOW, YELLOW, PINK, PINK, RED , GREEN};

typedef struct {
	int is_mine;
	int is_reveal;
	int close_mine;
	int is_flag;
} Tile;


typedef struct {
	int row;
	int col;
	Tile** tile; // Tableau 2D de cases
	int remainingTile;
} Grid;


void InitTile(Tile* tile) {
	tile->is_mine = 0;
	tile->is_reveal = 0;
	tile->close_mine = 0;
	tile->is_flag = 0;
}


int AskIntBetween(const char text[], int Min, int Max) {
	int num;

	while (1) {


		printf("%s\n", text);
		int ret = scanf_s("%d", &num);
		while (getchar() != '\n');


		if (num < Min || num > Max) {
			ret = 0;
		}

		if (ret == 1) {
			break;
		}
		printf("Merci de rentrer uniquement des nombres entre %d et %d\n", Min, Max);
	}
	return num;
}


void InitGrid(Grid* grid, int row, int col) {
	grid->row = row;
	grid->col = col;

	grid->tile = (Tile**)malloc(row * sizeof(Tile*));
	if (grid->tile == NULL) exit(1);

	for (int i = 0; i < row; i++) {
		grid->tile[i] = (Tile*)malloc(col * sizeof(Tile));
		if (grid->tile[i] == NULL) exit(1);
	}

	for (int x = 0; x < row; x++) {
		for (int y = 0; y < col; y++) {
			InitTile(&(grid->tile[x][y]));
		}
	}
}

Tile* GetTile(Grid* grid, int row, int col) {
	if (row < 0 || col < 0 || row >= grid->row || col >= grid->col) return NULL;

	return &grid->tile[row][col];
}


void PlaceMines(Grid* grid, int num_mines, int row, int col, int xUser, int yUser) {
	srand(time(NULL));

	grid->remainingTile = grid->row * grid->col - num_mines;

	int mines_placed = 0;
	int total_size = grid->row * grid->col;

	int* available_tiles = (int*)malloc(total_size * sizeof(int));
	if (available_tiles == NULL) exit(1);

	for (int i = 0; i < total_size; i++) {
		*(available_tiles + i) = i;
	}


	for (int i = xUser - 1; i < xUser + 2; i++) {
		for (int j = yUser - 1; j < yUser + 2; j++) {
			available_tiles[i * grid->col + j] = available_tiles[total_size - 1];
			total_size--;
		}
	}


	for (int m = 1; m < num_mines + 1; m++) {
		int selected_index = rand() % total_size;
		int selected_val = available_tiles[selected_index];

		available_tiles[selected_index] = available_tiles[total_size - 1];

		int x = selected_val / grid->col;
		int y = selected_val % grid->col;

		grid->tile[x][y].is_mine = 1;

		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				Tile* tile = GetTile(grid, x + i, y + j);

				if (tile != NULL) {
					tile->close_mine++;
				}
					
			}
		}

		total_size--;
	}
}


void PrintGrid(Grid* grid, int showBomb) {
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int tile_number = 1;

	for (int x = 0; x < grid->row; x++) {
		printf("\n");
		for (int y = 0; y < grid->col; y++) {

			if (grid->tile[x][y].is_reveal == 1) {
				if (grid->tile[x][y].is_mine == 1) {
					SetConsoleTextAttribute(hConsole, RED);
					printf("  *   |");
				}
				else {
					if (grid->tile[x][y].close_mine == 0) {
						printf("      |");
					}
					else {
						SetConsoleTextAttribute(hConsole, COLORS[grid->tile[x][y].close_mine]);
						printf(" %4d |", grid->tile[x][y].close_mine);
					}
				}
			}
			else {
				if (grid->tile[x][y].is_mine == 1 && showBomb == 1) {
					SetConsoleTextAttribute(hConsole, RED);
					printf("  *   |");
				}
				else if (grid->tile[x][y].is_flag == 1) {
					SetConsoleTextAttribute(hConsole, RED);
					printf(" F%3d |", tile_number);
				}
				else {
					SetConsoleTextAttribute(hConsole, WHITE);
					printf(" %4d |", tile_number);
				}
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
	grid->remainingTile--;

	if (grid->tile[rowx][coly].close_mine > 0) {
		return;
	}

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			RevealTile(grid, rowx + i, coly + j);
		}
	}
}


void AskCoord(Grid* grid, int* rowx, int* coly) {
	int select_tile;

	while (1) {

		printf("\nEntrez un numero de tuile : ");
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
}

int main() {
	Grid grid;

	int rows = 10;
	int cols = 30;
	int num_mines = 99;

	InitGrid(&grid, rows, cols);
	PrintGrid(&grid, 0);

	int firstInput = 1;

	while (1) {
		int rowx;
		int coly;
		int choice;

		AskCoord(&grid, &rowx, &coly);
		
		choice = AskIntBetween("Que voulez-vous faire avec cette case ? (0: Reveler, 1:drapeau ?, 2:Annuler la selection)", 0, 2);

		if (choice == 0) {
			if (firstInput == 1) {
				PlaceMines(&grid, num_mines, rows, cols, rowx, coly);
				firstInput = 0;
			}

			RevealTile(&grid, rowx, coly);

			if (grid.tile[rowx][coly].is_mine == 1) {
				system("cls");
				printf("Vous avez perdu !!!\n");
				PrintGrid(&grid, 1);
				break;
			}

			if (grid.remainingTile == 0) {
				system("cls");
				printf("Vous avez gagne !!\n");
				PrintGrid(&grid, 1);
				break;
			}

		}
		else if (choice == 1) {
			if (grid.tile[rowx][coly].is_flag == 0) {
				grid.tile[rowx][coly].is_flag = 1;
			}
			else {
				grid.tile[rowx][coly].is_flag = 0;
			}
		}

		PrintGrid(&grid, 0);

	}

	return 0;
}

