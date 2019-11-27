/*
 * Sort.h
 *
 * This sorting file uses a specialized comparator to
 * compare the columns of the eclipses to a specific object
 * specified by user. It Uses an quicksort to sort the Array
 * it is manipulating.
 *
 *  Created on: Nov 2, 2017
 *      Author: cglen
 */

#ifndef SORT_H_
#define SORT_H_

#include "Eclipse.h"
#include "ResizableArray.h"

using namespace std;

bool compareInts(int a, int b);
bool compareFloats(float a, float b);
bool compareStrings(string a, string b);
bool compare(int column, Eclipse* e1, Eclipse* e2);
int partition(ResizableArray<Eclipse*>* a, int low, int high, int x);
void quickSort(ResizableArray<Eclipse*>* a, int low, int high, int x);

#endif /* SORT_H_ */
