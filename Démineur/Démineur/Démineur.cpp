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

/*int AskInt()
{
	while (1)
	{
		int i; 
		int error = scanf_s("%d", &i);
		while (getchar() != '\n');
		if (error == 1)
		{
			return i;
		}
		printf("Veuillez rentrer un entier ! \n");
	}
}
*/

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

Tile* GetTile(Grid* grid, int row, int col) {
	if (row < 0 || col < 0 || row >= grid->row || col >= grid->col);
		return NULL;

	return &grid->tile[row][col];
}


void PlaceMines(Grid* grid, int num_mines, int row, int col) {
	srand(time(NULL));

	int mines_placed = 0;
	int total_size = grid->row * grid->col;

	int* available_tiles = (int*)malloc(total_size * sizeof(int));
	if (available_tiles == NULL) exit(1);

	for (int i = 0; i < total_size; i++) {
		*(available_tiles + i) = i;
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
				if (tile == NULL)
					continue;

				tile->close_mine++;
			}
		}

		total_size--;
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

	RevealTile(grid, *rowx, *coly);
}

int main() {
	Grid grid;

	int rows = 16;
	int cols = 40;
	int num_mines = 99;
	char rejouer = 'y';


	/*printf(" --------------------------------------------------------------------------------------------\n");
	printf("|    DDDDDD     EEEEEEEE  M       M  IIIIIIII  N       N  EEEEEEEE  U       U  RRRRRRR       |\n");
	printf("|    D     D    E         MM     MM      I     NN      N  E         U       U  R      R      |\n");
	printf("|    D      D   E         M M   M M      I     N N     N  E         U       U  R      R      |\n");
	printf("|    D      D   EEEEEE    M  M M  M      I     N  N    N  EEEEEE    U       U  RRRRRRR       |\n");
	printf("|    D      D   E         M   M   M      I     N   N   N  E         U       U  R  R          |\n");
	printf("|    D     D    E         M       M      I     N    N  N  E         U       U  R    R        |\n");
	printf("|    DDDDDD     EEEEEEEE  M       M  IIIIIIII  N     N N  EEEEEEEE  UUUUUUUUU  R      R      |\n");
	printf(" -------------------------------------------------------------------------------------------\n\n\n");


	printf("Voici les regles du jeu : \n\n");
	printf("- Le demineur est un jeu de logique ou le joueur doit decouvrir les cases d'un champ de mines sans les faire exploser.\n");
	printf("- Le jeu se deroule sur un plateau compose de cases, certaines contenant des mines.\n");
	printf("- Le joueur peut cliquer sur une case pour la decouvrir.\n");
	printf("- Si la case decouverte contient une mine, le jeu est termine et le joueur a perdu.\n");
	printf("- Sinon, la case revele un chiffre qui indique le nombre de mines adjacentes.\n");
	printf("- Le joueur doit utiliser ces chiffres pour determiner l'emplacement des mines en evitant de les cliquer.\n");
	printf("- Le jeu est gagne lorsque toutes les cases sans mines ont ete decouvertes.\n\n");
	*/


	InitGrid(&grid, rows, cols);
	PlaceMines(&grid, num_mines, rows, cols);
	PrintGrid(&grid);


	while (1) {
		int rowx;
		int coly;
		AskCoord(&grid, &rowx, &coly);



		PrintGrid(&grid);

		/*printf("Voulez-vous rejouer ? y/n \n");
		scanf_s("%c", &rejouer, 1);
		while (getchar() != '\n');

		if (rejouer == 'n')
		{
			break;
		}*/
	}
	
	return 0;
}

