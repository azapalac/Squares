#pragma once
#include "Tile.h"
#define HAND_SIZE 7
#define HAND_OFFSET 140
#define STARTING_DIFFICULTY 3
#define MAX_DIFFICULTY 6
#define ORIG_X 200
#define ORIG_Y 800
class TileHand
{
public:
	
	Tile* hand[HAND_SIZE];
	void draw(int index);
	int difficulty = STARTING_DIFFICULTY;
	int tilesInHand = HAND_SIZE;
	void setUpHand();
	void removeSelected(Tile* t);
	void addTile(Tile* t);
	TileHand();
	~TileHand();

private:
	Vector2f currentTilePosition;
	Vector2f origPosition;
};

