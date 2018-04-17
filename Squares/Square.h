#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SQUARE_SIDE_LENGTH 50
using namespace sf;
float magnitude(Vector2f v);
class Square 
{
public:
	RectangleShape image;
	Color color;
	Square* next;
	Square* across;
	bool shifting;
	Vector2f getPosition();
	void updatePosition();
	void shiftNext();
	
	Square(int difficulty);
	~Square();

private:
	Vector2f currentPosition;
	Vector2f nextPosition;
	Color randomColor(int difficulty);

	
};

//int difficulty = 3;