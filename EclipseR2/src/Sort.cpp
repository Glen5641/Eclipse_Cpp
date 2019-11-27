/*
 * Sort.cpp
 *
 * This sorting file uses a specialized comparator to
 * compare the columns of the eclipses to a specific object
 * specified by user. It Uses an quicksort to sort the Array
 * it is manipulating.
 *
 *  Created on: Nov 2, 2017
 *      Author: cglen
 */

#include <iostream>
#include "Eclipse.h"
#include "ResizableArray.h"

using namespace std;

/*
 * COMPAREINTS:
 * This function compares two
 * integers and returns true if a is less than
 * or equal to b or false if b is less than a.
 *
 * Author: Clayton Glenn
 */
bool compareInts(int a, int b) {
	if (a <= b) {
		return true;
	} else {
		return false;
	}
}

/*
 * COMPAREFLOATS:
 * This function compares two floats
 * and returns true if a is less than
 * or equal to b or false if b is less than a.
 *
 * Author: Clayton Glenn
 */
bool compareFloats(float a, float b) {
	if (a <= b) {
		return true;
	} else {
		return false;
	}
}

/*
 * COMPARESTRINGS:
 * This function compares two strings
 * and returns true if a is less than
 * or equal to b or false if b is less than a.
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
	if (a <= b) {
		return true;
	} else {
		return false;
	}
}

/*
 * COMPARE:
 * This function is the middle man for comparing
 * certain objects. It uses string, int, and float
 * comparators to compare a certain column in the eclipses.
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
 * PARTITION:
 * This function takes last element as pivot, places
 * the pivot element at its correct position in sorted
 * array, and places all smaller (smaller than pivot)
 * to left of pivot and all greater elements to right
 * of pivot.
 *
 * This function was derived from
 * http://www.geeksforgeeks.org/quick-sort/ to
 * specifically work on Eclipse Array's.
 *
 * Author: http://www.geeksforgeeks.org/quick-sort/ && Clayton Glenn
 */
int partition(ResizableArray<Eclipse*>* a, int low, int high, int x) {
	Eclipse* pivot = a->at(high);    // pivot
	int i = (low - 1);  // Index of smaller element

	for (int j = low; j <= high - 1; j++) {
		// If current element is smaller than or
		// equal to pivot
		if (compare(x, a->at(j), pivot)) {
			i++;    // increment index of smaller element
			a->swap(i, j);
		}
	}
	a->swap(i + 1, high);
	return (i + 1);
}

/*
 * QUICKSORT:
 * This Function implements a quicksort to sort the
 * array that is passed in. This function was modified from
 * http://www.geeksforgeeks.org/quick-sort/ to be implemented
 * specifically on the eclipses.
 *
 * Author: http://www.geeksforgeeks.org/quick-sort/ && Clayton Glenn
 */
void quickSort(ResizableArray<Eclipse*>* a, int low, int high, int x) {
	if (low < high) {
		/* pi is partitioning index, arr[p] is now
		 at right place */
		int pi = partition(a, low, high, x);

		// Separately sort elements before
		// partition and after partition
		quickSort(a, low, pi - 1, x);
		quickSort(a, pi + 1, high, x);
	}
}
