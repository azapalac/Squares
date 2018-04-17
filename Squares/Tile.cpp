#include "stdafx.h"
#include "Tile.h"


Tile::Tile(int difficulty)
{
	//Set up individual squares
	upLeft = new Square(difficulty);
	upRight = new Square(difficulty);
	bottomLeft = new Square(difficulty);
	bottomRight = new Square(difficulty);

	upLeft -> next = upRight;
	upRight -> next = bottomRight;
	bottomRight -> next = bottomLeft;
	bottomLeft -> next = upLeft;

	upLeft->across = bottomRight;
	bottomRight->across = upLeft;

	(*upRight).image.move(TILE_OFFSET, 0);
	(*bottomLeft).image.move(0, TILE_OFFSET);
	(*bottomRight).image.move(TILE_OFFSET, TILE_OFFSET);

	
	//Rectangle starts at origin before moving
	boundary.top = 0;
	boundary.left = 0;
	boundary.width = TILE_SIDE_LENGTH;
	boundary.height = TILE_SIDE_LENGTH;
}


Tile::~Tile()
{
}

void Tile::move(Vector2f v) {
	move(v.x, v.y);
}

void Tile::move(float x, float y) {
	(*upLeft).image.move(x, y);
	(*upRight).image.move(x, y);
	(*bottomLeft).image.move(x, y);
	(*bottomRight).image.move(x, y);
	boundary.top += y;
	boundary.left += x;
}


void Tile::moveTo(Vector2f v) {

	Vector2f delta = v - getPosition();
	move(delta.x, delta.y);
}

void Tile::moveTo(float x, float y) {
	(*upLeft).image.setPosition(x, y);
	(*upRight).image.setPosition(x, y);
	(*bottomLeft).image.setPosition(x, y);
	(*bottomRight).image.setPosition(x, y);

}

void  Tile::draw(RenderWindow window) {
	window.draw((*upLeft).image);
	window.draw((*upRight).image);
	window.draw((*bottomLeft).image);
	window.draw((*bottomRight).image);
	
}

void Tile::rotate() {

		Square* temp;
		temp = upLeft;
		upLeft = bottomLeft;
		bottomLeft = bottomRight;
		bottomRight = upRight;
		upRight = temp;

		(*upLeft).shiftNext();
		(*upRight).shiftNext();
		(*bottomLeft).shiftNext();
		(*bottomRight).shiftNext();

}

void Tile::updateSquares() {
	(*upLeft).updatePosition();
	upLeft->image.setFillColor(upLeft->color);

	(*upRight).updatePosition();
	upRight->image.setFillColor(upRight->color);

	(*bottomLeft).updatePosition();
	bottomLeft->image.setFillColor(bottomLeft->color);

	(*bottomRight).updatePosition();
	bottomRight->image.setFillColor(bottomRight->color);
}

Vector2f Tile::getPosition() {
	Vector2f v(0, 0);
	if (upLeft != NULL) {
		v = (*upLeft).getPosition();
	}

	v.x += (SQUARE_SIDE_LENGTH * 2) + (TILE_OFFSET - SQUARE_SIDE_LENGTH);
	v.y += (SQUARE_SIDE_LENGTH * 2) + (TILE_OFFSET - SQUARE_SIDE_LENGTH);
	return v;
}

bool Tile::pointInBounds(Vector2i point) {
	//Need to convert the int vector to a float 
	Vector2f pointf((float)point.x, (float)point.y);
	return boundary.contains(pointf);
}