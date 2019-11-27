/*
 * EclipseR.h
 *
 *	This header file are the functions for
 *	the EclipseR class. These are all helper
 *	functions for main. The majority of the
 *	 header file is a sorting algorith and a
 *	  searching algorithm.
 *
 *  Created on: Oct 18, 2017
 *      Author: cglen
 */

#ifndef SRC_ECLIPSER_H_
#define SRC_ECLIPSER_H_

#include "Eclipse.h"
#include "ResizableArray.h"

/*
 * This function compares two
 * integers and returns true or false.
 *
 * Author: Clayton Glenn
 */
bool compareInts(int a, int b) {
	if (a < b) {
		return true;
	} else {
		return false;
	}
}

/*
 * This function compares two floats
 * and returns true or false.
 *
 * Author: Clayton Glenn
 */
bool compareFloats(float a, float b) {
	if (a < b) {
		return true;
	} else {
		return false;
	}
}

/*
 * This function compares two strings
 * and returns true or false.
 *
 * Author: Clayton Glenn
 */
bool compareStrings(string a, string b) {

	if (b == "") {
		return true;
	}
	if (a == "") {
		return false;
	}
	if (a < b) {
		return true;
	} else {
		return false;
	}
}

/*
 * This function is the middle man for comparing
 * certain objects. Will mostlikely template the
 *  object in the next project.
 *
 * Author: Clayton Glenn
 */
bool compare(int column, Eclipse* e1, Eclipse* e2) {
	switch (column) {
	case 18:
		return compareStrings(e1->getCentDur(), e2->getCentDur());
	case 17:
		return compareInts(e1->getPathWidth(), e2->getPathWidth());
	case 16:
		return compareInts(e1->getSunAzm(), e2->getSunAzm());
	case 15:
		return compareInts(e1->getSunAlt(), e2->getSunAlt());
	case 14:
		return compareStrings(e1->getLongitude(), e2->getLongitude());
	case 13:
		return compareStrings(e1->getLatitude(), e2->getLatitude());
	case 12:
		return compareFloats(e1->getEclMag(), e2->getEclMag());
	case 11:
		return compareFloats(e1->getGamma(), e2->getGamma());
	case 10:
		return compareStrings(e1->getType(), e2->getType());
	case 9:
		return compareInts(e1->getSaros(), e2->getSaros());
	case 8:
		return compareInts(e1->getLuna(), e2->getLuna());
	case 7:
		return compareInts(e1->getDT(), e2->getDT());
	case 6:
		return compareStrings(e1->getTdOfGreat(), e2->getTdOfGreat());
	case 5:
		return compareInts(e1->getDay(), e2->getDay());
	case 4:
		return compareInts(e1->getMonthNum(), e2->getMonthNum());
	case 3:
		return compareInts(e1->getYear(), e2->getYear());
	case 2:
		return compareInts(e1->getCanPlate(), e2->getCanPlate());
	case 1:
		return compareInts(e1->getCatNum(), e2->getCatNum());
	default:
		return false;
	}
}

/*
 * This function swaps two eclipses in the array.
 *
 * Author: Clayton Glenn
 */
void insertion(ResizableArray<Eclipse*>* a, int CTR, int x) {
	if (CTR > 0 && compare(x, a->at(CTR), a->at(CTR - 1))) {
		a->swap(CTR, CTR - 1);
		--CTR;
		insertion(a, CTR, x);
	}
	return;
}

/*
 * This function, with help from others, sorts the array by Insertion
 * sort. Bad time complexity, but time complexity is not very
 * concerning right now.
 *
 * Author: Clayton Glenn
 */
void sort(ResizableArray<Eclipse*>* a, int x) {
	int ctr = 1, stepBackCTR;
	for (ctr = 1; ctr < a->getSize(); ++ctr) {
		stepBackCTR = ctr;
		insertion(a, stepBackCTR, x);
	}
	return;
}

/*
 * This function compares two integers and returns true or false.
 *
 * Author: Clayton Glenn
 */
bool equalsInts(int a, int b) {
	if (a == b) {
		return true;
	} else {
		return false;
	}
}

/*
 * This function compares two floats and returns true or false.
 *
 * Author: Clayton Glenn
 */
bool equalsFloats(float a, float b) {
	if (a < b + 0.0001 && a > b - 0.0001) {
		return true;
	} else {
		return false;
	}
}

/*
 * This function compares two strings and returns true or false.
 *
 * Author: Clayton Glenn
 */
bool equalsStrings(string a, string b) {

	if (a == b) {
		return true;
	} else {
		return false;
	}
}

/*
 * This function is the middle man for comparing
 * certain objects. Will mostlikely template the
 *  object in the next project.
 *
 * Author: Clayton Glenn
 */
bool equals(int column, Eclipse* e1, int a, float b, string c) {
	switch (column) {
	case 18:
		return equalsStrings(e1->getCentDur(), c);
	case 17:
		return equalsInts(e1->getPathWidth(), a);
	case 16:
		return equalsInts(e1->getSunAzm(), a);
	case 15:
		return equalsInts(e1->getSunAlt(), a);
	case 14:
		return equalsStrings(e1->getLongitude(), c);
	case 13:
		return equalsStrings(e1->getLatitude(), c);
	case 12:
		return equalsFloats(e1->getEclMag(), b);
	case 11:
		return equalsFloats(e1->getGamma(), b);
	case 10:
		return equalsStrings(e1->getType(), c);
	case 9:
		return equalsInts(e1->getSaros(), a);
	case 8:
		return equalsInts(e1->getLuna(), a);
	case 7:
		return equalsInts(e1->getDT(), a);
	case 6:
		return equalsStrings(e1->getTdOfGreat(), c);
	case 5:
		return equalsInts(e1->getDay(), a);
	case 4:
		if (a > 0 && a < 19) {
			return equalsInts(e1->getMonthNum(), a);
		}
		return false;
	case 3:
		return equalsInts(e1->getYear(), a);
	case 2:
		return equalsInts(e1->getCanPlate(), a);
	case 1:
		return equalsInts(e1->getCatNum(), a);
	default:
		return false;
	}
}

/*
 * This function, with help from other functions, searches for
 * eclipses and creates new array of eclipses that meet found
 * criteria.
 *
 * Author: Clayton Glenn
 */
ResizableArray<Eclipse*>* search(int x, ResizableArray<Eclipse*>* arr, int a,
		float b, string c) {

	ResizableArray<Eclipse*>* newArr = new ResizableArray<Eclipse*>();

	for (int i = 0; i < arr->getSize(); i++) {
		if (equals(x, arr->at(i), a, b, c)) {
			newArr->add(arr->at(i));
		}
	}
	return newArr;
}

/*
 * This function prints the headers of the new data files that
 * is 10 lines long.
 *
 * Author: Clayton Glenn
 */
void printHeader(ostream &o) {
	o << "Title: Five Millennium Catalog of Solar Eclipses:";
	o << "-1999 to +3000 (2000 BCE to 3000CE)" << endl;
	o << "Authors: Fred Espenak and Jean Meeus" << endl;
	o << "Source: Based on NASA Technical Publication";
	o << " TP-2006-21414" << endl;
	o << "Catalog Key: http://eclipse.gsfc.nasa.gov/SE";
	o << "cat5/catkey.html" << endl;
	o << "Date: 2007 Jan 26" << endl;
	o << "----------------------------------------------";
	o << "----------------------------------------------";
	o << "--------------------" << endl;
	o << "                            TD of" << endl;
	o << " Cat. Canon    Calendar   Greatest          Luna";
	o << " Saros Ecl.           Ecl.                Sun  Sun";
	o << "Path Central" << endl;
	o << "  No. Plate      Date      Eclipse     DT    Num  ";
	o << "Num  Type  Gamma    Mag.   Lat.   Long. Alt  Azm ";
	o << "Width   Dur." << endl;
	o << "                                       s          ";
	o << "?      ?     ?    ?   km" << endl;
}

/*
 * This function searches through catalog numbers and sends
 * index back to main function
 *
 * Author: Clayton Glenn
 */
int searchCats(Eclipse* e1, const ResizableArray<Eclipse*>* arr) {
	for (int i = 0; i < arr->getSize(); ++i) {
		if (arr->at(i)->getCatNum() == e1->getCatNum()) {
			return i;
		}
	}
	return -1;
}

/**
 * Function borrowed from stack overflow and manipulated to
 * fit format to check if string is an integer
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

/**
 * Function that immitates strtol and strtod converts Strings into
 * integers for Month Enumerator
 *
 * Author: Clayton Glenn
 */
int strom(string s) {
	if (s == "Dec") {
		return 12;
	} else if (s == "Nov") {
		return 11;
	} else if (s == "Oct") {
		return 10;
	} else if (s == "Sep") {
		return 9;
	} else if (s == "Aug") {
		return 8;
	} else if (s == "Jul") {
		return 7;
	} else if (s == "Jun") {
		return 6;
	} else if (s == "May") {
		return 5;
	} else if (s == "Apr") {
		return 4;
	} else if (s == "Mar") {
		return 3;
	} else if (s == "Feb") {
		return 2;
	} else if (s == "Jan") {
		return 1;
	} else {
		return -1;
	}
}

#endif /* SRC_ECLIPSER_H_ */
