/*
 * Search.h
 *
 * This searching file uses a specialized comparator to
 * compare the columns of the eclipses to a specific object
 * specified by user. It Uses an iterative search to save
 * time not having to sort the list beforehand.
 *
 *  Created on: Nov 2, 2017
 *      Author: cglen
 */

#ifndef SEARCH_H_
#define SEARCH_H_

#include "Eclipse.h"
#include "ResizableArray.h"

using namespace std;

bool equalsInts(int a, int b);
bool equalsFloats(float a, float b);
bool equalsStrings(string a, string b);
bool equals(int column, Eclipse* e1, int a, float b, string c);
ResizableArray<Eclipse*>* search(int x, ResizableArray<Eclipse*>* ll, int a,
		float b, string c);

#endif /* SEARCH_H_ */
