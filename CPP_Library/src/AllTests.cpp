/*
 * AllTests.cpp
 *
 *  Created on: Sep 22, 2017
 *      Author: cglen
 */

#include "LineList_Test.h"
#include "DoublyLinkedListTest.h"

bool isInteger(std::string & s) {
	if (s.empty()
			|| ((!isdigit(s[0])) && (s[0] != '-' && s.length() == 1)
					&& (s[0] != '+')))
		return false;
	if (s[0] == '0' && s.length() == 1) {
		return true;
	}
	char * p;
	strtol(s.c_str(), &p, 10);
	if (*p != '\0' || p == s) {
		return false;
	}
	return true;
}

int main() {

	cout << "Which Library Would You Like To Test?" << endl;
	cout << "1 : LineList" << endl;
	cout << "2 : LinkedList" << endl;
	cout << "3 : ResizableArray" << endl;

	string word;
	getline(cin, word);
	int num;
	if (isInteger(word)) {
		char * p;
		num = strtol(word.c_str(), &p, 10);
	}

	switch (num) {
	case 3:
	case 2:
		linkListTests();
		break;
	case 1:
		lineListTest();
		break;
	default:
		cout << "Error" << endl;
		break;
	}
}

