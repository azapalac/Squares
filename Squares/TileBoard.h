#pragma once
#include "Tile.h"
#include "TileHand.h"
#include <vector>
#define GRID_SIZE 50
#define BOARD_OFFSET 120
using namespace std;
class TileBoard
{
public:

	Tile* grid[GRID_SIZE][GRID_SIZE];
	Vector2f pointGrid[GRID_SIZE][GRID_SIZE];
	bool checkPlacement(int i, int j);
	bool snapToGrid(Tile* t);
	void returnToHand(Tile* t, TileHand* h);
	Tile* startingTile;
	TileBoard();
	~TileBoard();
	

private: 
	bool compareSquares(Square* a, Square* b, Square* c, Square* d);
};

