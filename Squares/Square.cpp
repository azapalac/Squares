#include "stdafx.h"
#include "Square.h"



Square::Square(int difficulty)
{	//Make a new square
	//set the color to a random value
	Vector2f squareSize(SQUARE_SIDE_LENGTH, SQUARE_SIDE_LENGTH);
	RectangleShape shape(squareSize);
	Color c = randomColor(difficulty);
	image = shape;
	image.setFillColor(c);
	color = c;
	shifting = false;
	
}



Square::~Square()
{
}


Vector2f Square::getPosition() {
	return image.getPosition();
}

void Square::shiftNext() {
	if (!shifting) {
		shifting = true;
		currentPosition = getPosition();
		nextPosition = (*next).getPosition();
	}
}

void Square::updatePosition() {


	float epsilon = 0.007f;
	if (shifting) {
		Vector2f delta(nextPosition.x - currentPosition.x, nextPosition.y - currentPosition.y);
		image.move(delta);
		shifting = false;
	}
}

Color Square::randomColor(int difficulty){
	int upperLimit = difficulty;
	int r = rand()%(upperLimit + 1);
	Color c;
	switch (r) {
	case 0:
		c = Color::Blue;
		break;
	case 1:
		c = Color::Green;
		break;
	case 2:
		c = Color::Red;
		break;
	case 3: 
		c = Color::White;
		break;
	case 4:
		c = Color::Yellow;
		break;
	case 5:
		c = Color::Cyan;
		break;
	case 6:
		c = Color::Magenta;
		break;


	default:
		//Square will not be visible if there is an error
		c = Color::Black;
		break;
	}

	return c;
}

float magnitude(Vector2f v) {
	float m = 0;
	m = sqrtf((v.x*v.x) + (v.y*v.y));


	return m;
}