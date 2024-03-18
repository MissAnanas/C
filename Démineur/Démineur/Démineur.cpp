#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>

typedef enum TileType {
	HIDE,
	BOMB,
	EMPTY
} TileType;

typedef struct Tile {
	TileType type;
	int Number;
	int CloseBomb;
} Tile;

typedef struct Grid {
	Tile cell;
	int x;
	int y;
} Grid;

void InitGrid() {
	
}




int main() {
	Grid grid;

	grid.x = 0;
	grid.y = 0;

	return 0;
}