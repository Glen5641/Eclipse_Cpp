/*
 * EclipseR.cpp
 *
 * This Program reads data from an eclipse data file and creates
 * Eclipse Objects. It also checks for errors in the eclipse input.
 * The program stores all eclipse objects in a doubly linked list.
 * The program in turn, after getting data, manipulates the data
 * by sorting or searching through it. Searching and sorting is
 * only attempted by converting the eclipses list into a resizable array.
 *
 *  Created on: Sep 25, 2017
 *      Author: cglen
 */


#include <fstream>

#include "EclipseR2.h"
#include "Eclipse.h"
#include "DoublyLinkedList.h"
#include "ResizableArray.h"
#include "HelperFunctions.h"
#include "Sort.h"
#include "Search.h"

using namespace std;

int main() {

	//Create ResizableArrays for storing eclipses and catalog numbers
	ResizableArray<int>* catalogNums = new ResizableArray<int>();
	DoublyLinkedList<Eclipse*>* eclipses = new DoublyLinkedList<Eclipse*>();
	bool isEmpty = true;

	//Create an Eclipse to object each line of data.
	Eclipse* eclipse;

	//Create strings for data lines, error lines, and user input
	string line, eline, input = "input";

	//Create booleans for catalog matches and blank checking
	bool match = false, isBlank = true;

	//Create incrementers to count valid lines,
	//data lines from each file, and total line count
	int validCount = 0, dataCount = 0, totalCount = 0;

	//Greet User
	cout << "Welcome to Chase Glenn's Eclipse DataBase." << endl;

	//Create user generated file to read data lines into eclipse objects
	ifstream inF;

	//Check if file is valid, if not, prompt user for new file
	while (!inF.is_open() && !input.empty()) {
		cout << "Please enter a valid input file or "
				<< "leave answer blank to continue." << endl;
		getline(cin, input);
		inF.open(input);
		if (!inF.is_open() && input != "") {
			cout << "File Not Available." << endl;
		}
	}

	//Skip header rows of the data file
	for (int i = 0; i < 10 && !inF.eof(); ++i) {
		getline(inF, line);
	}

	//Loop while in file and eof flag not introduced
	while (!inF.eof()) {

		//Get next data line for reading
		getline(inF, line);

		//Check if line is blank but contains whitespace, if so,
		//skip data retrieval
		for (unsigned int i = 0; i < line.length(); ++i) {
			if (!isspace(line[i])) {
				isBlank = false;
				break;
			}
		}

		//If line is populated, start creating eclipses
		if (line != "" && !isBlank) {

			//Create new Eclipse object with data line and line count
			eclipse = new Eclipse(line, validCount);

			//If eclipse doesnt have generated error, go ahead and check
			//for Catalog number duplicates
			if (!eclipse->hasErr()) {

				//Increment the valid count since this eclipse is good
				validCount++;

				//Check for duplicates through catalog number array
				for (int i = 0; i < catalogNums->getSize(); ++i) {

					//If cat nums match, generate error in eclipse and
					//break from loop
					if (eclipse->getCatNum() == catalogNums->at(i)) {
						eline = "Error in data row ";
						eline += to_string(validCount);
						eline += ": Duplicate Catalog Number ";
						eline += to_string(catalogNums->at(i));
						eclipse->setErr(eline);
						match = true;
						break;
					}
				}
			}

			//If eclipse still doesnt have error, add it to the array for
			//manipulation and add catalog number of eclipse to array of
			//cat nums
			if (!eclipse->hasErr()) {
				catalogNums->add(eclipse->getCatNum());

				if (isEmpty) {
					eclipses->create_list(eclipse);
					isEmpty = false;
				} else {
					eclipses->add_end(eclipse);
				}

			} else {				//If error decribe the error
				cerr << eclipse->what() << endl;
				if (match) {

					//If match exists, replace the old duplicate with
					//the new Eclipse
					eclipse->setErr("");
					int index = searchCats(eclipse, eclipses);
					if (index >= 0) {
						eclipses->replace_at(eclipse, index);
					}
					match = false;
				}
			}
		}
		//Increment the data count for each data line in the file
		dataCount++;
	}

	//If data count is zero, this means there is nothing in the file,
	//exit Eclipse.
	if (dataCount == 0) {
		cout << "Blank file chosen, Thanks for using Eclipses.";
		return 0;
	}

	//Assign totalcount with datacounts of each file to
	//show all data read and initialize data count as zero.
	totalCount += dataCount;
	dataCount = 0;

	//Close the data file that is being read from
	inF.close();

	//Data Manipulation Loop

	//Create additional input line for user input
	string inputLine;

	//Create character array to check for Integers or Floats
	char* p;

	//Create float and two integers, float and one integer for searching,
	//and one int for user input
	float b = 0.0;
	int a = 0, inputInt = 0;

	//Create out file to stream output
	ofstream outF;

	//Loop while user wants to continue
	while (input != "Q" && input != "q") {

		//Create new array for storing manipulations without destroying integrity
		//of the main array
		ResizableArray<Eclipse*>* list = new ResizableArray<Eclipse*>();

		//Ask for user to pick output, sort, find, or quit
		cout
				<< "'C' for Catalog Number Output, 'M' for merge, 'P' for purge, �O� for output, �S� for sort, �F� for find, and �Q� for quit."
				<< endl;

		//Clear cin buffer for collection reasons and get users line
		cin.clear();
		getline(cin, input);

		if (input == "C" || input == "c") {
			printHeader(cout);
			cout << eclipses << endl;
		} else if (input == "P" || input == "p") {

			if (eclipses->count() == 0) {
				cout << "List is empty, please merge a list." << endl;
			} else {

				//Check if file is valid, if not, prompt user for new file
				while (!inF.is_open() && !input.empty()) {
					cout << "Please enter a valid input file or "
							<< "leave answer blank to continue." << endl;
					getline(cin, input);
					inF.open(input);
					if (!inF.is_open() && input != "") {
						cout << "File Not Available." << endl;
					}
				}

				//Skip header rows of the data file
				for (int i = 0; i < 10 && !inF.eof(); ++i) {
					getline(inF, line);
				}

				//Loop while in file and eof flag not introduced
				while (!inF.eof()) {

					//Get next data line for reading
					getline(inF, line);

					//Check if line is blank but contains whitespace, if so,
					//skip data retrieval
					for (unsigned int i = 0; i < line.length(); ++i) {
						if (!isspace(line[i])) {
							isBlank = false;
							break;
						}
					}

					//If line is populated, start creating eclipses
					if (line != "" && !isBlank) {

						//Create new Eclipse object with data line and line count
						eclipse = new Eclipse(line, validCount);

						//If eclipse doesnt have generated error, go ahead and check
						//for Catalog number duplicates
						if (!eclipse->hasErr()) {
							match = false;
							//Check for duplicates through catalog number array
							for (int i = 0; i < catalogNums->getSize(); ++i) {

								//If cat nums match, generate error in eclipse and
								//break from loop
								if (eclipse->getCatNum()
										== catalogNums->at(i)) {
									//Search for eclipse and delete
									if (eclipses->count() == 1) {
										eclipses =
												new DoublyLinkedList<Eclipse*>();
									} else {
										int index = searchCats(eclipse,
												eclipses);
										if (index != -1) {
											eclipses->delete_element(index);
										}
									}
									catalogNums->removeAt(i);
									i--;
									dataCount--;
									match = true;
								}
							}
							if (!match) {
								cerr << "Catalog Number not found." << endl;
							}
						}
					}
				}
				inF.close();
			}
		} else if (input == "M" || input == "m") {

			//Check if file is valid, if not, prompt user for new file
			while (!inF.is_open() && !input.empty()) {
				cout << "Please enter a valid input file or "
						<< "leave answer blank to continue." << endl;
				getline(cin, input);
				inF.open(input);
				if (!inF.is_open() && input != "") {
					cout << "File Not Available." << endl;
				}
			}

			//Skip header rows of the data file
			for (int i = 0; i < 10 && !inF.eof(); ++i) {
				getline(inF, line);
			}

			//Loop while in file and eof flag not introduced
			while (!inF.eof()) {

				//Get next data line for reading
				getline(inF, line);

				//Check if line is blank but contains whitespace, if so,
				//skip data retrieval
				for (unsigned int i = 0; i < line.length(); ++i) {
					if (!isspace(line[i])) {
						isBlank = false;
						break;
					}
				}

				//If line is populated, start creating eclipses
				if (line != "" && !isBlank) {

					//Create new Eclipse object with data line and line count
					eclipse = new Eclipse(line, validCount);

					//If eclipse doesnt have generated error, go ahead and check
					//for Catalog number duplicates
					if (!eclipse->hasErr()) {

						//Increment the valid count since this eclipse is good
						validCount++;

						//Check for duplicates through catalog number array
						for (int i = 0; i < catalogNums->getSize(); ++i) {

							//If cat nums match, generate error in eclipse and
							//break from loop
							if (eclipse->getCatNum() == catalogNums->at(i)) {
								eline = "Error in data row ";
								eline += to_string(validCount);
								eline += ": Duplicate Catalog Number ";
								eline += to_string(catalogNums->at(i));
								eclipse->setErr(eline);
								match = true;
								break;
							}
						}
					}

					//If eclipse still doesnt have error, add it to the array for
					//manipulation and add catalog number of eclipse to array of
					//cat nums
					if (!eclipse->hasErr()) {
						catalogNums->add(eclipse->getCatNum());

						if (eclipses->count() == 0) {
							eclipses->create_list(eclipse);
							isEmpty = false;
						} else {
							eclipses->add_end(eclipse);
						}

					} else {				//If error decribe the error
						cerr << eclipse->what() << endl;
						if (match) {

							//If match exists, replace the old duplicate with
							//the new Eclipse
							eclipse->setErr("");
							int index = searchCats(eclipse, eclipses);
							if (index >= 0) {
								eclipses->replace_at(eclipse, index);
							}
							match = false;
						}
					}
				}
				//Increment the data count for each data line in the file
				dataCount++;
			}

			//If data count is zero, this means there is nothing in the file,
			//exit Eclipse.
			if (dataCount == 0) {
				cout << "Blank file chosen, Thanks for using Eclipses.";
				return 0;
			}

			//Assign totalcount with datacounts of each file to
			//show all data read and initialize data count as zero.
			totalCount += dataCount;
			dataCount = 0;

			//Close the data file that is being read from
			inF.close();
			//Check if user input is o or O for output.
		} else if (input == "O" || input == "o") {

			if (eclipses->count() == 0) {
				cout << "List is empty, please merge a list." << endl;
			} else {

				//Ask user for input regarding outfile name.
				cout << "Input a data file name for output"
						<< " or press enter to print to console." << endl;

				//Clear buffer and get user input
				cin.clear();
				getline(cin, inputLine);

				//Open Data file for user
				outF.open(inputLine);

				//If name is not found, inform user and return to start of loop.
				if (!outF.is_open() && inputLine != "") {
					cout << "File Not Available." << endl;

					//If user input is empty, Print data out to user via console
				} else if (inputLine.empty()) {
					printHeader(cout);
					cout << eclipses << endl;
					cout << "Data lines read: " << to_string(totalCount)
							<< "; Valid eclipses read: "
							<< to_string(validCount) << "; Eclipses in memory: "
							<< to_string(eclipses->count()) << endl << endl;

					//Else, print output data to user specified file
				} else {
					printHeader(outF);
					outF << eclipses << endl;
					outF << "Data lines read: " << to_string(totalCount)
							<< "; Valid eclipses read: "
							<< to_string(validCount) << "; Eclipses in memory: "
							<< to_string(eclipses->count()) << endl << endl;

					//Close output file
					outF.close();
				}

				//Check if user input is s or S for Sorting.
			}
		} else if (input == "S" || input == "s") {

			if (eclipses->count() == 0) {
				cout << "List is empty, please merge a list." << endl;
			} else {

				for (int i = 1; i <= eclipses->count(); ++i) {
					list->add(eclipses->peek(i));
				}

				//Prompt user to sorting column
				cout << "Input which column you want to sort by." << endl;

				//Clear buffer and read line from user
				cin.clear();
				getline(cin, inputLine);

				//If input is integer convert to integer
				if (isInteger(inputLine)) {
					inputInt = strtol(inputLine.c_str(), &p, 10);

					//Make rest of loop unreachable
				} else {
					inputInt = 0;
				}

				//Check for number between 1 and 18 inclusively
				if (0 < inputInt && inputInt <= 18) {

					//Sort the eclipses by user specifications
					quickSort(list, 0, list->getSize() - 1, inputInt);
					eclipses->~DoublyLinkedList();
					eclipses = new DoublyLinkedList<Eclipse*>();
					eclipses->create_list(list->at(0));
					for (int i = 1; i < list->getSize(); ++i) {
						eclipses->add_end(list->at(i));
					}
				}
				list->~ResizableArray();

				//Check if user input is f or F for Find.
			}
		} else if (input == "F" || input == "f") {

			list = new ResizableArray<Eclipse*>();
			if (eclipses->count() == 0) {
				cout << "List is empty, please merge a list." << endl;
			} else {

				//Prompt user for column to search in
				cout << "Input which column you want to search in." << endl;

				for (int i = 1; i <= eclipses->count(); ++i) {
					list->add(eclipses->peek(i));
				}

				//Clear buffer and get user input
				cin.clear();
				getline(cin, inputLine);

				//Check for integer, if so, convert to integer, if not, make data
				//unreachable
				if (isInteger(inputLine)) {
					inputInt = strtol(inputLine.c_str(), &p, 10);
				} else {
					inputInt = 0;
				}

				//Check if int is between 1 and 18 inclusively
				if (0 < inputInt && inputInt <= 18) {

					//Prompt user for item to search for
					cout << "Input what you want to search for." << endl;

					//Clear buffer and get user input
					cin.clear();
					getline(cin, inputLine);

					//If input is a double and integer is 11 or 12, seach for
					//double in eclipses
					if (isDouble(inputLine)
							&& (inputInt == 11 || inputInt == 12)) {
						b = strtod(inputLine.c_str(), &p);
						list = search(inputInt, list, 0, b, "");

						//If input is an integer and column is 1, 2, 3, 5, 7, 8,
						//9, 15, 16, or 17, search for integer in eclipses
					} else if (isInteger(inputLine)
							&& (inputInt == 1 || inputInt == 2 || inputInt == 3
									|| inputInt == 5 || inputInt == 7
									|| inputInt == 8 || inputInt == 9
									|| inputInt == 15 || inputInt == 16
									|| inputInt == 17)) {
						a = strtol(inputLine.c_str(), &p, 10);
						list = search(inputInt, list, a, 0.0, "");

						//If column is 4, use month enum to search for certain
						//month. If month is out of bounds, skip search
					} else if (inputInt == 4) {
						a = strom(inputLine);
						if (a > 0) {
							list = search(inputInt, list, a, 0.0, "");
						}

						//Else, search for a string in the remaining columns
					} else if (inputInt == 6 || inputInt == 10 || inputInt == 13
							|| inputInt == 14 || inputInt == 18) {
						list = search(inputInt, list, 0, 0.0, inputLine);
					} else {
						continue;
					}

					//Output the search conclusions to the console for user to see
					cout << list << endl;
					list->~ResizableArray();
				}

				//Check is user input is Q or q, If so break loop and quit.
			}
		} else if (input == "Q" || input == "q") {
			cout << "Thanks for using eclipse." << endl;
			break;

			//If input doesnt make, character is invalid.
		} else {
			cout << "Invalid Character, Please Try again.";
		}
	}
}
