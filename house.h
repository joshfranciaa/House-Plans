#ifndef HOUSE_H
#define HOUSE_H

#include<string>
#include "floor.h"
#include "furniture.h"

using namespace std;

//A dynamically resizing list of the residents in the house
class ResidentList
{
	string* residents; //Array containing the name of all residents in the list
	int residentCount; //How many residents are on the list
	int arraySize; //Size of the residents array
	const int SIZE_INCREASE = 3;

public:
	ResidentList() { residents = nullptr; residentCount = arraySize = 0; }
	ResidentList(int size);
	~ResidentList();

	void addResidentToList(string resident_name);
	void printResidents();
};

//A class representing a house to build and decorate
class House
{
	ResidentList residentList; //List of the residents of this house
	Floor** floors; //1D Array of the floors in the house. The second pointer is because the array contains pointers.
	int floorCount; //How many floors there are

public:
	House(int num_floors);
	~House();

	void buildFloor(int floor_num, int width, int height);
	void addFurniture(int floor_num, int x, int y, Furniture furniture);
	void displayHouse();
	void addResidentToHouse(string resident_name);
};

#endif
