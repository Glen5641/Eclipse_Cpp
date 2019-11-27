/*
 * UnitTests.h
 *
 *  Created on: Sep 19, 2017
 *      Author: cglen
 */

#ifndef UNITTESTS_H_
#define UNITTESTS_H_

#include <string>
#include <iostream>
#include "EclipseR0.3.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//      A R R A Y L I S T   T E S T S            A C T I V A T E   B Y   T E S T (  )   F U N C T I O N
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Test function to Test the Default Constructor in ArrayList
 *
 * Author: Clayton Glenn
 */
void testDefaultConstructor() {

	cout << "Testing Default Constructor..." << endl;

	ArrayList<string>* a = new ArrayList<string>();
	a->add("Hey");
	a->add("Hi");

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl << endl;

	delete a;

	return;
}

/*
 * Test function to Test the Overriden Constructor in ArrayList
 *
 * Author: Clayton Glenn
 */
void testOverrideConstructor() {

	cout << "Testing Override Constructor..." << endl;

	ArrayList<string>* a = new ArrayList<string>(23);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl << endl;

	delete a;

	return;
}

/*
 * Test function to Test the Destructor in ArrayList
 *
 * Author: Clayton Glenn
 */
void testDestructor() {

	cout << "Testing Destructor..." << endl;

	ArrayList<string>* a = new ArrayList<string>();

	delete a;

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl << endl;

	return;
}

/*
 * Test function to Test the Copy Constructor in ArrayList
 *
 * Author: Clayton Glenn
 */
void testCopyConstructor() {

	cout << "Testing CopyConstructor..." << endl;

	ArrayList<string>* a = new ArrayList<string>();
	a->add("Hey");

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl;

	ArrayList<string>* b = a;

	cout << "Number of Elements: " << b->length() << endl;
	cout << "Array Size: " << b->getCapacity() << endl;
	cout << "Array B: " << b->toString() << endl << endl;

	delete b;

	return;
}

/*
 * Test function to Test the Get Capacity Function in ArrayList
 *
 * Author: Clayton Glenn
 */
void testGetCapacity() {

	cout << "Testing GetCapacity Function..." << endl;

	ArrayList<string>* a = new ArrayList<string>(42);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl << endl;

	delete a;

	return;
}

/*
 * Test function to Test the Add Function in ArrayList
 *
 * Author: Clayton Glenn
 */
void testAdd() {

	cout << "Testing Add Function with String Parameter..." << endl;

	ArrayList<string>* a = new ArrayList<string>();
	a->add("Chase");
	a->add("Glenn");

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl << endl;

	delete a;

	return;
}

/*
 * Test function to Test the Overloaded Add Function in ArrayList
 *
 * Author: Clayton Glenn
 */
void testOverloadAdd() {

	cout << "Testing Add Function with String and Integer Parameter..." << endl;

	ArrayList<string>* a = new ArrayList<string>();
	a->add("Hey");
	a->add("Hey");
	a->add("Hey");
	a->add("Hey");
	a->add("Hey");
	a->add("Hey");
	a->add("What", 0);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl << endl;

	delete a;

	return;
}

/*
 * Test function to Test the Add All Function in ArrayList
 *
 * Author: Clayton Glenn
 */
void testAddAll() {

	cout << "Testing AddAll Function with Array and Integer Parameter...";

	ArrayList<string>* a = new ArrayList<string>();
	string c[] = { "Hey", "Hi", "HowRU", "How", "What", "Who", "Why" };
	a->addAll(c, 7);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl << endl;

	delete a;

	return;
}

/*
 * Test function to Test the Overloaded Set Function in ArrayList
 *
 * Author: Clayton Glenn
 */
void testSet() {

	cout << "Testing Set Function with String and Integer Parameter..." << endl;

	ArrayList<string>* a = new ArrayList<string>();
	string c[] = { "Hey", "Hi", "HowRU", "How", "What", "Who", "Why" };
	a->addAll(c, 7);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl;

	a->set("WhatchyaDoin", 3);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl << endl;

	delete a;

	return;
}

/*
 * Test function to Test the Get Function in ArrayList
 *
 * Author: Clayton Glenn
 */
void testGet() {

	cout << "Testing Get Function..." << endl;

	ArrayList<string>* a = new ArrayList<string>();
	string c[] = { "Hey", "Hi", "HowRU", "How", "What", "Who", "Why" };
	a->addAll(c, 7);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl;
	cout << "The 3rd Element is " << a->get(2);

	delete a;

	return;
}

/*
 * Test function to Test the To Array Function in ArrayList
 *
 * Author: Clayton Glenn
 */
void testToArray() {

	cout << "Testing ToArray Function..." << endl;

	ArrayList<string>* a = new ArrayList<string>();
	string c[] = { "Hey", "Hi", "HowRU", "How", "What", "Who", "Why" };
	a->addAll(c, 7);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	for (int i = 0; i < a->length(); ++i) {
		cout << a->toArray()[i] << " ";
	}
	cout << endl << endl;

	delete a;
	return;
}

/*
 * Test function to Test the Contains Function in ArrayList
 *
 * Author: Clayton Glenn
 */
void testContains() {

	cout << "Testing Contain Function with String Parameter..." << endl;

	ArrayList<string>* a = new ArrayList<string>();
	string c[] = { "Hey", "Hi", "HowRU", "How", "What", "Who", "Why" };
	a->addAll(c, 7);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl;

	if (a->contains("How")) {
		cout << "Array Contains How" << endl << endl;
	}

	delete a;

	return;
}

/*
 * Test function to Test the Index Of Function in ArrayList
 *
 * Author: Clayton Glenn
 */
void testIndexOf() {

	cout << "Testing IndexOf Function with String Parameter..." << endl;

	ArrayList<string>* a = new ArrayList<string>();
	string c[] = { "Hey", "Hi", "HowRU", "How", "What", "Who", "Why" };
	a->addAll(c, 7);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl;
	cout << "Who is indexes as " << a->indexOf("Who") << endl << endl;

	delete a;

	return;
}

/*
 * Test Function to Test the Last Index Of Function in ArrayList
 *
 * Author: Clayton Glenn
 */
void testLastIndexOf() {

	cout << "Testing LastIndexOf Function with String Parameter..." << endl;

	ArrayList<string>* a = new ArrayList<string>();
	string c[] = { "Hey", "Hi", "HowRU", "Who", "What", "Who", "Why" };
	a->addAll(c, 7);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl;
	cout << "Who is indexes as " << a->lastIndexOf("Who") << endl << endl;

	delete a;

	return;
}

/*
 * Test Function to Test the Remove Function in Arraylist
 *
 * Author: Clayton Glenn
 */
void testRemove() {

	cout << "Testing Remove Function with String Parameter..." << endl;

	ArrayList<string>* a = new ArrayList<string>();
	string c[] = { "Hey", "Hi", "HowRU", "Who", "What", "Who", "Why" };
	a->addAll(c, 7);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl;

	a->removeObject("Who");

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl << endl;

	delete a;

	return;
}

/*
 * Test Function to Test the Overloaded Remove Function in Arraylist
 *
 * Author: Clayton Glenn
 */
void testOverloadRemove() {

	cout << "Testing Remove Function with Integer Parameter..." << endl;

	ArrayList<string>* a = new ArrayList<string>();
	string c[] = { "Hey", "Hi", "HowRU", "Who", "What", "Who", "Why" };
	a->addAll(c, 7);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl;

	a->remove(6);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl << endl;

	delete a;

	return;
}

/*
 * Test Function to Test the Trim to Size Function in Arraylist
 *
 * Author: Clayton Glenn
 */
void testTrimToSize() {

	cout << "Testing TrimToSize Function..." << endl;

	ArrayList<string>* a = new ArrayList<string>();
	string c[] = { "Hey", "Hi", "HowRU", "Who", "What", "Who", "Why" };
	a->addAll(c, 7);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl;

	a->trimToSize();

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl << endl;

	delete a;

	return;
}

/*
 * Test Function to Test the Overloaded Trim to Size Function in Arraylist
 *
 * Author: Clayton Glenn
 */
void testOverloadTrimToSize() {
	cout << "Testing TrimToSize Function with Integer Parameter..." << endl;

	ArrayList<string>* a = new ArrayList<string>();
	string c[] = { "Hey", "Hi", "HowRU", "Who", "What", "Who", "Why" };
	a->addAll(c, 7);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl;
	a->trimToSize(3);

	cout << "Number of Elements: " << a->length() << endl;
	cout << "Array Size: " << a->getCapacity() << endl;
	cout << "Array A: " << a->toString() << endl;
	delete a;
	return;
}

/*
 * Test Function that Wraps ALL Arraylist Tests Together
 *
 * Author: Clayton Glenn
 */
void test() {

	testDefaultConstructor();
	testOverrideConstructor();
	testDestructor();
	testCopyConstructor();
	testGetCapacity();
	testAdd();
	testOverloadAdd();
	testAddAll();
	testSet();
	testGet();
	testToArray();
	testContains();
	testIndexOf();
	testLastIndexOf();
	testRemove();
	testOverloadRemove();
	testTrimToSize();
	testOverloadTrimToSize();
}



#endif /* UNITTESTS_H_ */
