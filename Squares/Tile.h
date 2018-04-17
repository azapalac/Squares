#pragma once
#include "Square.h"
#include <vector>
#include <SFML/Graphics.hpp>
//Each tile is 110 by 110


#define TILE_OFFSET 60
#define TILE_SIDE_LENGTH 110

class Tile
{
public:
	Square* upLeft;
	Square* upRight;
	Square* bottomLeft;
	Square*	bottomRight;
	bool canBeMoved = true;
	int index;
	int orderPlaced = 0;
	Vector2f getPosition();
	void rotate();
	bool pointInBounds(Vector2i point);
	void draw(RenderWindow window);


	void move(float x, float y);
	void move(Vector2f v);
	void moveTo(float x, float y);
	void moveTo(Vector2f v);


	void snapToGridPoint(Vector2f point);
	
	Vector2f origPosition;
	void updateSquares();
	Tile* randomTile();


	FloatRect boundary;


	Tile(int difficulty);
	~Tile();
};

