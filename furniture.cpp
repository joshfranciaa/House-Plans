//This file contains implementations for the Furniture and FurnitureCatalog classes.
//YOU DO NOT NEED TO ADD ANY CODE HERE
//However, please feel free to look through the code to gain a better understanding of efficient memory usage
//Note that some functions are written in the furniture.h file

#include <string>
#include <fstream>
#include "furniture.h"

using namespace std;

//Setting static fields
const string FurnitureCatalog::directory = "furniture_files";
const char* FurnitureCatalog::furnitureFiles[] = { "chair.furn", "table.furn", "lamp.furn", "rug.furn" };
const int FurnitureCatalog::fileCount = 4;
map<string, char**> FurnitureCatalog::catalog;

//------------------------------ Furniture ------------------------------

//Gets the char in the ASCII art for this furniture
char Furniture::getImageChar(int x, int y)
{
	if (images == nullptr)
		return ' ';

	//Draw left facing sprites as right facing, but flipped horizontally
	if (direction == Direction::LEFT)
		return images[0][IMAGE_SIZE * y + IMAGE_SIZE - x - 1]; //Note: 0 is the enum value for RIGHT

	return images[static_cast<int>(direction)][IMAGE_SIZE * y + x]; //Else return pixel from direction's image
}

//Prints the given line of the Furniture's image (used for rendering)
void Furniture::printLine(int line)
{
	if (images == nullptr)
	{
		for (int j = 0; j < IMAGE_SIZE; j++)
			cout << ' ';
		return;
	}
	else if (direction == Direction::LEFT) //For left, print right image backwards
	{
		int end = line * IMAGE_SIZE;
		int i = end + IMAGE_SIZE - 1;
		for (; i >= end; i--)
			cout << images[0][i]; //Note: 0 is the enum value for RIGHT
	}
	else
	{
		int facing_direction = static_cast<int>(direction);
		int i = line * IMAGE_SIZE;
		int end = i + IMAGE_SIZE;
		for (; i < end; i++)
			cout << images[facing_direction][i]; //Note: 0 is the enum value for RIGHT
	}
}

//------------------------------ FurnitureCatalog ------------------------------
//Populates the FurnitureCatalog using the list of files in the header file
void FurnitureCatalog::populate()
{
	//Sadly the iterator for files in a directory was not introduced until C++17 :(
	//Will use a static array instead

	ifstream infile;
	char** images;
	string furnitureName;
	for (int i = 0; i < fileCount; i++)
	{
		infile.open(directory + "/" + furnitureFiles[i]);
		images = new char*[3]; //Make an array to hold right, up, down images
		getline(infile, furnitureName); //First line is furniture's name
		sanitize(furnitureName);
		images[0] = parseImage(infile, "endright"); //Read right facing sprite
		images[1] = parseImage(infile, "endup"); //Read up facing sprite
		images[2] = parseImage(infile, "enddown"); //Read down facing sprite
		catalog[furnitureName] = images; //Put the furniture into the catalog
		infile.close();
	}

}

//Deallocates all of the furniture allocated and placed within the map
void FurnitureCatalog::deallocateFurniture()
{
	int j;
	for (map<string, char**>::iterator i = catalog.begin(); i != catalog.end(); i++)
		if (i->second != nullptr)
		{
			//Delete each image
			for (j = 0; j < 3; j++)
				delete[] i->second[j];
			delete[] i->second; //Delete array holding direction pointers
		}
}

//Returns the array of images (right, up, down facing) for the furniture with the given name
char** FurnitureCatalog::getFurnitureImages(string name)
{
	return catalog[name];
}

//Tells whether or not a furniture item with the given name is in the catalog
bool FurnitureCatalog::isInCatalog(string name)
{
	return catalog.find(name) != catalog.end();
}

string temp_image[IMAGE_SIZE]; //Used to have a static variable across calls for efficiency
//Parses the next image in the file until the end_token is hit and returns the array holding the image
char* FurnitureCatalog::parseImage(ifstream& infile, string end_token)
{
	int lineCount = 0;
	int maxWidth = 0;
	int tempLength, startIndex;
	getline(infile, temp_image[0]);
	sanitize(temp_image[0]);

	//Handle any possible blank lines
	while (temp_image[0].compare("") == 0) //Read until there is no blank line
	{
		getline(infile, temp_image[0]);
		sanitize(temp_image[0]);
	}
	lineCount++;

	//Read each line of the picture
	bool foundEndToken = false;
	getline(infile, temp_image[lineCount]);
	sanitize(temp_image[lineCount]);
	while (!infile.eof() && !foundEndToken && lineCount < IMAGE_SIZE - 1)
	{
		//Get the length of the last read line and record its length for future centering
		tempLength = static_cast<int>(temp_image[lineCount].length());
		if (tempLength > maxWidth)
			maxWidth = tempLength;

		//Check if the line read is valid
		if (maxWidth > IMAGE_SIZE)
		{
			cout << "Error: Length of line " << lineCount + 1 << " before end token "
				<< end_token << " is too long" << endl;
			exit(1);
		}

		//Increment the lineCount and try to get the next line
		lineCount++;
		getline(infile, temp_image[lineCount]);
		sanitize(temp_image[lineCount]);

		foundEndToken |= temp_image[lineCount].compare(end_token) == 0; //Check if the endToken was found
	}

	//If the end token was never found, continue to parse for it
	while(!infile.eof() && !foundEndToken)
	{
		getline(infile, temp_image[lineCount]);
		sanitize(temp_image[lineCount]);
		foundEndToken |= temp_image[lineCount].compare(end_token) == 0; //Check if the endToken was found
	}

	//Convert the image from strings into the array and center it
	char* result = new char[IMAGE_SIZE * IMAGE_SIZE];
	int i, j;
	int lastIndex = 0;

	//Pad the top with spaces
	startIndex = (IMAGE_SIZE / 2) - (lineCount / 2);
	for (i = 0; i < startIndex; i++)
		for (j = 0; j < IMAGE_SIZE; j++)
			result[lastIndex++] = ' ';

	//Fill in the middle of the image
	for (i = 0; i < lineCount; i++)
	{
		//Find where to start putting the line so it is centered
		startIndex = (IMAGE_SIZE / 2) - (maxWidth / 2);

		//Pad to the left with spaces
		for (j = 0; j < startIndex; j++)
			result[lastIndex++] = ' ';

		//Fill in with the drawing chars
		tempLength = static_cast<int>(temp_image[i].length());
		for (j = 0; j < tempLength; j++)
			result[lastIndex++] = temp_image[i][j];

		//Pad to the right with spaces
		for (j = startIndex + tempLength; j < IMAGE_SIZE; j++)
			result[lastIndex++] = ' ';
	}

	for (i++; i < IMAGE_SIZE; i++)
		for (j = 0; j < IMAGE_SIZE; j++)
			result[lastIndex++] = ' ';

	return result;
}

//Prints all of the items in the furniture catalog
void FurnitureCatalog::printCatalog()
{
	int num = 1;
	cout << "-------------------- Furniture Catalog --------------------" << endl;
	for (map<string, char**>::iterator i = catalog.begin(); i != catalog.end(); i++)
	{
		cout << num << ". " << i->first << endl;
		num++;
	}
	cout << endl << endl; 
}

//Sanitizes a string by changing all linefeeds to '\n'
void FurnitureCatalog::sanitize(string& str)
{
	if(str[str.length() - 1] == '\r')
		str = str.substr(0, str.length() - 1);
}