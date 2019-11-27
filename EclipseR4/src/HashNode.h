/*
 * HashNode.h
 *
 * Templated HashNode. Creates a HashNode of any object
 * type and Encapsulates the Node in Private Variables, Allowing
 * Mutation and Access of the Hash Node.
 *
 *  Created on: Nov 15, 2017
 *      Author: cglen
 */

#ifndef SRC_HASHNODE_H_
#define SRC_HASHNODE_H_

#include<iostream>

template<class K, class V>
class HashNode {
public:

	//Constructors
	HashNode(K key, V value);
	HashNode(const HashNode<K, V> &node);

	//Accessors
	K getKey() const;
	V getValue() const;
	HashNode* getNext() const;

	//Mutators
	void setValue(V value);
	void setNext(HashNode *next);

private:
	K key;
	V value;
	HashNode *next;
};

/**
 * CONSTRUCTOR:
 * Creates a Hash node from a key and a
 * value and sets the nodes next value to null.
 *
 * Author: Clayton Glenn
 */
template<class K, class V>
HashNode<K, V>::HashNode(K key, V value) {
	this->key = key;
	this->value = value;
	next = NULL;
}

/**
 * COPY CONSTRUCTOR:
 * Copies the information from another
 * hash node to this hash node.
 *
 * Author: Clayton Glenn
 */
template<class K, class V>
HashNode<K, V>::HashNode(const HashNode<K, V> &node) {
	this->key = node.key;
	this->value = node.value;
	next = node.next;
}

/**
 * GETKEY:
 * This function returns the key of the
 * HashNode to the calling function.
 *
 * Author: Clayton Glenn
 */
template<class K, class V>
K HashNode<K, V>::getKey() const {
	return key;
}

/**
 * GETVALUE:
 * This function returns the value of the
 * HashNode to the calling function.
 *
 * Author: Clayton Glenn
 */
template<class K, class V>
V HashNode<K, V>::getValue() const {
	return value;
}

/**
 * GETNEXT:
 * This function returns the next linked HashNode of the
 * HashNode to the calling function.
 *
 * Author: Clayton Glenn
 */
template<class K, class V>
HashNode<K, V>* HashNode<K, V>::getNext() const {
	return next;
}

/**
 * SETVALUE:
 * This function sets the Value of the
 * HashNode from a value brought in as a parameter.
 *
 * Author: Clayton Glenn
 */
template<class K, class V>
void HashNode<K, V>::setValue(V value) {
	HashNode::value = value;
}

/**
 * SETNEXT:
 * This function sets the next Linked HashNode of the
 * HashNode from a HashNode brought in as a parameter.
 *
 * Author: Clayton Glenn
 */
template<class K, class V>
void HashNode<K, V>::setNext(HashNode *next) {
	this->next = next;
}

#endif /* SRC_HASHNODE_H_ */
