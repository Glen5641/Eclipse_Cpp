/*
 * Search.cpp
 *
 * This searching file uses a specialized comparator to
 * compare the columns of the eclipses to a specific object
 * specified by user. It Uses an iterative search to save
 * time not having to sort the list beforehand.
 *
 *  Created on: Nov 2, 2017
 *      Author: cglen
 */

#include <iostream>
#include <string>
#include "Eclipse.h"
#include "ResizableArray.h"

using namespace std;

/*
 * EQUALSINTS:
 * This function compares two integers and returns true
 * if integer A equals integer B. Returns false if the
 * integers do not match.
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
 * EQUALSFLOATS:
 * This function compares two floats and returns true
 * if float A equals float B. Returns false if the
 * floats do not match.
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
 * EQUALSSTRINGS:
 * This function compares two strings and returns true
 * if string A equals string B. Returns false if the
 * strings do not match.
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
 * EQUALS:
 * Middle man for checking compares on different columns.
 * Calls String, Integer, and Float comparing functions
 * that immediately gets returned to the calling function.
 *
 * Author: Clayton Glenn
 */
bool equals(int x, Eclipse* e1, int a, float b, string c) {
	switch (x) {
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
 * SEARCH:
 * This function, with help from other functions, searches for matching
 * eclipses iteratively based on a column number and creates new array of eclipses
 * that meet found criteria. Iteration is used so array can be unsorted.
 * This produces a O(n) time complexity.
 *
 * Author: Clayton Glenn
 */
ResizableArray<Eclipse*>* search(int x, ResizableArray<Eclipse*>* ra, int a,
		float b, string c) {

	ResizableArray<Eclipse*>* newra = new ResizableArray<Eclipse*>();

	for (int i = 0; i < ra->getSize(); i++) {
		if (equals(x, ra->at(i), a, b, c)) {
				newra->add(ra->at(i));
		}
	}
	return newra;
}

