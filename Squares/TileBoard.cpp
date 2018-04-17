#include "stdafx.h"
#include "TileBoard.h"


TileBoard::TileBoard()
{
	Vector2f origin(0, 0);
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			Vector2f pos(i*BOARD_OFFSET, j*BOARD_OFFSET);
			pointGrid[i][j] = pos + origin;
		}
	}

	//Make a new tile in the center to start the game
	//Need to add this to draw list
	grid[GRID_SIZE / 10][GRID_SIZE / 10] = new Tile(STARTING_DIFFICULTY);
	startingTile = grid[GRID_SIZE / 10][GRID_SIZE / 10];
	(*startingTile).moveTo(pointGrid[GRID_SIZE / 10][GRID_SIZE / 10]);
	startingTile->canBeMoved = false;
	//startingTile->name = "Starting Tile";
}


TileBoard::~TileBoard()
{
}

bool TileBoard::snapToGrid(Tile* t) {
	float min = INFINITY;
	int iIndex, jIndex;

	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			if (magnitude((*t).getPosition() - pointGrid[i][j]) < min) {
				min = magnitude((*t).getPosition() - pointGrid[i][j]);
				iIndex = i;
				jIndex = j;
			}
		}
	}
	//Assume valid placement before checking
	grid[iIndex][jIndex] = t;
	//Check placement of tile - If valid, move it to the grid
	//If not valid, move back to hand
	if (checkPlacement(iIndex, jIndex)) {
		(*t).moveTo(pointGrid[iIndex][jIndex]);
		t->canBeMoved = false;
		return true;
	}
	else {
		grid[iIndex][jIndex] = NULL;
		(*t).moveTo((*t).origPosition);
		return false;
	}
	

}

bool TileBoard::checkPlacement(int i, int j) {
	//bool isValid = false;
	Tile* tile = grid[i][j];
	Tile* upNeighbor = NULL;
	Tile* downNeighbor = NULL;
	Tile* leftNeighbor = NULL;
	Tile* rightNeighbor = NULL;

	if (i < GRID_SIZE - 1) {
		rightNeighbor = grid[i + 1][j];
	}
	if (i > 0) {
		leftNeighbor = grid[i - 1][j];
	}
	if (j < GRID_SIZE - 1) {
		downNeighbor = grid[i][j + 1];
	}
	if (j > 0) {
		upNeighbor = grid[i][j - 1];
	}

	//Check if all neighbors are null
	if (upNeighbor == NULL && downNeighbor == NULL &&
		leftNeighbor == NULL && rightNeighbor == NULL) {
		return false;
	}

	//Check individual neighbors
	if (upNeighbor != NULL) {
		if (!compareSquares(tile->upRight, tile->upLeft, upNeighbor->bottomRight, upNeighbor->bottomLeft)) {
			return false;
		}
	}

	if (downNeighbor != NULL) {
		if(!compareSquares(tile->bottomRight, tile->bottomLeft, downNeighbor->upRight, downNeighbor->upLeft)){
			return false;
		}
	}

	if (leftNeighbor != NULL) {
		if (!compareSquares(tile->upLeft, tile->bottomLeft, leftNeighbor->upRight, leftNeighbor->bottomRight)) {
			return false;
		}
	}

	if (rightNeighbor != NULL) {
		if (!compareSquares(tile->upRight, tile->bottomRight, rightNeighbor->upLeft, rightNeighbor->bottomLeft)) {
			return false;
		}
	}
	//Return true if all placement tests are passed
	return true;
}


bool TileBoard::compareSquares(Square* a, Square* b, Square* c, Square* d) {
	//Handle wildcards
	//handle color matching
	if ((a->color == c->color || a->color == Color::White || c->color == Color::White) &&
		(b->color == d->color || b->color == Color::White || d->color == Color::White)) {
		
		if (a->color == Color::White) {
			a->color = c->color;
		}

		if (c->color == Color::White) {
			c->color = a->color;
		}
		

		if (b->color == Color::White) {
			b->color = d->color;
		}

		if (d->color == Color::White) {
			d->color = b->color;
		}

		return true;
	}
	else {
		return false;
	}
}