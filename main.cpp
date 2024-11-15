#include <iostream>
#include <string>
#include "furniture.h"
#include "floor.h"
#include "house.h"

using namespace std;

int getPositiveInt();
char getOption();
Direction getDirection();

int main()
{
	//Create the house and floors
	House* house; //Declare the house variable, but don't make the House until we have the number of floors
	cout << "How many floors?" << endl;
	int floors = getPositiveInt();
	house = new House(floors); 
	//Notice that we can delay the creation of a House until after the floor count is read by using pointers!

	//Build all of the floors
	int width, height;
	for (int i = 0; i < floors; i++)
	{
		cout << "Enter the dimensions for floor " << i << endl;

		cout << "Enter width: " << endl;
		width = getPositiveInt();

		cout << "Enter height: " << endl;
		height = getPositiveInt();

		house->buildFloor(i, width, height); //Build a floor with the read dimensions
	}

	//Adding residents to the house
	int residentCount = 1;
	string name;
	while (true)
	{
		cout << "Enter the name for resident " << residentCount << endl;
		cin >> name;
		house->addResidentToHouse(name);
		residentCount++;
		cout << "Would you like to add another resident (Y/N)?" << endl;
		if(getOption() == 'n') break;
	}

	//Adding furniture
	FurnitureCatalog::populate(); //Populate the furniture catalog using the furniture files
	FurnitureCatalog::printCatalog(); //Print the catalog

	Direction direction;
	cout << "What furniture would you like to add?" << endl;
	while (true)
	{
		cin >> name; //Read the furniture to add

		//If the furniture entered was not in the catalog, reprompt
		if (!FurnitureCatalog::isInCatalog(name))
		{
			cout << "Could not find item " << name << ". Please enter an item from the catalog:" << endl;
			FurnitureCatalog::printCatalog();
			continue;
		}

		//Ask the user for where to put the furniture
		cout << "What floor would you like to place the " << name << " on?" << endl;
		floors = getPositiveInt(); //Re-use floors variable for floor number

		cout << "What x position? " << endl;
		width = getPositiveInt();

		cout << "What y position? " << endl;
		height = getPositiveInt();

		cout << "Facing what direction? " << endl;
		direction = getDirection();

		//Place the furniture with the read traits
		house->addFurniture(floors, width, height, Furniture(name, direction));

		cout << "Would you like to add more furniture (Y/N)?" << endl;
		if(getOption() == 'n') break;
		cout << "What furniture should be added next?" << endl;
	}
	house->displayHouse(); //Display the descorated house

	delete house; //Deallocate the house
	FurnitureCatalog::deallocateFurniture(); //Deallocate the furniture from the catalog
}

//Gets the next valid option from the user and reprompts as needed
char getOption()
{
	char option;

	//Print prompt
	cin >> option;
	while (cin.fail() || (option != 'y' && option != 'n' && option != 'Y' && option != 'N'))
	{
		cout << "The letter entered does not match any of the choices, please try again." << endl;
		cin.ignore(1024);
		cin.clear();
		cin >> option;
	}

	return tolower(option);
}

//Gets a positive int from the user and handles error checking
int getPositiveInt()
{
	int value;

	cin >> value;
	while (cin.fail() || value < 0)
	{
		cout << "Could not read a number. Please enter a non-negative integer" << endl;
		cin.ignore(1024);
		cin.clear();
		cin >> value;
	}

	return value;
}

Direction getDirection()
{
	char option;

	//Print prompt
	cin >> option;
	option = tolower(option);
	while (cin.fail() || (option != 'r' && option != 'l' && option != 'u' && option != 'd'))
	{
		cout << "Please choose between left, right, up, or down (l, r, u, d)." << endl;
		cin.ignore(1024);
		cin.clear();
		cin >> option;
		option = tolower(option);
	}

	//Convert character to Direction enum
	switch (option)
	{
		case 'r':
			return Direction::RIGHT;
		case 'l':
			return Direction::LEFT;
		case 'd':
			return Direction::DOWN;
		case 'u':
			return Direction::UP;
		default:
			return Direction::RIGHT;
	}
}