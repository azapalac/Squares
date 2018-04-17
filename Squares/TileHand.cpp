#include "stdafx.h"
#include "TileHand.h"


TileHand::TileHand()

{

	origPosition.x = ORIG_X;
	origPosition.y = ORIG_Y;

	setUpHand();

}

void TileHand::draw(int index) {
	Tile* t = new Tile(difficulty);
	hand[index] = t;
	t->index = index;
	(*t).moveTo(currentTilePosition);
	currentTilePosition.x += HAND_OFFSET;
	(*t).origPosition = (*t).getPosition();
	t->canBeMoved = true;
}

void TileHand::setUpHand() {
	currentTilePosition = origPosition;
	for (int i = 0; i < HAND_SIZE; ++i) {
		draw(i);
	}
}


TileHand::~TileHand()
{
}
