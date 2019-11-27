/*
 * Eclipse.cpp
 *
 * This Program reads data from an eclipse data file and creates a
 * comma delimited output file. It also checks for errors in the eclipse input.
 *
 *  Created on: Sep 25, 2017
 *      Author: cglen
 */

#include "ResizableArray.h"
#include "Eclipse.h"

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

/**
 * Function borrowed from stack overflow and manipulated to fit format
 * to check if string is an integer
 *
 * Author: paercebal & Clayton Glenn
 */
bool isInteger(std::string & s) {

	//If quick fails, get out quick
	if (s.empty()
			|| ((!isdigit(s[0])) && (s[0] != '-' && s.length() == 1)
					&& (s[0] != '+')))
		return false;

	//If only 0, return true
	if (s[0] == '0' && s.length() == 1) {
		return true;
	}

	//pull numbers out of string
	char * p;
	strtol(s.c_str(), &p, 10);

	//If non numbers detected, return false
	if (*p != '\0' || p == s) {
		return false;
	}

	//Default, return true to main
	return true;
}

/**
 * Function derived from isInteger function from stack overflow
 * to check if string is a double
 *
 * Author: paercebal & Clayton Glenn
 */
bool isDouble(std::string & s) {

	//If not number in quick check, exit false fast
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) {
		return false;
	}

	//Pull numbers and decimals out of string
	char* p;
	strtod(s.c_str(), &p);

	//If non numbers detected, return false
	if (*p != '\0' || p == s) {
		return false;
	}

	//Default, return true to main
	return true;
}

bool isChar(char a, char b[], int bNum) {

	//Check Array for matching character
	for (int i = 0; i < bNum; ++i) {
		if (a == b[i]) {
			return true;
		}
	}

	//Return to main
	return false;
}

int main() {

	//Create Character Array with every character on my
	//keyboard which omits any kind of whitespace
	const int CHARNUM = 85;
	int integers[10] = { 0, 1, 2, 4, 6, 7, 8, 14, 15, 16 };
	int doubles[2] = { 10, 11 };
	char character[CHARNUM] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
			'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
			'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
			'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
			'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			'0', '<', '.', '>', '/', '?', ':', '|', '~', '`', '!', '@', '#',
			'$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+' };
	ResizableArray<string>* catNums = new ResizableArray<string>();
	string* columns;

	//Skip header lines of the input file
	string line = "", line2 = "";
	for (int i = 0; i < 10; ++i) {
		getline(cin, line);
	}

	//Create a dynamic array to store eclipses
	ResizableArray<Eclipse*>* a = new ResizableArray<Eclipse*>();

	//Declare an eclipse for later initialization
	Eclipse* e;

	while (cin.good()) {
		//Get next line from input file while input is good
		getline(cin, line);

		//To handle garbage like Random NewLine Characters
		if (line != "") {
			//If a line is actually generated, Comma delimit it.
			for (unsigned int count = 0; count < line.length(); ++count) {
				if (isChar(line.at(count), character, CHARNUM)) {
					line2.push_back(line.at(count));
				}
				if (isspace(line.at(count)) && (count != 0)) {
					if (isChar(line.at(count - 1), character, CHARNUM)) {
						line2.push_back(',');
					}
				}
			}
			if (line2.at(line2.length() - 1) == ',') {
				line2.erase(line2.length() - 1, 1);
			}

			//Create new eclipse with comma delimitted line
			e = new Eclipse(line2);

			columns = e->getColumns();

			//Check for Right amount of columns in each row
			if (columns[9].substr(0, 1) == "P") {
				if (e->getSize() != 16) {
					cerr << "Error in data row " << columns[0] << ": "
							<< e->getSize()
							<< " columns found. Should be 16.";
					cerr << endl;
					e->setError();
				}
			} else {
				if (e->getSize() != 18) {
					cerr << "Error in data row " << columns[0] << ": "
							<< e->getSize()
							<< " columns found. Should be 18.";
					cerr << endl;
					e->setError();
				}
			}

			//Check for integer values in certain columns
			if (!e->hasError()) {
				for (int i = 0; i < 10; ++i) {
					line = columns[integers[i]];
					if (columns[9].substr(0, 1) == "P") {
						if (i != 9) {
							if (!isInteger(line)) {
								cerr << "Error in data row " << columns[0]
										<< ": Column " << integers[i] + 1
										<< " is not a whole number." << endl;
								e->setError();
							}
						}
					} else {
						if (!isInteger(line)) {
							cerr << "Error in data row " << columns[0]
									<< ": Column " << integers[i] + 1
									<< " is not a whole number." << endl;
							e->setError();
						}
					}
				}

				//Check for double values in certain columns
				for (int i = 0; i < 2; ++i) {
					line = columns[doubles[i]];
					if (!isDouble(line)) {
						cerr << "Error in data row " << columns[0]
								<< ": Column " << doubles[i] + 1
								<< " is not a decimal number." << endl;
						e->setError();
					}
				}
			}

			//Check for unique catalog numbers in each data line
			if (!e->hasError()) {
				if (catNums->getSize() != 0) {
					for (int i = 0; i < catNums->getSize(); ++i) {
						if (columns[0] == catNums->at(i)) {
							cerr << "Error in data row " << columns[0]
									<< ": Duplicate catalog number "
									<< columns[0] << "." << endl;
							e->setError();
						}
					}
				}
				if (!e->hasError()) {
					catNums->add(columns[0]);
				}
			}
			if (!e->hasError()) {
				a->add(e);
			}

			//Reset the comma string
			line2 = "";
		}
	}
	cout << a;
}

