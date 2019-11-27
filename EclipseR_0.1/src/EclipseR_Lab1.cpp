//============================================================================
// Name        : EclipseData.cpp
// Author      : Clayton Glenn
// Date		   : 8/31/2017
// Teacher     : Dean Hougen
// Version     : Lab 1
// Description : Data file manipulator from spaced file to comma-delimited
//============================================================================

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

/*
 * This main method reads data from a file and manipulates
 * it into comma delimited data, all while checking for bad
 * data and duplicates.
 *
 * Contributor: Simon Boerwinkle
 * General understanding of reading in files with cin.
 */
int main() {

	//Create line for reading in strings of code
	std::string line = "";

	//Skip first ten lines of headers
	for (int i = 0; i < 10 && cin.good(); ++i) {
		getline(cin, line);
	}

	/*Create columns for storing variables, compare for comparing
	 catalog numbers, match for checking catalogs, and lineNum
	 catalog catalog for counting lines of printout*/
	std::string column[24];
	std::string compare[12000];
	for (int i = 0; i < 12000; i++) {
		compare[i] = "";
	}

	bool match = false;
	int lineNum = 1;

	//While the file lines are good, read through each line
	//Made possible through Sim Boerwinkle
	while (std::cin.good()) {

		//Assign all columns in array to blank string
		for (int i = 0; i < 24; ++i) {
			column[i] = "";
		}

		//Get line from file
		getline(std::cin, line);

		//Format data file line into pseudo-Comma Delimited Lines
		for (unsigned int i = 0; i < line.length(); ++i) {
			if (isspace(line.at(i))) {
				if (i != 0) {
					if ((isalpha(line.at(i - 1)) || isdigit(line.at(i - 1))
							|| line[i - 1] == '-')) {
						line.replace(i, 1, ",");
					} else {
						line.erase(i, 1);
						i--;
					}
				} else {
					line.erase(i, 1);
					i--;
				}
			}
		}

		//Assign each data in a different string variable in an array
		int varNum = 0;
		for (unsigned int i = 0; i < line.length(); ++i) {
			if (line.at(i) == ',') {
				varNum++;
			} else {
				column[varNum].push_back(line.at(i));
			}
		}
		varNum = 0;

		//If catalog is duplicate make match true for error report
		for (int i = 0; i < 12000; ++i) {
			if (compare[i] == column[0]) {
				match = true;
			}
		}

		//ERROR FUNCTION and Output to file
		if (column[9] == "P" && column[16] != "") { //Error data contains P and too long
			cerr << "Invalid Data input at line: " << lineNum << endl;
			lineNum++;
		} else if (match) { //Error catalog number duplicate of previous
			cerr << "Duplicate Data input at line: " << lineNum << endl;
			lineNum++;
		} else { //If good data, print out
			for (int j = 0; j < 24; ++j) {
				if (j != 0 && column[j] != "") {
					cout << "," << column[j];
				}
				if (j == 0) {
					cout << column[j];
				}
				column[j] = "";
			}
			cout << endl;
			lineNum++;
		}

		//Assign line's catalog number to compare
		compare[lineNum] = column[0];
		match = false;
	}

	//Exit program by 0 code
	return 0;
}
