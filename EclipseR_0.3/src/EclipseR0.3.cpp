/*
 * EclipseR0.3.cpp
 *
 * This program uses Dynamic Array Templates to read a column file.
 * It comma delimits the data and checks for input errors.
 *
 *  Created on: Sep 17, 2017
 *      Author: Clayton Glenn
 */

#include <iostream>
#include <string>
#include "EclipseR0.3.h"

using namespace std;

/**
 * A Function used to check if a Character is not a Space
 *
 * Author: Clayton Glenn
 */
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

	//If quick fails, get out quick
	if (s.empty()
			|| ((!isdigit(s[0])) && (s[0] != '-' && s.length() == 1)
					&& (s[0] != '+')))
		return false;

	//If only 0, return true
	if (s[0] == '0' && s.length() == 1) {
		return true;
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

/*
 * This function uses Dynamic Array Templates to read a column file.
 * It comma delimits the data and checks for input errors
 */
int main() {

	//Initiallize Variables
	string line, line2 = "";
	bool error = false;
	ArrayList<string>* data = new ArrayList<string>();
	ArrayList<string>* catalogNumArray = new ArrayList<string>();
	int characterNum = 85, intNum = 10, doubleNum = 2;
	int intValues[intNum] = { 0, 1, 2, 4, 6, 7, 8, 14, 15, 16 };
	int doubleValues[doubleNum] = { 10, 11 };
	char character[characterNum] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
			'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
			'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
			'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
			'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8',
			'9', '0', '<', '.', '>', '/', '?', ':', '|', '~', '`', '!', '@',
			'#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+' };

	//Read through Headers in Data File
	for (int i = 0; i < 10; ++i) {
		getline(cin, line);
	}

	//Read through Each Line, Comma Delimit it, and Store in ArrayList
	while (cin.good()) {
		std::getline(cin, line);
		for (unsigned int count = 0; count < line.length(); ++count) {
			if (isChar(line.at(count), character, characterNum)) {
				line2.push_back(line.at(count));
			}
			if (isspace(line.at(count)) && (count != 0)) {
				if (isChar(line.at(count - 1), character, characterNum)) {
					line2.push_back(',');
				}
			}
		}
		if (line2.at(line2.length() - 1) == ',') {
			line2.erase(line2.length() - 1, 1);
		}
		data->add(line2);
		line2 = "";
	}

	//Store each item in Data Line in column for Integrity Check
	for (int count = 0; count < data->length(); ++count) {
		ArrayList<string>* column = new ArrayList<string>();
		line = data->get(count);
		string lineInColumn = "";
		for (unsigned int i = 0; i < line.length(); ++i) {
			if (line.substr(i, 1) == ",") {
				column->add(lineInColumn);
				lineInColumn = "";
			} else {
				lineInColumn.push_back(line.at(i));
			}
		}
		column->add(lineInColumn);

		//Check for Right amount of columns in each row
		if (column->get(9).substr(0, 1) == "P") {
			if (column->length() != 16) {
				cerr << "Error in data row " << column->get(0) << ": "
						<< column->length() << " columns found. Should be 16."
						<< endl;
				error = true;
			}
		} else {
			if (column->length() != 18) {
				cerr << "Error in data row " << column->get(0) << ": "
						<< column->length() << " columns found. Should be 18."
						<< endl;
				error = true;
			}
		}

		//Check for integer values in certain columns
		if (!error) {
			for (int i = 0; i < intNum; ++i) {
				lineInColumn = column->get(intValues[i]);
				if (column->get(9).substr(0, 1) == "P") {
					if (i != intNum - 1) {
						if (!isInteger(lineInColumn)) {
							cerr << "Error in data row " << column->get(0)
									<< ": Column " << intValues[i] + 1
									<< " is not a whole number." << endl;
							error = true;
						}
					}
				} else {
					if (!isInteger(lineInColumn)) {
						cerr << "Error in data row " << column->get(0)
								<< ": Column " << intValues[i] + 1
								<< " is not a whole number." << endl;
						error = true;
					}
				}
			}

			//Check for double values in certain columns
			for (int i = 0; i < doubleNum; ++i) {
				lineInColumn = column->get(doubleValues[i]);
				if (!isDouble(lineInColumn)) {
					cerr << "Error in data row " << column->get(0)
							<< ": Column " << doubleValues[i] + 1
							<< " is not a decimal number." << endl;
					error = true;
				}
			}
		}

		//Check for unique catalog numbers in each data line
		if (!error) {
			if (catalogNumArray->length() != 0) {
				for (int i = 0; i < catalogNumArray->length(); ++i) {
					if (column->get(0) == catalogNumArray->get(i)) {
						cerr << "Error in data row " << column->get(0)
								<< ": Duplicate catalog number "
								<< column->get(0) << "." << endl;
						error = true;
					}
				}
			}
			if (!error) {
				catalogNumArray->add(column->get(0));
			}
		}
		if (error) {
			data->remove(count);
			count--;
		}
		error = false;

		//Delete Column ArrayList
		column->~ArrayList();
	}

	//Print output to Output File
	cout << data;

	//Delete ArrayLists to be tidy
	data->~ArrayList();
	catalogNumArray->~ArrayList();

	//Exit program cleanly
	return 0;
}
