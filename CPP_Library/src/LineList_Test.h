/*
 * LineList_Test.h
 *
 *  Created on: Sep 22, 2017
 *      Author: cglen
 */

#ifndef LINELIST_TEST_H_
#define LINELIST_TEST_H_

#include "LineList.h"

void print(LineList<int>* test) {
	cout << "{";
	for (int i = 0; i < test->size() - 1; ++i) {
		cout << " " << test->at(i) << ",";
	}
	if (test->size() != 0) {
		cout << " " << test->at(test->size() - 1) << " }" << endl;
	} else {
		cout << " " << " }" << endl;
	}
}

void lineListConstructorTest() {
	LineList<int>* test = new LineList<int>();
	if (test->capacity() == 10 && test->size() == 0) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void lineListOverloadedConstructorTest() {
	LineList<int>* test = new LineList<int>(42);
	if (test->capacity() == 42 && test->size() == 0) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void deleteLineListTest() {
	LineList<int>* test = new LineList<int>();
	test->~LineList();
	if (test->capacity() == 0 && test->size() == 0) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
}

void equalsTest() {
	LineList<int>* test1 = new LineList<int>(42);
	LineList<int>* test = new LineList<int>();
	test = test1;
	if (test->capacity() == 42 && test->size() == 0) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void outStreamTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	cout << test << endl;
	cout << "BlastOff!!!" << endl;
	test->~LineList();
}

void beginTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	if (test->begin() == 0) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void rbeginTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	if (test->rbegin() == size - 1) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void endTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	if (test->end() == size - 1) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void rendTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	if (test->rend() == 0) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void sizeTest() {
	LineList<int>* test = new LineList<int>();
	if (test->size() == 0) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void capacityTest() {
	LineList<int>* test = new LineList<int>();
	if (test->capacity() == 10) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void shrinkToFitTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->shrinkToFit();
	if (test->capacity() == 5) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void atTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	if (test->at(1) == 2) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void frontTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	if (test->front() == 1) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void backTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	if (test->back() == 5) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void dataTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	int * array = test->data();
	cout << "{";
	for (int i = 0; i < size - 1; ++i) {
		cout << " " << array[i] << ",";
	}
	cout << " " << array[size - 1] << " }" << endl;
	test->~LineList();
}

void indexOfTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	if (test->indexOf(2) == 1) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void lastIndexOfTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	if (test->lastIndexOf(3) == 2) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void subDataTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	int * array = test->subData(1, 3);
	cout << "{";
	for (int i = 0; i < 2; ++i) {
		cout << " " << array[i] << ",";
	}
	cout << " " << array[2] << " }" << endl;
	test->~LineList();
}

void containsTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	if (test->contains(3)) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void isEmptyTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	if (!test->isEmpty()) {
		cout << "Test Successful" << endl;
	} else {
		cout << "Test Unsuccessful" << endl;
	}
	test->~LineList();
}

void assignTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->assign(40, 2);
	print(test);
	test->~LineList();
}

void pushBackTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->pushBack(size);
	print(test);
	test->~LineList();
}

void pushFrontTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->pushFront(8);
	print(test);
	test->~LineList();
}

void popBackTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->popBack();
	print(test);
	test->~LineList();
}

void popFrontTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->popFront();
	print(test);
	test->~LineList();
}

void insertTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->insert(3, 2);
	print(test);
	test->~LineList();
}

void eraseTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->erase(2);
	print(test);
	test->~LineList();
}

void removeTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->remove(2);
	print(test);
	test->~LineList();
}

void pushBackTest(int * dataArray, int size, int * dataArray1, int size1) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->pushBack(dataArray1, size1);
	print(test);
	test->~LineList();
}

void pushFrontTest(int * dataArray, int size, int * dataArray1, int size1) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->pushFront(dataArray1, size1);
	print(test);
	test->~LineList();
}

void insertTest(int * dataArray, int size, int * dataArray1, int size1) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->insert(dataArray1, size1, 1);
	print(test);
	test->~LineList();
}

void removeAllTest(int * dataArray, int size, int * dataArray1, int size1) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->removeAll(dataArray1, size1);
	print(test);
	test->~LineList();
}

void eraseRangeTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->eraseRange(0, 1);
	print(test);
	test->~LineList();
}

void retainAllTest(int * dataArray, int size, int * dataArray1, int size1) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->retainAll(dataArray1, size1);
	print(test);
	test->~LineList();
}

void swapTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->swap(1, 3);
	print(test);
	test->~LineList();
}

void swapObjectsTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->swapObjects(1, 3);
	print(test);
	test->~LineList();
}

void clearTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->clear();
	print(test);
	test->~LineList();
}

void sortTest(int * dataArray, int size) {
	LineList<int>* test = new LineList<int>();
	test->pushBack(dataArray, size);
	test->pushBack(dataArray, size);
	test->pushBack(dataArray, size);
	test->sort();
	print(test);
	test->~LineList();
}

void lineListTest() {

	/*
	 * Header For Tests
	 */
	cout << "NOW ATTEMPTING LINE LIST TESTS..." << endl << endl << endl;

	//Arrays for Test
	int dataArray[] = { 1, 2, 3, 4, 5 };
	int dataArray1[] = { 3, 4, 6 };

	/*
	 * Testing All Member Functions
	 */
	cout << "Testing Constructor..." << endl;
	lineListConstructorTest();
	cout << endl << "Testing Overloaded Constructor..." << endl;
	lineListOverloadedConstructorTest();
	cout << endl << "Testing Destructor..." << endl;
	deleteLineListTest();
	cout << endl << "Testing Equals Copy Constructor..." << endl;
	equalsTest();
	cout << endl << "Testing Outstream Function..." << endl;
	outStreamTest(dataArray, 5);
	cout << endl << "Testing Begin Iterator Function..." << endl;
	beginTest(dataArray, 5);
	cout << endl << "Testing RBegin Iterator Function..." << endl;
	rbeginTest(dataArray, 5);
	cout << endl << "Testing End Iterator Function..." << endl;
	endTest(dataArray, 5);
	cout << endl << "Testing REnd Iterator Function..." << endl;
	rendTest(dataArray, 5);
	cout << endl << "Testing Size Function..." << endl;
	sizeTest();
	cout << endl << "Testing Capacity Function..." << endl;
	capacityTest();
	cout << endl << "Testing Shrink To Fit Function..." << endl;
	shrinkToFitTest(dataArray, 5);
	cout << endl << "Testing At Function..." << endl;
	atTest(dataArray, 5);
	cout << endl << "Testing Front Function..." << endl;
	frontTest(dataArray, 5);
	cout << endl << "Testing Back Function..." << endl;
	backTest(dataArray, 5);
	cout << endl << "Testing Data Function..." << endl;
	dataTest(dataArray, 5);
	cout << endl << "Testing Index Of Function..." << endl;
	indexOfTest(dataArray, 5);
	cout << endl << "Testing Last Index Of Function..." << endl;
	lastIndexOfTest(dataArray, 5);
	cout << endl << "Testing SubData Function..." << endl;
	subDataTest(dataArray, 5);
	cout << endl << "Testing Contains Function..." << endl;
	containsTest(dataArray, 5);
	cout << endl << "Testing Is Empty Function..." << endl;
	isEmptyTest(dataArray, 5);
	cout << endl << "Testing Assign Function..." << endl;
	assignTest(dataArray, 5);
	cout << endl << "Testing Push Back Function..." << endl;
	pushBackTest(dataArray, 5);
	cout << endl << "Testing Push Front Function..." << endl;
	pushFrontTest(dataArray, 5);
	cout << endl << "Testing Pop Back Function..." << endl;
	popBackTest(dataArray, 5);
	cout << endl << "Testing Pop Front Function..." << endl;
	popFrontTest(dataArray, 5);
	cout << endl << "Testing Insert Function..." << endl;
	insertTest(dataArray, 5);
	cout << endl << "Testing Erase Function..." << endl;
	eraseTest(dataArray, 5);
	cout << endl << "Testing Remove Function..." << endl;
	removeTest(dataArray, 5);
	cout << endl << "Testing Push Back Collection Function..." << endl;
	pushBackTest(dataArray, 5, dataArray1, 3);
	cout << endl << "Testing Push Front Collection Function..." << endl;
	pushFrontTest(dataArray, 5, dataArray1, 3);
	cout << endl << "Testing Insert Collection Function..." << endl;
	insertTest(dataArray, 5, dataArray1, 3);
	cout << endl << "Testing Remove All Function..." << endl;
	removeAllTest(dataArray, 5, dataArray1, 3);
	cout << endl << "Testing Erase Range Function..." << endl;
	eraseRangeTest(dataArray, 5);
	cout << endl << "Testing Retain All Function..." << endl;
	retainAllTest(dataArray, 5, dataArray1, 3);
	cout << endl << "Testing Swap Function..." << endl;
	swapTest(dataArray, 5);
	cout << endl << "Testing Swap Objects Function..." << endl;
	swapObjectsTest(dataArray, 5);
	cout << endl << "Testing Clear Function..." << endl;
	clearTest(dataArray, 5);
	cout << endl << "Testing Sort Function..." << endl;
	sortTest(dataArray, 5);
	cout << endl << endl << "LINE LIST TEST COMPLETE!!!!!!" << endl;
}

#endif /* LINELIST_TEST_H_ */
