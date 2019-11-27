/*
 * EclipseR.cpp
 *
 * This Program reads data from an eclipse data file and creates
 * Eclipse Objects. It also checks for errors in the eclipse input.
 * The program stores all eclipse objects in a doubly linked list,
 * resizable array, and a hashmap. The program in turn, after getting
 * data, manipulates the data by sorting or searching, merging or
 * purging, and outputing. Searching and sorting is only attempted
 * by converting the eclipses list into a resizable array.
 *
 *  Created on: Nov 15, 2017
 *      Author: cglen
 */

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "DoublyLinkedList.h"
#include "Eclipse.h"
#include "LinkedHashMap.h"
#include "HelperFunctions.h"
#include "ResizableArray.h"
#include "Sort.h"
#include "Search.h"

using namespace std;

int main() {

	ResizableArray<int>* catalogNums = new ResizableArray<int>();
	DoublyLinkedList<Eclipse*>* eclipses = new DoublyLinkedList<Eclipse*>();
	ResizableArray<Eclipse*>* list = new ResizableArray<Eclipse*>();
	bool match = false, isBlank = true;
	Eclipse* eclipse;
	string line, eline, input = "input";
	int validCount = 0, dataCount = 0, totalCount = 0;
	ifstream inF;
	ofstream cerrFile;
	cerrFile.open("cerr.txt");

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Data Collection Loop
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Greet User to the Database
	cout << "Welcome to Chase Glenn's Eclipse DataBase." << endl;

	//Ask for an Eclipse File and check if file is valid.
	//If not, prompt user for new file
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

	//Loop while in file
	while (!inF.eof()) {

		//Get next data line for reading and Check if line is blank
		//but contains whitespace. if so, skip data retrieval
		getline(inF, line);
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
				validCount++;

				//Check for duplicates through catalog number array
				//If cat nums match, generate error in eclipse and
				//break from loop
				for (int i = 0; i < catalogNums->getSize(); ++i) {
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
				} else {
					eclipses->add_end(eclipse);
				}

			} else {				//If error decribe the error
				cerrFile << eclipse->what() << endl;
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

	//If data count is zero, this means a blank file is chosen.
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

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Data Manipulation Loop
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	string inputLine;
	char* p;
	float b = 0.0;
	int a = 0, inputInt = 0;
	ofstream outF;

	list = eclipses->getList();
	quickSort(list, 0, list->getSize() - 1, 1);
	eclipses = new DoublyLinkedList<Eclipse*>();
	eclipses->create_list(list->at(0));
	for (int i = 1; i < list->getSize(); ++i) {
		eclipses->add_end(list->at(i));
	}

	LinkedHashMap *lhm = new LinkedHashMap(eclipses);

	//Loop while user wants to continue
	while (input != "Q" && input != "q") {

		//Create new array for storing manipulations without destroying integrity
		//of the main array
		list->~ResizableArray();
		list = new ResizableArray<Eclipse*>();

		//Ask for user to pick C, O, L, H, or Q
		cout << "'C' for Merging or Purging the list, ‘O’ for Output, "
				<< "'L' for List Output, ‘H’ for Hash Output, and ‘Q’ for quit."
				<< endl;

		//Clear cin buffer for collection reasons and get users line
		cin.sync();
		getline(cin, input);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//COLLECTION
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (input == "C" || input == "c") {

			cout << "'M' for Merge, 'P' for Purge" << endl;
			cin.sync();
			getline(cin, input);
			while (input != "P" && input != "p" && input != "m" && input != "M") {

				cout << "Invalid Character, please enter another Character."
						<< endl;
				cin.sync();
				getline(cin, input);
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//PURGE
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (input == "P" || input == "p") {
				if (eclipses->count() == 0) {
					cout << "List is empty, please merge a list." << endl;
				} else {

					//Check if file is valid, if not, prompt user for new file
					while (!inF.is_open() && !input.empty()) {
						cout << "Please enter a valid input file or "
								<< "leave answer blank to continue." << endl;
						cin.sync();
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
								for (int i = 0; i < catalogNums->getSize();
										++i) {

									//If cat nums match, generate error in eclipse and
									//break from loop
									if (eclipse->getCatNum()
											== catalogNums->at(i)) {
										//Search for eclipse and delete
										if (eclipses->count() == 1) {
											eclipses = new DoublyLinkedList<
													Eclipse*>();
										} else {
											int index = searchCats(eclipse,
													eclipses);
											if (index != -1) {
												lhm->remove(
														eclipse->getCatNum());
											}
										}
										catalogNums->removeAt(i);
										i--;
										dataCount--;
										match = true;
									}
								}
								if (!match) {
									cerrFile << "Catalog Number not found."
											<< endl;
								}
							}
						}
					}
					inF.close();
					if (catalogNums->getSize() == 0) {
						list->~ResizableArray();
						list = new ResizableArray<Eclipse*>();
						eclipses->~DoublyLinkedList();
						eclipses = new DoublyLinkedList<Eclipse*>();
						catalogNums->~ResizableArray();
						catalogNums = new ResizableArray<int>();
					}
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//MERGE
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			} else {

				list = eclipses->getList();
				//Check if file is valid, if not, prompt user for new file
				while (!inF.is_open() && !input.empty()) {
					cout << "Please enter a valid input file or "
							<< "leave answer blank to continue." << endl;
					cin.sync();
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
								if (eclipse->getCatNum()
										== catalogNums->at(i)) {
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
							list->add(eclipse);

						} else {				//If error decribe the error
							cerrFile << eclipse->what() << endl;
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

				lhm->~LinkedHashMap();
				lhm = new LinkedHashMap(eclipses);

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

				quickSort(list, 0, list->getSize() - 1, 1);
				eclipses = new DoublyLinkedList<Eclipse*>();
				eclipses->create_list(list->at(0));
				for (int i = 1; i < list->getSize(); ++i) {
					eclipses->add_end(list->at(i));
				}
				lhm->~LinkedHashMap();
				lhm = new LinkedHashMap(eclipses);
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//OUTPUT
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		} else if (input == "O" || input == "o") {
			if (eclipses->count() == 0) {
				cout << "List is empty, please merge a list." << endl;
			} else {

				cout << "'S' for Sorted Output, 'F' to Find an Eclipse" << endl;
				cin.sync();
				getline(cin, input);
				while (input != "S" && input != "s" && input != "F"
						&& input != "f") {
					cout << "Invalid Character, please enter another Character."
							<< endl;
					cin.sync();
					getline(cin, input);
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//SORTED OUTPUT
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				if (input == "S" || input == "s") {
					for (int i = 1; i <= eclipses->count(); ++i) {
						list->add(eclipses->peek(i));
					}

					//Prompt user to sorting column
					cout << "Input which column you want to sort by." << endl;

					//Clear buffer and read line from user
					cin.sync();
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
						//Ask user for input regarding outfile name.
						cout << "Input a data file name for output"
								<< " or press enter to print to console."
								<< endl;

						//Clear buffer and get user input
						cin.sync();
						getline(cin, inputLine);

						//Open Data file for user
						outF.open(inputLine);

						//If name is not found, inform user and return to start of loop.
						if (!outF.is_open() && inputLine != "") {
							cout << "File Not Available." << endl;

							//If user input is empty, Print data out to user via console
						} else if (inputLine.empty()) {
							printHeader(cout);
							cout << list << endl;
							cout << "Data lines read: " << to_string(totalCount)
									<< "; Valid eclipses read: "
									<< to_string(validCount)
									<< "; Eclipses in memory: "
									<< to_string(eclipses->count()) << endl
									<< endl;

							//Else, print output data to user specified file
						} else {
							printHeader(outF);
							outF << list << endl;
							outF << "Data lines read: " << to_string(totalCount)
									<< "; Valid eclipses read: "
									<< to_string(validCount)
									<< "; Eclipses in memory: "
									<< to_string(eclipses->count()) << endl
									<< endl;

							//Close output file
							outF.close();
						}
					}
					list->~ResizableArray();

					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//FIND OUTPUT
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				} else {
					list = new ResizableArray<Eclipse*>();
					if (eclipses->count() == 0) {
						cout << "List is empty, please merge a list." << endl;
					} else {

						//Prompt user for column to search in
						cout << "Input which column you want to search in."
								<< endl;

						for (int i = 1; i <= eclipses->count(); ++i) {
							list->add(eclipses->peek(i));
						}

						//Clear buffer and get user input
						cin.sync();
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
							cout << "Input what you want to search for."
									<< endl;

							//Clear buffer and get user input
							cin.sync();
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
									&& (inputInt == 1 || inputInt == 2
											|| inputInt == 3 || inputInt == 5
											|| inputInt == 7 || inputInt == 8
											|| inputInt == 9 || inputInt == 15
											|| inputInt == 16 || inputInt == 17)) {
								a = strtol(inputLine.c_str(), &p, 10);
								if (inputInt == 1) {
									list = new ResizableArray<Eclipse*>();
									eclipse = lhm->get(a);
									list->add(eclipse);
								} else {
									list = search(inputInt, list, a, 0.0, "");
								}
								//If column is 4, use month enum to search for certain
								//month. If month is out of bounds, skip search
							} else if (inputInt == 4) {
								a = strom(inputLine);
								if (a > 0) {
									list = search(inputInt, list, a, 0.0, "");
								}

								//Else, search for a string in the remaining columns
							} else if (inputInt == 6 || inputInt == 10
									|| inputInt == 13 || inputInt == 14
									|| inputInt == 18) {
								list = search(inputInt, list, 0, 0.0,
										inputLine);
							} else {
								continue;
							}

							//Output the search conclusions to the console for user to see
							int i = 0;
							Eclipse *e = new Eclipse("", i);
							if (list->getSize() == 1
									&& list->at(0)->getCatNum()
											== e->getCatNum()) {
							} else {
								printHeader(cout);
								cout << list << endl;
								cout << "Data lines read: "
										<< to_string(totalCount)
										<< "; Valid eclipses read: "
										<< to_string(validCount)
										<< "; Eclipses in memory: "
										<< to_string(eclipses->count()) << endl
										<< endl;
							}

							//Delete resizableArray
							list->~ResizableArray();
						}
					}
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//LINKED LIST OUTPUT
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		else if (input == "L" || input == "l") {
			if (eclipses->count() == 0) {
				cout << "List is empty, please merge a list." << endl;
			} else {

				//Ask user for input regarding outfile name.
				cout << "Input a data file name for output"
						<< " or press enter to print to console." << endl;

				//Clear buffer and get user input
				cin.sync();
				getline(cin, inputLine);

				//Open Data file for user
				outF.open(inputLine);

				//If name is not found, inform user and return to start of loop.
				if (!outF.is_open() && inputLine != "") {
					cout << "File Not Available." << endl;

					//If user input is empty, Print data out to user via console
				} else if (inputLine.empty()) {
					printHeader(cout);
					lhm->printList(cout);
					cout << "Data lines read: " << to_string(totalCount)
							<< "; Valid eclipses read: "
							<< to_string(validCount) << "; Eclipses in memory: "
							<< to_string(eclipses->count()) << endl << endl;

				} else {		//Else, print to outfile
					printHeader(outF);
					lhm->printList(outF);
					outF << "Data lines read: " << to_string(totalCount)
							<< "; Valid eclipses read: "
							<< to_string(validCount) << "; Eclipses in memory: "
							<< to_string(eclipses->count()) << endl << endl;
				}

				//Close outfile
				outF.close();
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//HASH MAP OUTPUT
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		} else if (input == "H" || input == "h") {

			//Blank List Check
			if (eclipses->count() == 0) {
				cout << "List is empty, please merge a list." << endl;
			} else {

				//Ask user for input regarding outfile name.
				cout << "Input a data file name for output"
						<< " or press enter to print to console." << endl;

				//Clear buffer and get user input
				cin.sync();
				getline(cin, inputLine);

				//Open Data file for user
				outF.open(inputLine);

				//If name is not found, inform user and return to start of loop.
				if (!outF.is_open() && inputLine != "") {
					cout << "File Not Available." << endl;

					//If user input is empty, Print data out to user via console
				} else if (inputLine.empty()) {
					printHeader(cout);
					lhm->printMap(cout);
					cout << "Data lines read: " << to_string(totalCount)
							<< "; Valid eclipses read: "
							<< to_string(validCount) << "; Eclipses in memory: "
							<< to_string(eclipses->count()) << endl << endl;

				} else {			//Else Print to certain file
					printHeader(outF);
					lhm->printMap(outF);
					outF << "Data lines read: " << to_string(totalCount)
							<< "; Valid eclipses read: "
							<< to_string(validCount) << "; Eclipses in memory: "
							<< to_string(eclipses->count()) << endl << endl;
				}

				//Close Output file
				outF.close();
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//QUIT
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		} else if (input == "Q" || input == "q") {
			cout << "Thanks for using eclipse." << endl;
			break;

			//If input doesnt make, character is invalid.
		} else {
			cout << "Invalid Character, Please Try again.";
		}
	}

	//Close CERR File
	cerrFile.close();
}

