/*
 * HashMap.h
 *
 * Templated HashMap. Creates a HashMap of any object
 * type and Encapsulates the Map in Private Variables, Allowing
 * Mutation and Access of Map through addition and deletion of HashNodes.
 *
 *  Created on: Nov 17, 2017
 *      Author: cglen
 */

#ifndef SRC_HASHMAP_H_
#define SRC_HASHMAP_H_

#include "HashNode.h"
#include <iostream>
#include <iomanip>

using namespace std;

template<class E>
class HashMap {

public:

	//Constructors
	HashMap(int size);
	HashMap(const HashMap<E> &map);
	~HashMap();

	//Operators
	template<class E1>
	friend std::ostream& operator<<(std::ostream& os, const HashMap<E1>* ll);

	//Accessors
	E get(int key) const;
	HashNode<int, E>* at(int index) const;
	int getSize() const;

	//Mutators
	void insert(int key, E e);
	void remove(int key);

private:

	//Private Functions
	void setNull();
	int hashKey(int key) const;

	//Private Variables
	HashNode<int, E>** map;
	int size;
};

/**
 * CONSTRUCTOR:
 * Creates a Hash Map object with a certain
 * size and sets all values in the hashmap to NULL
 *
 * Author: Clayton Glenn
 */
template<class E>
HashMap<E>::HashMap(int size) {
	this->size = size;
	map = new HashNode<int, E>*[size];
	setNull();
}

/**
 * COPY CONSTRUCTOR:
 * Creates a Hash Map object from
 * another Hash Map object's Map and Size
 *
 * Author: Clayton Glenn
 */
template<class E>
HashMap<E>::HashMap(const HashMap<E> &hm) {
	this->map = hm.map;
	this->size = hm.size;
}

/**
 * DESTRUCTOR:
 * Destroys the map array in the hashmap object
 *
 * Author: Clayton Glenn
 */
template<class E>
HashMap<E>::~HashMap() {
	delete[] this->map;
}

/**
 * OSTREAM OPERATOR:
 * Prints the contents of the map and If no
 * object exists in the specified index, this
 * function prints NULL.
 *
 * Author: Clayton Glenn
 */
template<class E>
std::ostream& operator<<(std::ostream& os, const HashMap<E>* hm) {

	HashNode<int, E> *n;
	for (int i = 0; i < hm->getSize(); ++i) {
		n = hm->at(i);
		if(n == NULL){
			os << setw(5) << std::right << "NULL" << endl;
		}
		while (n != NULL) {
			os << n->getValue();
			n = n->getNext();
		}
	}

	//Return outstream
	return os;
}

/**
 * GET:
 * This function gets a certain object with the specified key
 * from the calling function and returns null if an object
 * cannot be found.
 *
 * Author: Clayton Glenn
 */
template<class E>
E HashMap<E>::get(int key) const {

	int index = hashKey(key);
	if (index < 0 || index >= size) {
		throw out_of_range("HashTable<X>::insert() : Out of range");
		return NULL;
	}

	HashNode<int, E>* node = map[index];

	if (node == NULL) {
		throw invalid_argument(
				"E HashMap<E>::get(int key) const : Object not found");
		return node->getValue();
	}
	if (node->getKey() == key) {
		return node->getValue();
	}

	while (node->getKey() != key) {
		if (node->getNext() == NULL) {
			throw invalid_argument(
					"E HashMap<E>::get(int key) const : Object not found");
			return node->getValue();
		}
		node = node->getNext();
	}
	return node->getValue();
}

/**
 * AT:
 * Function that returns a HashNode at a
 * certain index to the calling function
 *
 * Author: Clayton Glenn
 */
template<class E>
HashNode<int, E>* HashMap<E>::at(int index) const {
	return map[index];
}

/**
 * GETSIZE:
 * Function that returns the size of the Hash Map object.
 *
 * Author: Clayton Glenn
 */
template<class E>
int HashMap<E>::getSize() const {
	return size;
}

/**
 * INSERT:
 * This function inserts object into the
 * hashmap as a node with a key and information
 *
 * Author: Clayton Glenn
 */
template<class E>
void HashMap<E>::insert(int key, E e) {

	int index = hashKey(key);
	if (index < 0 || index >= size) {
		throw out_of_range("HashTable<X>::insert() : Out of range");
		return;
	}

	HashNode<int, E>* node = new HashNode<int, E>(key, e);

	if (map[index] == NULL) {
		map[index] = node;
	} else {
		map[index]->setNext(node);
	}

	return;
}

/**
 * REMOVE:
 * This function removes a object that
 * match the specified key from the map
 *
 * Author: Clayton Glenn
 */
template<class E>
void HashMap<E>::remove(int key) {

	int index = hashKey(key);
	if (index < 0 || index >= size) {
		throw out_of_range("HashTable<X>::remove() : Out of range");
		return;
	}

	HashNode<int, E> *node = map[index], *q;
	if (node->getKey() == key) {
		map[index] = node->getNext();
		delete node;
		return;
	}

	q = node->getNext();
	while (q->getKey() != key) {
		if (q->getKey() == 0) {
			throw invalid_argument("HashTable::remove() : Object not found");
			return;
		}
		node = node->getNext();
		q = node->getNext();
	}
	node->setNext(node->getNext()->getNext());

	return;
}

/**
 * SETNULL:
 * This function is private and sets
 * all Elements of the array to NULL
 *
 * Author: Clayton Glenn
 */
template<class E>
void HashMap<E>::setNull() {
	for (int i = 0; i < size; ++i) {
		map[i] = NULL;
	}
}

/**
 * HASHKEY:
 * This function hashes a integer key
 * and returns it to the calling function.
 *
 * Author: Clayton Glenn
 */
template<class E>
int HashMap<E>::hashKey(int key) const {
	return key % size;
}

#endif /* SRC_HASHMAP_H_ */
