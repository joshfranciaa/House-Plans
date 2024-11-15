#ifndef FLOOR_H
#define FLOOR_H

#include <iostream>
#include "furniture.h"

using namespace std;

//A single floor of the house. This contains tiles where furniture can be placed
class Floor
{
	Furniture** floorTiles; //2D dynamic array of the tiles that make up the floor
	int width, height; //Dimensions of the floor (and the array)

public:
	Floor(int width, int height);
	~Floor();

	void addFurniture(Furniture piece, int x, int y);
	void printFloor();
	bool isInBounds(int x, int y);
	void printDimensions() { cout << width << "x" << height; }
};

#endif
