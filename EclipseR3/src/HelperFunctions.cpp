/*
 * HelperFunctions.cpp
 *
 * This file is for helper functions in the main method.
 * It contains functions like manipulation of month, is
 * int, is double, and print headers.
 *
 *  Created on: Nov 2, 2017
 *      Author: cglen
 */

#include "HelperFunctions.h"

/*
 * PRINTHEADER:
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
 * SEARCHCATS:
 * This function searches through catalog numbers and sends
 * index back to main function
 *
 * Author: Clayton Glenn
 */
int searchCats(Eclipse* e1, DoublyLinkedList<Eclipse*>* ll) {
	for (int i = 1; i < ll->count(); ++i) {
		if (ll->peek(i)->getCatNum() == e1->getCatNum()) {
			return i;
		}
	}
	return -1;
}

/**
 * ISINTEGER:
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
 * ISDOUBLE:
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
 * STROM:
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


