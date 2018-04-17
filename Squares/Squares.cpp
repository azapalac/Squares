// Squares.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Square.h"
#include "Tile.h"
#include "TileHand.h"
#include "TileBoard.h"
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

void AddToDrawList(Tile* t);

using namespace sf;
using namespace std;
vector<Tile*> tiles;
vector<Square*> drawList;
int nTilesPlaced = 0;
#define SCREEN_HEIGHT 1500
#define SCREEN_WIDTH 1000
#define DELTA 0.1f

int main()
{
	srand((unsigned)time(NULL)*time(NULL));

	RenderWindow window(VideoMode(SCREEN_HEIGHT, SCREEN_WIDTH), "Squares");
	Vector2f rectSize(50, 50);
	Vector2f rectDelta(1, 1);
	float speed = 1;
	Tile* selectedTile = NULL;
	TileHand* tileHand = new TileHand();
	TileBoard* board = new TileBoard();
	bool canRotate = true;
	//Add all tiles to draw list
	
	vector<Tile*>::iterator i;

	nTilesPlaced++;
	
	tiles.push_back(board->startingTile);
	AddToDrawList(board->startingTile);
	board->startingTile->orderPlaced = nTilesPlaced;

	for (int i = 0; i < HAND_SIZE; i++) {
		
		tiles.push_back(tileHand->hand[i]);
		AddToDrawList(tileHand->hand[i]);
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		Vector2i mousePos = Mouse::getPosition(window);

		//Select a tile if one isn't selected already;

		for (int k = 0; k < tiles.size(); ++k) {
			if (tiles[k] -> pointInBounds(mousePos) && Mouse::isButtonPressed(Mouse::Left) && tiles[k] -> canBeMoved) {
				//cout << "Selected tile " << k << endl;
				selectedTile = tiles[k];
			}
		}

		

		if (selectedTile != NULL) {
			Vector2f mousePosf((float)mousePos.x, (float)mousePos.y);
			selectedTile -> moveTo(mousePosf);
			if (Keyboard::isKeyPressed(Keyboard::R) && canRotate) {
				selectedTile->rotate();
				canRotate = false;
			}
			
			if (!Keyboard::isKeyPressed(Keyboard::R)) {
				canRotate = true;
			}


			if (Mouse::isButtonPressed(Mouse::Right)) {
				//Move the tile to the board
				if (board->snapToGrid(selectedTile)) {
					nTilesPlaced++;
					selectedTile->orderPlaced = nTilesPlaced;
					tileHand->hand[(*selectedTile).index] = NULL;
					tileHand->tilesInHand--;
					
					//cout << "Tiles in hand: " << tileHand->tilesInHand << endl;

				}
				selectedTile = NULL;
				canRotate = true;
			}
		}

		if (tileHand->tilesInHand == 0) {
			//Redraw a full hand
			if (tileHand->difficulty < MAX_DIFFICULTY) {
				tileHand->difficulty++;
			}
			tileHand->setUpHand();
			tileHand->tilesInHand = HAND_SIZE;

			for (int i = 0; i < HAND_SIZE; i++) {
				tiles.push_back(tileHand->hand[i]);


				AddToDrawList(tileHand->hand[i]);
			}
		}

		//USED FOR DEBUG PURPOSES ONlY
		//if (Keyboard::isKeyPressed(Keyboard::Space)) {
		//	selectedTile = NULL;
		//}
		for (int k = 0; k <tiles.size(); ++k) {
			tiles[k]->updateSquares();
		}

		window.clear();


		//vector<Square>::iterator j;
		for (i = tiles.begin(); i != tiles.end(); ++i) {
			if (i == tiles.begin()) {

			}
			window.draw((*i)->upLeft->image);
			window.draw((*i)->upRight->image);
			window.draw((*i)->bottomLeft->image);
			window.draw((*i)->bottomRight->image);
		}
		window.display();
	}

	return 0;
}


void AddToDrawList(Tile* t) {
	vector<Square> temp;
	drawList.push_back(t->upRight);
	drawList.push_back(t->upLeft);
	drawList.push_back(t->bottomRight);
	drawList.push_back(t->bottomLeft);
}

