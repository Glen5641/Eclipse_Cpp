/*
 * DoublyLinkedList.h
 *
 *  Created on: Oct 22, 2017
 *      Author: cglen
 */

#ifndef DOUBLYLINKEDLIST_H_
#define DOUBLYLINKEDLIST_H_
#include <iostream>
#include <ostream>
#include <iomanip>
#include <string>

using namespace std;

template<class T>
class DoublyLinkedList {
public:
	DoublyLinkedList(T object);
	void add_begin(T object);
	void add_end(T object);
	void add_after(T object, int pos);
	void delete_object(T object);			//try catch
	void delete_element(int position);		//try catch

	void display_list();
	int count() const;
	void reverse();							//try catch

	void swap_positions(int index1, int index2);	//try catch
	void swap(T object1, T object2);		//try catch
	T peek(int index) const;			//try catch
	int position_of(T object);						//try catch
	string toString() const;
	template<class T1>
	friend std::ostream& operator<<(std::ostream& os,
			const DoublyLinkedList<T1>* ll);
private:
	int size;
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
DoublyLinkedList<T>::DoublyLinkedList(T object) {

	//Create HEAD of linked list
	this->head = new (struct node);
	this->head->info = object;
	this->head->prev = NULL;
	this->head->next = NULL;

	//HEAD equals TAIL w/ only one element
	this->tail = head;

	//Set SIZE to 1
	this->size = 1;
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
	temp->next = this->head;

	//Attach TMP to HEAD PREV and reassign HEAD as TMP
	this->head->prev = temp;
	this->head = temp;

	//Increment SIZE
	this->size++;
}

/**
 * ADD_AFTER:
 * Creates a new object and adds it to a selected position.
 * The selected position is found by iteration from head or
 * tail based on half of the size.
 *
 * Author: Clayton Glenn
 */
template<class T>
void DoublyLinkedList<T>::add_after(T object, int position) {

	//Bounds Checking
	if (position > this->size || position < 1) {
		cout << "Position is out of bounds" << endl;
		return;
	}

	//Q is selected element in linked list and TMP is element being added.
	//I is incrementer
	struct node *temp, *q;
	int i;

	//Find which side to search the array for better efficiency.
	//Only checks for median size, not Catalog number.
	if (position <= this->size / 2) { //If POS is half of SIZE, Start from HEAD of Linked list
		q = this->head;
		for (i = 1; i < position; i++) { //Increment from HEAD
			q = q->next;
		}
	} else { //If POS is half of SIZE, Start from TAIL of Linked list
		q = this->tail;
		for (i = this->size; i > position; --i) { //Decrement from TAIL
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
		this->tail = temp;
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
	this->size++;
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
	temp->prev = this->tail;

	//Link TMP to TAILS next value.
	this->tail->next = temp;

	//Reassign TAIL as TMP
	this->tail = temp;

	//Increment SIZE
	this->size++;
}

/**
 * DELETE_OBJECT:
 * Finds a certain object in the Linked List and
 * deletes it by wrapping the previous object to
 * the next object of the linked list and freeing
 * the selected object
 *
 * Author: Clayton Glenn
 */
template<class T>
void DoublyLinkedList<T>::delete_object(T object) {

	struct node *temp;

	//If OBJECT is HEAD of linked list
	if (this->head->info == object) {

		//resassign HEAD as next element
		temp = this->head;
		this->head = this->head->next;
		this->head->prev = NULL;

		//free Q from memory and decrement SIZE
		free(temp);
		this->size--;

		//Return so the rest of the function is not reached.
		return;
	}

	/*If OBJECT isnt HEAD, iterate through the linked list
	 until the object it found, but stop 1 element before TAIL*/
	temp = this->head;
	while (temp->next->next != NULL) {
		if (temp->info == object) {

			//Link the previous and next of Q to each other, and free Q.
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			free(temp);

			//Decrement SIZE
			this->size--;

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
		this->size--;

		//Return so the rest of the function is not reached.
		return;
	}

	/*If the OBJECT isnt found, OBJECT
	 is not in linked list. Return*/
	return;
}

/**
 * DELETE_ELEMENT:
 * Finds a certain element in the Linked List and
 * deletes it by wrapping the previous object to
 * the next object of the linked list and freeing
 * the selected element
 *
 * Author: Clayton Glenn
 */
template<class T>
void DoublyLinkedList<T>::delete_element(int position) {

	//If POSITION is out of bounds, get out fast.
	if (position < 0 || position >= size) {
		cout << "Index out of bounds" << endl;
		return;
	}

	//Declare a TEMP node to store needed information
	struct node *temp;

	if (position == 0) { //If POSITION is at HEAD of linked list

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
 * POSITION_OF:
 * Finds a certain object by iteration in the Linked
 * List and returns the position of the object.
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
 * COUNT:
 * Returns the Size of the linked list
 *
 * Author: Clayton Glenn
 */
template<class T>
int DoublyLinkedList<T>::count() const {

	//Return SIZE to calling function
	return this->size;
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
 * SWAP_POSITIONS:
 * Flips the info on two selected elements in the linked list.
 *
 * Author: Clayton Glenn
 */
template<class T>
void DoublyLinkedList<T>::swap_positions(int position1, int position2) {

	//Declare 3 nodes for manipulation
	struct node *p, *q, *temp;

	//If POSITIONS are out of bounds, get out fast
	if (position1 >= size || position2 >= size) {
		cout << "Index out of bounds." << endl;
		return;
	}
	if (position1 <= 0 || position2 <= 0) {
		cout << "Index out of bounds." << endl;
		return;
	}

	//Iterate through linked list until the two chosen POSITIONS
	//are found from HEAD or TAIL depeneding on SIZE
	int i = 0;
	if (position1 <= size / 2) {
		p = head;
		for (i = 0; i < position1 - 1; i++) {
			p = p->next;
		}
	} else {
		p = tail;
		for (i = size - 1; i >= position1; --i) {
			p = p->prev;
		}
	}

	if (position2 <= size / 2) {
		q = head;
		for (i = 0; i < position2 - 1; i++) {
			q = q->next;
		}
	} else {
		q = tail;
		for (i = size - 1; i >= position2; --i) {
			q = q->prev;
		}
	}

	//just flip the INFO of the two nodes to hold linked list integrity
	temp = new (struct node);
	temp->info = q->info;
	q->info = p->info;
	p->info = temp->info;

	//Return to calling function
	return;
}

template<class T>
void DoublyLinkedList<T>::swap(T object1, T object2) {

	//Declare 3 nodes for data manipulation
	struct node *p, *q, *temp;

	//Initiallize P & Q as HEAD
	p = head;
	q = head;

	//Increment through the linked list and find the objects
	if (head == object1) {
		while (q->info != object2 && q->next != NULL) {
			q = q->next;
		}
	} else if (head == object2) {
		while (p->info != object1 && p->next != NULL) {
			p = p->next;
		}
	} else {
		while (p->info != object1 && p->next != NULL) {
			p = p->next;
		}
		while (q->info != object2 && q->next != NULL) {
			q = q->next;
		}
	}

	//Check if P & Q are equal to OBJECTS
	if (p != object1 && q != object2) {
		cout << "Both objects not found" << endl;
	}

	//Swap Information of the two selected OBJECTS.
	temp = new (struct node);
	temp->info = q->info;
	q->info = p->info;
	p->info = temp->info;

	//Return to calling function
	return;
}

template<class T>
T DoublyLinkedList<T>::peek(int position) const {
	if (position < 1 || position > size) {
		cout << "Out of bounds" << endl;
		return tail->info;  //TODO Needs changed
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

template<class T>
std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>* ll) {

	for (int i = 1; i <= ll->count(); ++i) {
		os << to_string(ll->peek(i)) << endl;
	}

	//Return outstream
	return os;
}

#endif /* DOUBLYLINKEDLIST_H_ */
