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
#include "AVLTree.h"
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
	AVLTree<Eclipse*>* tree = new AVLTree<Eclipse*>();
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
				tree->insert(eclipse, cerrFile);

			} else {				//If error decribe the error
				cerrFile << eclipse->what() << endl;
				if (match) {

					//If match exists, replace the old duplicate with
					//the new Eclipse
					eclipse->setErr("");
					int index = searchCats(eclipse, tree);
					if (index > 0) {
						tree->insert(eclipse, cerrFile);
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

	ResizableArray<Eclipse*>* array;
	LinkedHashMap *map = new LinkedHashMap(tree);

	//Loop while user wants to continue
	while (input != "Q" && input != "q") {

		//Create new array for storing manipulations without destroying integrity
		//of the main array
		array = new ResizableArray<Eclipse*>(tree->getSize());

		//Ask for user to pick C, O, L, H, R, T, or Q
		cout
				<< "'C' for Merging or Purging the list, ‘O’ for Output, 'L' for List Output, ‘H’ for Hash Output, "
				<< endl
				<< "'R' for Pre Order Output, 'T' for Post Order Output, or ‘Q’ for quit."
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
				if (tree->getSize() == 0) {
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
										catalogNums->removeAt(i);
										i--;
										dataCount--;
										match = true;
									}
								}
								if (tree->getSize() != 0) {

									//Delete the eclipse from the tree
									try {
										tree->del(eclipse);
									} catch (out_of_range &except) {
										tree = new AVLTree<Eclipse*>();
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
						catalogNums->~ResizableArray();
						catalogNums = new ResizableArray<int>();
					}
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//MERGE
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			} else {

				array = tree->getArray();
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
							tree->insert(eclipse, cerrFile);

						} else {				//If error decribe the error
							cerrFile << eclipse->what() << endl;
							if (match) {

								//If match exists, replace the old duplicate with
								//the new Eclipse
								eclipse->setErr("");
								int index = searchCats(eclipse, tree);
								if (index >= 0) {
									tree->insert(eclipse, cerrFile);
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
			}

			map = new LinkedHashMap(tree);

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//OUTPUT
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		} else if (input == "O" || input == "o") {
			if (tree->getSize() == 0) {
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
					array = tree->getArray();

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

						if (inputInt != 1) {
							//Sort the eclipses by user specifications
							quickSort(array, 0, array->getSize() - 1, inputInt);
						}
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
							if (inputInt == 1) {
								tree->inorder(cout);
							} else {
								cout << array << endl;
							}
							cout << "Data lines read: " << to_string(totalCount)
									<< "; Valid eclipses read: "
									<< to_string(validCount)
									<< "; Eclipses in memory: "
									<< to_string(catalogNums->getSize()) << endl
									<< endl;

							//Else, print output data to user specified file
						} else {
							printHeader(outF);
							if (inputInt == 1) {
								tree->inorder(outF);
							} else {
								outF << array << endl;
							}
							outF << "Data lines read: " << to_string(totalCount)
									<< "; Valid eclipses read: "
									<< to_string(validCount)
									<< "; Eclipses in memory: "
									<< to_string(catalogNums->getSize()) << endl
									<< endl;

							//Close output file
							outF.close();
						}
					}

					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//FIND OUTPUT
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				} else {
					if (tree->getSize() == 0) {
						cout << "List is empty, please merge a list." << endl;
					} else {

						//Prompt user for column to search in
						cout << "Input which column you want to search in."
								<< endl;

						array = tree->getArray();

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
								array = search(inputInt, array, 0, b, "");

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
									array = new ResizableArray<Eclipse*>();
									eclipse = new Eclipse(a);
									eclipse = tree->find(eclipse);
									array->add(eclipse);
								} else {
									array = search(inputInt, array, a, 0.0, "");
								}
								//If column is 4, use month enum to search for certain
								//month. If month is out of bounds, skip search
							} else if (inputInt == 4) {
								a = strom(inputLine);
								if (a > 0) {
									array = search(inputInt, array, a, 0.0, "");
								}

								//Else, search for a string in the remaining columns
							} else if (inputInt == 6 || inputInt == 10
									|| inputInt == 13 || inputInt == 14
									|| inputInt == 18) {
								array = search(inputInt, array, 0, 0.0,
										inputLine);
							} else {
								continue;
							}

							//Output the search conclusions to the console for user to see
							int i = 0;
							Eclipse *e = new Eclipse("", i);
							if (array->getSize() == 1
									&& array->at(0)->getCatNum()
											== e->getCatNum()) {
							} else {
								printHeader(cout);
								cout << array << endl;
								cout << "Data lines read: "
										<< to_string(totalCount)
										<< "; Valid eclipses read: "
										<< to_string(validCount)
										<< "; Eclipses in memory: "
										<< to_string(catalogNums->getSize())
										<< endl << endl;
							}
						}
					}
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//LINKED LIST OUTPUT
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		else if (input == "L" || input == "l") {
			if (tree->getSize() == 0) {
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
					map->printList(cout);
					cout << "Data lines read: " << to_string(totalCount)
							<< "; Valid eclipses read: "
							<< to_string(validCount) << "; Eclipses in memory: "
							<< to_string(catalogNums->getSize()) << endl
							<< endl;

				} else {		//Else, print to outfile
					printHeader(outF);
					map->printList(outF);
					outF << "Data lines read: " << to_string(totalCount)
							<< "; Valid eclipses read: "
							<< to_string(validCount) << "; Eclipses in memory: "
							<< to_string(catalogNums->getSize()) << endl
							<< endl;
				}

				//Close outfile
				outF.close();
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//HASH MAP OUTPUT
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		} else if (input == "H" || input == "h") {

			//Blank List Check
			if (tree->getSize() == 0) {
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
					map->printMap(cout);
					cout << "Data lines read: " << to_string(totalCount)
							<< "; Valid eclipses read: "
							<< to_string(validCount) << "; Eclipses in memory: "
							<< to_string(catalogNums->getSize()) << endl
							<< endl;

				} else {			//Else Print to certain file
					printHeader(outF);
					map->printMap(outF);
					outF << "Data lines read: " << to_string(totalCount)
							<< "; Valid eclipses read: "
							<< to_string(validCount) << "; Eclipses in memory: "
							<< to_string(catalogNums->getSize()) << endl
							<< endl;
				}

				//Close Output file
				outF.close();
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//PreOrder
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} else if (input == "R" || input == "r") {
			//Blank List Check
			if (tree->getSize() == 0) {
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
					tree->preorder(cout);
					cout << "Data lines read: " << to_string(totalCount)
							<< "; Valid eclipses read: "
							<< to_string(validCount) << "; Eclipses in memory: "
							<< to_string(catalogNums->getSize()) << endl
							<< endl;

				} else {			//Else Print to certain file
					printHeader(outF);
					tree->preorder(outF);
					outF << "Data lines read: " << to_string(totalCount)
							<< "; Valid eclipses read: "
							<< to_string(validCount) << "; Eclipses in memory: "
							<< to_string(catalogNums->getSize()) << endl
							<< endl;
				}

				//Close Output file
				outF.close();
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//PostOrder
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		} else if (input == "T" || input == "t") {
			//Blank List Check
			if (tree->getSize() == 0) {
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
					tree->postorder(cout);
					cout << "Data lines read: " << to_string(totalCount)
							<< "; Valid eclipses read: "
							<< to_string(validCount) << "; Eclipses in memory: "
							<< to_string(catalogNums->getSize()) << endl
							<< endl;

				} else {			//Else Print to certain file
					printHeader(outF);
					tree->postorder(outF);
					outF << "Data lines read: " << to_string(totalCount)
							<< "; Valid eclipses read: "
							<< to_string(validCount) << "; Eclipses in memory: "
							<< to_string(catalogNums->getSize()) << endl
							<< endl;
				}

				//Close Output file
				outF.close();
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//Quit
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		} else if (input == "Q" || input == "q") {
			cout << "Thanks for using eclipse." << endl;
			break;

			//If input doesnt make, character is invalid.
		} else {
			cout << "Invalid Character, Please Try again.";
		}
		array->~ResizableArray();
	}

	//Close CERR File
	cerrFile.close();
}

