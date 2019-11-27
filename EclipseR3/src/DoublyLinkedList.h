/*
 * DoublyLinkedList.h
 *
 * Templated Doubly Linked List. Creates a Doubly Linked List of any object
 * type and Encapsulates the List in Private Variables, Allowing
 * Mutation and Access of List through addition and deletion of elements.
 *
 *  Created on: Oct 22, 2017
 *      Author: cglen
 */

#ifndef DOUBLYLINKEDLIST_H_
#define DOUBLYLINKEDLIST_H_

#include "ResizableArray.h"

/*
 * Templated Doubly Linked List. Creates a Doubly Linked List of any object
 * type and Encapsulates the List in Private Variables, Allowing
 * Mutation and Access of List through addition and deletion of elements.
 *
 * Author: Clayton Glenn
 */
template<class T>
class DoublyLinkedList {
public:

	//Constructors
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList<T> &ll);
	~DoublyLinkedList();

	//Operators
	template<class T1>
	friend std::ostream& operator<<(std::ostream& os,
			const DoublyLinkedList<T1>* ll);

	//Accessors
	int count() const;
	T peek(int index) const;
	int position_of(T object);

	//Mutators
	void create_list(T object);
	void add_begin(T object);
	void add_end(T object);
	void add_after(T object, int position);
	void delete_object(T object);
	void delete_element(int position);
	void reverse();
	void replace_at(T object, int position);
	ResizableArray<T>* getList();

private:

	//Size of LinkedList
	int size;

	//Head and Tail nodes of LinkedList
	struct node {
		T info;
		struct node *next;
		struct node *prev;
	}*head, *tail;
};

/**
 * CONSTRUCTOR:
 * Creates a doubly linked list with object attached as the head of the linked list.
 * Tail is same as head to start the list and size is set to one.
 *
 * Author: Clayton Glenn
 */
template<class T>
DoublyLinkedList<T>::DoublyLinkedList() {

	//Create HEAD of linked list
	head = new (struct node);
	head->info = NULL;
	head->prev = NULL;
	head->next = NULL;

	//HEAD equals TAIL w/ only one element
	tail = head;

	//Set SIZE to 1
	size = 0;
}

/**
 * COPY CONSTRUCTOR:
 * Creates a doubly linked list with LinkedList Object
 * Head, Tail, and Size are set to head, tail, and size respectively
 *
 * Author: Clayton Glenn
 */
template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &ll) {
	head = ll.head;
	tail = ll.tail;
	size = ll.size;
}

/**
 * DESTRUCTOR:
 * Deletes the linked list by freeing all elements and
 * initiallizing Head and Tail to NULL. Linked List needs
 * to create a new list before adding elements to it.
 *
 * Author: Clayton Glenn
 */
template<class T>
DoublyLinkedList<T>::~DoublyLinkedList() {

	struct node *q, *p;
	q = head;
	p = head->next;
	for (int i = 1; i <= size; ++i) {
		if (p->next != NULL) {
			free(q);
			q = p;
			p = p->next;
		}
		free(q);
	}
	head = NULL;
	tail = NULL;
}

/**
 * OPERATOR<<:
 * Creates an outstream object with all of the linked lists
 * elements printed to it. Then the ostream is returned to
 * the calling function.
 *
 * Author: Clayton Glenn
 */
template<class T>
std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>* ll) {

	for (int i = 1; i <= ll->count(); ++i) {
		os << ll->peek(i);
	}

//Return outstream
	return os;
}

/**
 * COUNT:
 * Returns the Size of the linked list
 *
 * Author: Clayton Glenn
 */
template<class T>
int DoublyLinkedList<T>::count() const {

	//Return SIZE to calling function
	return size;
}

/**
 * PEEK:
 * Returns a constant copy of the element's information
 * at a specified position.
 *
 * Throws Exception if index is out of bounds
 *
 * Author: Clayton Glenn
 */
template<class T>
T DoublyLinkedList<T>::peek(int position) const {

	//Throw out of range exception if needed
	if (position < 1 || position > size) {
		throw std::out_of_range(
				"DoublyLinkedList<T>::peek() : index is out of range");
		return tail->info;
	}

	if (position == 1) {
		return head->info;
	} else if (position == size) {
		return tail->info;
	} else {
		struct node *temp;
		if (position <= size / 2) {
			temp = head;
			for (int i = 1; i < position; ++i) {
				temp = temp->next;
			}
			return temp->info;
		} else {
			temp = tail;
			for (int i = size; i > position; --i) {
				temp = temp->prev;
			}
			return temp->info;
		}
	}
}

/**
 * POSITION_OF:
 * Finds a certain object by iteration in the Linked
 * List and returns the position of the object.
 *
 * Returns -1 if object is not found
 *
 * Author: Clayton Glenn
 */
template<class T>
int DoublyLinkedList<T>::position_of(T object) {

	//Create an incrementer node called TEMP
	struct node *temp;
	temp = head;
	int i = 1;

	//If HEAD matches OBJECT, return the position of HEAD
	if (temp->info == object) {
		return i;
	}

	//Loop until OBJECT is found
	while (temp->next != NULL) {
		i++;
		temp = temp->next;
		if (temp->info == object) {	//If found, return Position of OBJECT
			return i;
		}
	}

	//If no OBJECT is found, return -1
	return -1;
}

/**
 * CREATE_LIST:
 * Creates the initial linked list after being constructed
 * with the first element being the object. Head and Tail
 * are initiallized as the single object in the list.
 *
 * Author: Clayton Glenn
 */
template<class T>
void DoublyLinkedList<T>::create_list(T object) {
	//Create HEAD of linked list
	head = new (struct node);
	head->info = object;
	head->prev = NULL;
	head->next = NULL;

	//HEAD equals TAIL w/ only one element
	tail = head;

	//Set SIZE to 1
	size = 1;
}

/**
 * ADD_BEGIN:
 * Adds an object to the beginning of the linked list and assigns
 * the head as objects next value. In turn, head is initiallized
 * as the new object.
 *
 * Author: Clayton Glenn
 */
template<class T>
void DoublyLinkedList<T>::add_begin(T object) {

	//Create new node and assign PREV as NULL, NEXT as HEAD, and INFO as OBJECT
	struct node *temp;
	temp = new (struct node);
	temp->info = object;
	temp->prev = NULL;
	temp->next = head;

	//Attach TMP to HEAD PREV and reassign HEAD as TMP
	head->prev = temp;
	head = temp;

	//Increment SIZE
	size++;
}

/**
 * ADD_END:
 * Adds an object to the end of the linked list and assigns
 * the tail as objects prev value. In turn, tail is initiallized
 * as the new object.
 *
 * Author: Clayton Glenn
 */
template<class T>
void DoublyLinkedList<T>::add_end(T object) {

	//Create new TMP linked list node and assign as OBJECT.
	struct node *temp = new (struct node);
	temp->info = object;
	temp->next = NULL;
	temp->prev = tail;

	//Link TMP to TAILS next value.
	tail->next = temp;

	//Reassign TAIL as TMP
	tail = temp;

	//Increment SIZE
	size++;
}

/**
 * ADD_AFTER:
 * Creates a new object and adds it to a selected position.
 * The selected position is found by iteration from head or
 * tail based on half of the size.
 *
 * Throws exception if index is out of bounds
 *
 * Author: Clayton Glenn
 */
template<class T>
void DoublyLinkedList<T>::add_after(T object, int position) {

	//Throw out of range exception if needed
	if (position > this->size || position < 1) {
		throw std::out_of_range(
				"DoublyLinkedList<T>::add_after() : index is out of range");
		return;
	}

	//Q is selected element in linked list and TMP is element being added.
	//I is incrementer
	struct node *temp, *q;
	int i;

	//Find which side to search the array for better efficiency.
	//Only checks for median size, not Catalog number.
	if (position <= size / 2) {
		q = head;
		for (i = 1; i < position; ++i) {
			q = q->next;
		}
	} else {
		q = tail;
		for (i = size; i > position; --i) {
			q = q->prev;
		}
	}

	//Initiallize TMP as new node with OBJECT information
	temp = new (struct node);
	temp->info = object;

	if (q->next == NULL) { //If Q is the TAIL
		temp->prev = q;
		temp->next = NULL;
		q->next = temp;
		tail = temp;
	} else if (q->prev == NULL) { //If Q is the HEAD
		temp->next = q->next;
		temp->prev = NULL;
		temp->next->prev = temp;
		q->next = temp;
	} else { //If Q is ANYTHING ELSE
		temp->next = q->next;
		temp->prev = q;
		temp->next->prev = temp;
		q->next = temp;
	}

	//Increment SIZE
	size++;
}

/**
 * DELETE_OBJECT:
 * Finds a certain object in the Linked List and
 * deletes it by wrapping the previous object to
 * the next object of the linked list and freeing
 * the selected object
 *
 * throws exception if object is not found
 *
 * Author: Clayton Glenn
 */
template<class T>
void DoublyLinkedList<T>::delete_object(T object) {

	struct node *temp;

	//If OBJECT is HEAD of linked list
	if (head->info == object) {

		//resassign HEAD as next element
		temp = head;
		head = head->next;
		head->prev = NULL;

		//free Q from memory and decrement SIZE
		free(temp);
		size--;

		//Return so the rest of the function is not reached.
		return;
	}

	/*If OBJECT isnt HEAD, iterate through the linked list
	 until the object it found, but stop 1 element before TAIL*/
	temp = head;
	while (temp->next->next != NULL) {
		if (temp->info == object) {

			//Link the previous and next of Q to each other, and free Q.
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			free(temp);

			//Decrement SIZE
			size--;

			//Return so the rest of the function is not reached.
			return;
		}
		temp = temp->next;
	}

	/*If this part of function is reached, The last element
	 the object can be is the TAIL, so initiallize Q to TAIL*/
	temp = temp->next;

	//If TAIL equals OBJECT
	if (temp->info == object) {

		//Break Q off Linked List and Free it
		temp->prev->next = NULL;
		free(temp);

		//Decrement SIZE
		size--;

		//Return so the rest of the function is not reached.
		return;
	}

	/*If the OBJECT isnt found, OBJECT
	 is not in linked list. Return*/

	//Throw out of range exception if needed
	throw std::invalid_argument(
			"DoublyLinkedList<T>::delete_object() : Object not found");
	return;
}

/**
 * DELETE_ELEMENT:
 * Finds a certain element in the Linked List and
 * deletes it by wrapping the previous object to
 * the next object of the linked list and freeing
 * the selected element
 *
 * Throws exception if index is out of bounds
 *
 * Author: Clayton Glenn
 */
template<class T>
void DoublyLinkedList<T>::delete_element(int position) {

	//Throw out of range exception if needed
	if (position > this->size || position < 1) {
		throw std::out_of_range(
				"DoublyLinkedList<T>::delete_element() : index is out of range");
		return;
	}

	//Declare a TEMP node to store needed information
	struct node *temp;

	if (position == 1) { //If POSITION is at HEAD of linked list

		//Break off HEAD of linked list and set second POSITION as HEAD
		temp = head;
		head = head->next;
		head->prev = NULL;

		//Free TEMP from memory
		free(temp);

		//Decrement SIZE
		size--;

		//Return so rest of function is not reachable
		return;
	}

	if (position == size) {	//If POSITION is at TAIL of linked list

		//Break off TAIL of linked list and set second to last  POSITION as TAIL
		temp = tail;
		tail = tail->prev;
		tail->next = NULL;

		//Free TEMP from memory
		free(temp);

		//Decrement SIZE
		size--;

		//Return so rest of function is not reachable
		return;
	}

	//Initiallize TEMP as HEAD of linked list and increment or
	//decrement through linked list depending on POSITION related to SIZE
	int i = 1;
	if (position <= size / 2) {
		temp = head;
		for (i = 1; i < position; i++) {
			temp = temp->next;
		}
	} else {
		temp = tail;
		for (i = size; i > position; --i) {
			temp = temp->prev;
		}
	}

	//Break TEMP from linked list and free it.
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	free(temp);

	//Decrement SIZE
	size--;

	//Return to calling function
	return;

}

/**
 * REVERSE:
 * Reverses the linked list through iteration
 *
 * Author: Clayton Glenn
 */
template<class T>
void DoublyLinkedList<T>::reverse() {

	//Create Two TEMPORARY nodes for manipulation
	struct node *temp1, *temp2;

	//Initialize TEMP1 as HEAD and TEMP2 as second object
	temp1 = head;
	temp2 = temp1->next;

	//Flip TEMP1's linked objects
	temp1->next = NULL;
	temp1->prev = temp2;
	while (temp2 != NULL) {	//Loop while TEMP2 isn't TAIL

		//Step through Linkedlist with TEMP2 and Switch
		//linked objects of TEMP2 and attach to TEMP1
		temp2->prev = temp2->next;
		temp2->next = temp1;
		temp1 = temp2;
		temp2 = temp2->prev;
	}

	//Initiallize TAIL as HEAD and HEAD as TAIL
	tail = head;
	head = temp1;

	//Return to Calling function
	return;
}

/**
 * REPLACE_AT:
 * Replaces the selected element of the linked list's
 * information with the object from the parameters.
 *
 * Throws exception if index is out of bounds
 *
 * Author: Clayton Glenn
 */
template<class T>
void DoublyLinkedList<T>::replace_at(T object, int position) {

	//Throw out of range exception if needed
	if (position > this->size || position < 1) {
		throw std::out_of_range(
				"DoublyLinkedList<T>::replace_at() : index is out of range");
		return;
	}

	struct node *temp;
	temp = head;
	for (int i = 1; i < position; ++i) {
		temp = temp->next;
	}

	temp->info = object;

	return;
}

/**
 * GETLIST:
 * Returns a resizable array of the eclipses.
 * Only used for time efficiency.
 *
 * Author: Clayton Glenn
 */
template<class T>
ResizableArray<T>* DoublyLinkedList<T>::getList() {

	struct node *p = head;
	ResizableArray<T>* array = new ResizableArray<T>(size);

	//Populate the array
	for (int i = 1; i <= size; ++i) {
		array->add(p->info);
		p = p->next;
	}

	//Return array
	return array;
}

#endif /* DOUBLYLINKEDLIST_H_ */
