/*
 * EclipseR2.cpp Code that reads through a column spaced file
 * and creates a comma delimitted file with error checks.
 *
 *  Created on: Sep 12, 2017
 *      Author: Clayton Glenn
 */
#include <iostream>
#include <string>
#include "EclipseR2.h"

using namespace std;

/**
 * The main class reads data from a file and manipulates
 * and outputs necessary information, while showing errors
 * for incorrect information in the file
 */
int main() {

	//Create a dynamic data array to store each line from the file
	std::string *data = NULL;
	int dataSize = 10;
	data = new string[dataSize];
	for (int i = 0; i < dataSize; ++i) {
		data[i] = "";
	}

	//Create a dynamic data array to store each column from a line
	//for manipulation and error checking
	std::string *columns = NULL;
	int columnSize = 10;
	columns = new string[columnSize];
	for (int i = 0; i < columnSize; ++i) {
		columns[i] = "";
	}

	//Create a dynamic data array to store each catalog number from each line
	std::string *comparisons = NULL;
	int compareSize = 10;
	comparisons = new string[compareSize];
	for (int i = 0; i < compareSize; ++i) {
		comparisons[i] = "";
	}

	//Create necessary incrementers for each array
	int dataNum = 0;
	int columnNum = 0;
	int compareNum = 0;

	//Skip Header Lines
	for (int i = 0; i < 10 && !cin.eof(); ++i) {
		getline(cin, data[0]);
	}

	//Read data from file into an array
	for (; !cin.eof(); ++dataNum) {

		//If more space needed in array, make the space
		if (dataNum == (dataSize - 1)) {
			data = doubleSize(data, dataSize);
		}

		//Get line from file
		getline(cin, data[dataNum]);

		//Format data file line into pseudo-Comma Delimited Lines
		for (unsigned int j = 0; j < data[dataNum].length(); ++j) {
			if (isspace(data[dataNum].at(j))) {
				if (j != 0) {
					if (isalpha(data[dataNum].at(j - 1))
							|| isdigit(data[dataNum].at(j - 1))
							|| data[dataNum][j - 1] == '-') {
						data[dataNum].replace(j, 1, ",");
					} else {
						data[dataNum].erase(j, 1);
						j--;
					}
				} else {
					data[dataNum].erase(j, 1);
					j--;
				}
			}
		}
	}
	//Done with standard input from cin

	//Break the data into columns, line by line
	for (int i = 0; i < dataNum; ++i) {
		for (unsigned int j = 0; j < data[i].length(); ++j) {
			if (data[i].at(j) == ',') {

				//Only increment columnNum if comma is found
				columnNum++;

				//Make more columns if needed
				if (columnNum == columnSize - 1) {
					columns = doubleSize(columns, columnSize);
				}

			} else {

				//Push characters back to create strings of data
				columns[columnNum].push_back(data[i].at(j));
			}
		}

		//Delete the data line for new input into the string
		data[i] = "";

		//Find first character of column 9 for 'P' check
		string character = columns[9].substr(0, 1);

		if ((character == "P") && columnNum != 16) {

			//If eclipse is partial and columns aren't right, send error to user
			cerr << "Error in data row " << i + 1 << ": " << columnNum + 1
					<< " columns found. Should be 16." << endl;

		} else if ((character != "P") && columnNum != 17) {

			//If eclipse isnt partial and columns aren't right, send error to user
			cerr << "Error in data row " << i + 1 << ": " << columnNum + 1
					<< " columns found. Should be 18." << endl;
		} else {

			//If data passes column check, then data will undergo integer check
			//Create column check arrays and a flag for next error checks
			bool invalid = false;
			int intChecks[] = { 0, 1, 2, 4, 6, 7, 8, 14, 15, 16 };
			int doubleChecks[] = { 10, 11 };

			for (int c = 0; c < 10; ++c) {
				if (c != 9) {
					if (!isInteger(columns[intChecks[c]])) {

						//If certain column isnt integer, send error to user
						cerr << "Error in data row " << i + 1 << ": Column "
								<< intChecks[c] + 1 << " is not a whole number."
								<< endl;
						invalid = true;
						break;
					} else {
						if ((character == "P")) {
							if (!isInteger(columns[intChecks[c]])) {

								//If certain column isnt integer, send error to user
								cerr << "Error in data row " << i + 1
										<< ": Column " << intChecks[c] + 1
										<< " is not a whole number." << endl;
								invalid = true;
								break;
							}
						}
					}
				} else {
					if (!invalid) {
						if ((character != "P")) {

							//If certain column isnt integer, send error to user
							if (!isInteger(columns[intChecks[c]])) {
								cerr << "Error in data row " << i + 1
										<< ": Column " << intChecks[c] + 1
										<< " is not a whole number." << endl;
								invalid = true;
								break;
							}
						}
					}
				}
			}
			if (!invalid) {

				//If data passes integer check
				for (int c = 0; c < 2; ++c) {
					if (!isDouble(columns[doubleChecks[c]])) {

						//If certain column isnt double, send error to user
						cerr << "Error in data row " << i + 1 << ": Column "
								<< doubleChecks[c] + 1
								<< " is not a decimal number." << endl;
						invalid = true;
					}
				}
			}
			if (!invalid) {

				//If double checks pass, check for comparisons
				if (compareNum == compareSize - 1) {

					//If comparisons needs more space, make more elements in array
					comparisons = doubleSize(comparisons, compareSize);
				}
				for (int c = 0; c < compareNum; ++c) {
					if (columns[0] == comparisons[c]) {

						//If catalog number is duplicate, send error
						cerr << "Error in data row " << i + 1
								<< ": Duplicate catalog number "
								<< comparisons[c] << "." << endl;
						invalid = true;
					}
				}

				//Add catalog number to comparisons and increment the elements
				comparisons[compareNum] = columns[0];
				compareNum++;
			}
			if (!invalid) {

				//If all checks pass, create comma delimited line for output
				for (int j = 0; j <= columnNum; ++j) {
					if (columns[j + 1] != "") {
						data[i] += columns[j] + ",";
						columns[j] = "";
					} else {
						data[i] += (columns[j]);
						columns[j] = "";
					}
				}
			}
		}

		//eliminate all information in heap of columns array
		for (int j = 0; j < columnSize; ++j) {
			columns[j] = "";
		}

		//Reset elements to zero
		columnNum = 0;
	}

	//Print all viable data to user
	for (int i = dataNum - 1; i >= 0; --i) {
		if (data[i] != "") {
			cout << data[i] << endl;
		}
	}

	//End program with zero code
	return 0;
}
