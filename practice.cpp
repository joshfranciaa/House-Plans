/*This is a short worksheet-esque program to get you familiar with the basics of pointers.
The program is not directly related to the main assignment, but suggested as a starting point to 
get used to using pointers. We'll go through a few examples an observe some properties of dynamic execution */

#include <iostream>
#include <string>

//#define SHOW_EXAMPLE //Comment this out to turn off showing the example code output. Uncomment to display

using namespace std;

//Sample Person class for an example
class Person
{
	string name;
	int age;
	static int count;
public:
	Person() { count++; }
	Person(string name, int age) { this->name = name; this->age = age; count++; }

	static int getCount() { return count; }
	void sayName() { cout << "Hello, my name is " << name << endl; }
};

const int ARRAY_SIZE = 3;
int Person::count = 0;

void exampleCode();

int main()
{
#ifdef SHOW_EXAMPLE
	exampleCode(); //Example code below. Only shown if preprocessor define at top is uncommented.

#else

	//TODO: Add your code to meet the descriptions of the following comments. Please see the exampleCode function
	//for references 

	//Start by allocating a single Person using the p pointer. Set their name to "John Doe" and age to 25
	Person* p;

	//TODO: YOUR CODE HERE
	p = new Person("John Doe", 25);

	//Make p say their name
	//TODO: YOUR CODE HERE
	p->sayName(); 

	//Allocate an array of 5 Persons using the arr pointer
	Person* arr;

	//TODO: YOUR CODE HERE
	arr = new Person[5];
	//Allocate an array of 3 Person references. Allocate each of the 3 people using the following info:
	//Person 0: Jane Doe, 30
	//Person 1: Jake Doe, 32
	//Person 2: Julie Doe, 24

	Person** personArr;

	//TODO: YOUR CODE HERE
	personArr = new Person*[3];
	personArr[0] = new Person("Jane Doe", 30);
	personArr[1] = new Person("Jake Doe", 32);
	personArr[2] = new Person("Julie Doe", 24);

	for (int i = 0; i < 3; i++)
		personArr[i]->sayName();

	//This code prints the number of Persons allocated. You should get 9
	cout << "Allocated " << Person::getCount() << " Persons" << endl;

	//Finally, deallocate everything. Deallocate Person p, the arr, the 3 Persons in the personArr and the array itself
	//TODO: YOUR CODE HERE
	delete p;
	delete[] arr;
	for(int i = 0; i < 3; i++) {
		delete personArr[i];
	}
	delete[] personArr; 
	
	#endif
}

//This function contains a detailed explanation on how pointers work. Please use the code for reference
void exampleCode()
{
	/*Pointers are used to hold addresses which point to* where* memory has been allocated
		While in reality they represent some long bit string address, it may be more helpful to conceptualize
		a reference as a name that refers to an object when doing OOP */

		//Consider this non-pointer code
	Person p;
	string name;
	int age;

	cout << "Enter a name" << endl;
	cin >> name;
	cout << "Enter an age" << endl;
	cin >> age;
	p = Person(name, age);

	cout << "(0) Persons constructed: " << Person::getCount() << endl << endl;

	/*We cannot initialize the Person until we know their nameand age, read from the user.
	However, the line: Person p automatically constructs a Person (whether we like it or not)
	Notice that the above code creates two Persons. On the other hand, we can delay the creation
	of an object by using a pointer (since using a reference will only create space for a pointer,
	but not automatically make an object). This is also helpful if the class does not contain a default constructor
	and thus cannot be created with a simple declaration. */

	Person* q; //Does not automatically construct a Person

	cout << "Enter a name" << endl;
	cin >> name;
	cout << "Enter an age" << endl;
	cin >> age;
	q = new Person(name, age); //Dynamic allocation using "new". The constructor only gets called here when we explicitly put it

	cout << "(1) Persons constructed: " << Person::getCount() << endl << endl;

	//Notice that only one Person got constructed by this snippet. Using pointers/references allow us to 
	//create objects only when we need them, rather than let the compiler do it whenever

	//We can access members of a pointer/reference by using the arrow -> operator. It is almost identical to the 
	//dot operator, but for pointers:

	p.sayName(); //p says their name
	q->sayName(); //q says their name, but q is a pointer

	//Using references also allows for efficient array allocation. The below code will automatically create 
	//20 Person objects, regardles of how much of the array we actually want to use
	Person personArray[ARRAY_SIZE];

	cout << "(2) Persons constructed: " << Person::getCount() << endl << endl;

	//Using an array of references however:
	Person* personRefArray[ARRAY_SIZE];

	cout << "(3) Persons constructed: " << Person::getCount() << endl << endl;

	//Nobody gets allocated until we actually ask them to be 

	personRefArray[0] = new Person("John Doe", 25); //Make exactly one Person and put them into the array

	cout << "(4) Persons constructed: " << Person::getCount() << endl << endl;

	/* We can also use pointers to create arrays while our program is running.Consider the previous example array:
	Person personArray[ARRAY_SIZE]
	This array will always contain 20 Persons, even if we don't need that many. With dynamic allocation, we can allocate
	arrays to be as big as we need them to be */

	int dynArraySize;
	Person* dynArray;

	cout << "How big should the dynamic array be? " << endl;
	cin >> dynArraySize;

	dynArray = new Person[dynArraySize]; //The "new" keyword can also be used to make arrays, with new type[size]

	cout << "(5) Persons constructed: " << Person::getCount() << endl << endl;

	/* Notice that both an object and an array can be referenced with a pointer. We can't tell the difference 
	without the context of the code, so make sure you name variables to indicate their purpose. dynArray and q are both Person*
	type variables, but represent an array and object, respectively. 
	
	We can combine these two uses of pointers together: */

	Person** dynArrayOfReferences; //Will point to a 1D array of Person*s. The two **s come from the array and its contents being pointers
	dynArrayOfReferences = new Person*[dynArraySize];

	for (int i = 0; i < dynArraySize / 2; i++) //Fill half the array to demonstrate we can allocate just a portion 
		dynArrayOfReferences[i] = new Person("Jane Doe", 23);

	cout << "(6) Persons constructed: " << Person::getCount() << endl << endl;

	/*Finally, let's cover deallocating memory. When you explicitly allocate memory with "new" or C's malloc, you will also need
	to deallocate it yourself. Before pointers, the compiler/runtime environment automatically handled allocation and dellocation
	for us. We will now need to clean up any dynamically allocated memory. 
	
	Memory can be deallocated using the delete keyword */

	delete q; //Deletes the Person object pointed to by q

	delete[] dynArray; //Arrays are deallocated using delete[]

	q = nullptr; //nullptr is a default value that can be used to represent pointing to nothing

	//Deallocate the rest of what we made
	delete personRefArray[0]; //Delete John Doe

	//Delete the Jane Does
	for (int i = 0; i < dynArraySize / 2; i++)
		delete dynArrayOfReferences[i];

	//And the array that held them
	delete[] dynArrayOfReferences;

	//That concludes the basics on pointers. Give main() a shot!
}