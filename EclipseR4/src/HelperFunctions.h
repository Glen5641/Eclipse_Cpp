/*
 * HelperFunctions.h
 *
 * This file is for helper functions in the main method.
 * It contains functions like manipulation of month, is
 * int, is double, and print headers.
 *
 *  Created on: Nov 2, 2017
 *      Author: cglen
 */

#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

#include <iostream>
#include "Eclipse.h"
#include "AVLTree.h"
#include "DoublyLinkedList.h"
#include "MonthEnum.h"

using namespace std;

void printHeader(ostream &o);
int searchCats(Eclipse* e1, AVLTree<Eclipse*>* tree);
bool isInteger(std::string & s);
bool isDouble(std::string & s);
int strom(string s);

#endif /* HELPERFUNCTIONS_H_ */
