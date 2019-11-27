/*
 * LinkedHashMap.h
 *
 * Linked Hash Map. Creates a HashMap from a linked list of eclipses
 * and Encapsulates the Map and the list in Private Variables, Allowing
 * Mutation and Access of Map through addition, selection and deletion
 * of HashNodes.
 *
 *  Created on: Nov 17, 2017
 *      Author: cglen
 */

#ifndef SRC_LINKEDHASHMAP_H_
#define SRC_LINKEDHASHMAP_H_

#include <iostream>
#include "HashMap.h"
#include "DoublyLinkedList.h"
#include "Eclipse.h"

using namespace std;

class LinkedHashMap {

public:

	//Constructor
	LinkedHashMap(DoublyLinkedList<Eclipse*>* list);
	LinkedHashMap(const LinkedHashMap &hashTable);
	~LinkedHashMap();

	//Accessors
	Eclipse* get(int key) const;
	int getMapSize() const;
	int getListSize() const;
	bool sync() const;
	bool isEmpty() const;

	//Mutators
	void add(Eclipse* e);
	void addToList(Eclipse* e);
	void addToMap(Eclipse* e);
	void remove(int key);
	void removeFromList(int key);
	void removeFromMap(int key);

	//Printing operators
	void printList(ostream &o);
	void printMap(ostream &o);

private:

	//Private Functions
	void populateMap();
	void determineSize();

	//Private Variables
	DoublyLinkedList<Eclipse*>* default_list;
	HashMap<Eclipse*>* map;
	int mapSize;
	bool inSync;
};

#endif /* SRC_LINKEDHASHMAP_H_ */
