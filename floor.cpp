/*
Name: Joshua Francia, 2002157323, CS 202, Assignment #4
Description: Dynamically allocating space to form a House
Input: User-inputted buttons to browse through the house
Output: Outputs the floors and furnitures of the house
*/


#include "floor.h"
#include <iomanip>

using namespace std;

/*  */
Floor::Floor(int width, int height)
{
	//Set the width and height members to the corresponding parameters
	this->width = width; 
	this->height = height; 
	//Then allocate the floorTiles array to be a height x width 2D array of furniture
	
	//Start by allocating an array of size height and then populate that array with pointers to arrays of size width

	//TODO: Finish the function
	floorTiles = new Furniture*[height];
	for(int i = 0; i < height; i++) {
		floorTiles[i] = new Furniture[width];
	}
}

/*  */
Floor::~Floor()
{
	//Deallocate the 2D floorTiles array that was allocated in the constructor
	//Deallocate each of the width arrays followed by deallocating the height array
	//The contents of the array are not pointers and do not need to be deallocated

	//TODO: Finish the function
	for(int i = 0; i < height; i++) {
		delete[] floorTiles[i];
	}
	delete[] floorTiles; 
}

/* Puts the piece of furniture at the given x, y position in the */
void Floor::addFurniture(Furniture piece, int x, int y)
{
	floorTiles[y][x] = piece;
}

/* Prints all of the furniture on a floor */
void Floor::printFloor()
{
	int i, j, k;

	//Print top wall
	cout << setw(IMAGE_SIZE * width + 4) << setfill('-') << "" << setfill(' ') << endl;

	for (i = 0; i < height; i++)
	{
		for (k = 0; k < IMAGE_SIZE; k++)
		{
			cout << "| "; //Print left wall
			for (j = 0; j < width; j++)
				floorTiles[i][j].printLine(k);

			cout << " |" << endl; //Print right wall
		}
	}

	//Print bottom wall
	cout << setw(IMAGE_SIZE * width + 4) << setfill('-') << "" << setfill(' ') << endl;
}

//Tells whether the given (x, y) position is within the bounds of the floor
bool Floor::isInBounds(int x, int y)
{
	return x >= 0 && x < width && y >= 0 && y < height;
}