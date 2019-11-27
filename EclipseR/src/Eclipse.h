/*
 * Eclipse.h
 *
 * This class creates an Eclipse Object that reads a line into columns through its constructor.
 * It also has private variables that flag the whole object as an error if the is a certain
 * index that has unlikely errors. The object can be printed to the console as a comma delimited line.
 *
 *  Created on: Sep 25, 2017
 *      Author: Clayton Glenn
 */

#ifndef ECLIPSE_H_
#define ECLIPSE_H_

#include <iostream>
#include <ostream>
#include <iomanip>
#include <string>

using namespace std;

/**
 * ECLIPSE OBJECT
 *
 * This class creates an Eclipse Object that reads a line into columns through its constructor.
 * It also has private variables that flag the whole object as an error if the is a certain
 * index that has unlikely errors. The object can be printed to the console as a comma delimited line.
 */
class Eclipse {
public:

	//Public Member Functions
	Eclipse(std::string line);
	Eclipse(const Eclipse &e);
	~Eclipse();
	void operator=(const Eclipse &e);
	friend ostream& operator<<(ostream& os, Eclipse &e);

	//Mutator Functions
	void setError();
	bool hasError();

	//Accessor Functions
	string* getColumns();
	int getSize();

private:

	//Private Variables
	string* columns;
	const int COLCAP = 20;
	int size;
	bool error;
};

/*
 * CONSTRUCTOR: Creates an object with given comma delimited line
 *
 * Author: Clayton Glenn
 */
Eclipse::Eclipse(std::string line) {

	this->columns = new string[COLCAP];
	std::string colLine = "";
	unsigned int charCount = 0;
	size = 0;

	//Push back each data in the columns to create array
	while (charCount < line.length()) {
		while (charCount < line.length() && line.substr(charCount, 1) != ",") {
			colLine.push_back(line.at(charCount));
			charCount++;
		}
		this->columns[size] = colLine;
		size++;
		charCount++;
		colLine = "";
	}
	this->error = false;

	//Return to calling function
	return;
}

/*
 * COPY CONSTRUCTOR: Copies data from one Eclipse object to Another
 *
 * Author: Clayton Glenn
 */
Eclipse::Eclipse(const Eclipse &e) {

	//Copy Data
	this->columns = e.columns;
	size = e.size;
	this->error = e.error;

	//Return to calling function
	return;
}

/*
 * = Operator: Copies data from one Eclipse object to Another
 *
 * Author: Clayton Glenn
 */
void Eclipse::operator=(const Eclipse &e) {

	//Copy Data
	this->columns = e.columns;
	size = e.size;
	this->error = e.error;

	//Return to calling function
		return;
}

/*
 * DESTRUCTOR: Deletes the array in object
 *
 * Author: Clayton Glenn
 */
Eclipse::~Eclipse() {

	//Delete the columns array in the eclipse object
	delete[] this->columns;

	//Return to calling function
		return;
}

/*
 * << OPERATOR: Prints the Eclipse object in a way specified by the program
 *
 * Author: Clayton Glenn
 */
ostream& operator<<(ostream& os, Eclipse& e) {

	//Make lines printable to outstream
	for (int count = 0; count < e.size; ++count) {
		if (count == (e.size - 1)) {
			os << e.columns[count];
		} else {
			if (e.columns[count + 1] == "") {
				os << e.columns[count];
			} else {
				os << e.columns[count] << ",";
			}
		}
	}
	cout << endl;

	//Return Outstream to calling function
	return os;
}

/*
 * Mutator Method: Sets an error on the object to show it is invalid
 *
 * Author: Clayton Glenn
 */
void Eclipse::setError() {

	//Set error to true
	this->error = true;

	//Return to calling function
		return;
}

/*
 * Accessor Method: Sees if object is valid for printing
 *
 * Author: Clayton Glenn
 */
bool Eclipse::hasError() {

	//Return the true or false depending on error to calling function
	return error;
}

/*
 * Accessor Method: Returns the eclipse objects columns
 *
 * Author: Clayton Glenn
 */
string* Eclipse::getColumns() {

	//Return the eclipses columns to calling function
	return this->columns;
}

/*
 * Accessor Method: Returns the actual size of the 20 element array
 *
 * Author: Clayton Glenn
 */
int Eclipse::getSize() {

	//Return the eclipses size to calling function
	return this->size;
}

#endif /* ECLIPSE_H_ */
