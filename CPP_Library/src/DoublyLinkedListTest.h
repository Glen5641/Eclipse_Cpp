/*
 * DoublyLinkedListTest.h
 *
 *  Created on: Oct 22, 2017
 *      Author: cglen
 */

#ifndef DOUBLYLINKEDLISTTEST_H_
#define DOUBLYLINKEDLISTTEST_H_
#include "DoublyLinkedList.h"

void linkListTests() {
	cout << "Testing Constructor with 5" << endl;
	DoublyLinkedList<int>* list = new DoublyLinkedList<int>(5);
	cout << list << endl;

	cout << "Push 1,2,4 to front" << endl;
	list->add_begin(4);
	list->add_begin(2);
	list->add_begin(1);
	cout << list << endl;
	cout << endl;

	cout << "Add 3 after 2" << endl;
	list->add_after(3, 2);
	cout << list << endl;
	cout << endl;

	cout << "Add 6 after 5" << endl;
	list->add_after(6, 5);
	cout << list << endl;
	cout << endl;

	cout << "Add 7 to end" << endl;
	list->add_end(7);
	cout << list << endl;
	cout << endl;

	cout << "Delete 3" << endl;
	list->delete_object(3);
	cout << list << endl;
	cout << endl;

	cout << "Delete Element 3" << endl;
	list->delete_element(3);
	cout << list << endl;
	cout << endl;

	cout << "Add 3 after 2" << endl;
	list->add_after(3, 2);
	cout << list << endl;
	cout << endl;

	cout << "Add 4 after 3" << endl;
	list->add_after(4, 3);
	cout << list << endl;
	cout << endl;

	cout << "Search from 1-6" << endl;
	int i = list->position_of(1);
	cout << to_string(i) << ", ";
	i = list->position_of(2);
	cout << to_string(i) << ", ";
	i = list->position_of(3);
	cout << to_string(i) << ", ";
	i = list->position_of(4);
	cout << to_string(i) << ", ";
	i = list->position_of(5);
	cout << to_string(i) << ", ";
	i = list->position_of(6);
	cout << to_string(i) << endl;
	cout << endl;

	cout << "Testing size" << endl;
	i = list->count();
	cout << to_string(i) << endl;
	cout << endl;

	cout << "Reversing order of list" << endl;
	list->reverse();
	cout << list << endl;
	cout << endl;

	cout << "Search from 1-6" << endl;
	i = list->position_of(1);
	cout << to_string(i) << ", ";
	i = list->position_of(2);
	cout << to_string(i) << ", ";
	i = list->position_of(3);
	cout << to_string(i) << ", ";
	i = list->position_of(4);
	cout << to_string(i) << ", ";
	i = list->position_of(5);
	cout << to_string(i) << ", ";
	i = list->position_of(6);
	cout << to_string(i) << endl;

	cout << endl << "Swap elements 1 & 3" << endl;
	list->swap_positions(1, 3);
	cout << list << endl;
	cout << endl;
}

#endif /* DOUBLYLINKEDLISTTEST_H_ */
