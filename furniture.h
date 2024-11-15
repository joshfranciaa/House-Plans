#ifndef FURNITURE_H
#define FURNITURE_H

#include <map>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum class Direction { RIGHT, UP, DOWN, LEFT }; //Enum for which direction the furniture is facing
const int IMAGE_SIZE = 16; //Pixels per each dimension in the furniture images

//Catalog of all of the available furniture, indexed by name
class FurnitureCatalog
{
	static map<string, char**> catalog; //Dictionary containing all of the furniture info

	static char* parseImage(ifstream& infile, string end_token);
	static void sanitize(string& str);

	static const string directory;
	static const char* furnitureFiles[];
	static const int fileCount;
public:
	static void populate();
	static void deallocateFurniture();
	static void printCatalog();
	static char** getFurnitureImages(string name);
	static bool isInCatalog(string name);
};

//Class for an individual piece of furniture to be placed
class Furniture {
	string name;
	char** images; //Using pointers so each furniture points to the same image (don't need to duplicate per object)
	Direction direction;

public:
	Furniture() { name = ""; direction = Direction::RIGHT;  images = nullptr; }
	Furniture(string name, Direction direction = Direction::RIGHT) {
		//Set name and direction
		this->name = name;
		this->direction = direction;

		//Check if the name exists in the catalog
		if (FurnitureCatalog::isInCatalog(name))
			images = FurnitureCatalog::getFurnitureImages(name);
		else
		{
			images = nullptr;
			cout << "Could not find furniture: " << name << endl;
		}
	}

	char getImageChar(int x, int y);
	void printLine(int line);
	void setDirection(Direction direction) { this->direction = direction; }
};

#endif
