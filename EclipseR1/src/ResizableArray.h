/*
 * ResizableArray.h
 *
 * Templated Resizable Array. Creates a Dynamic Array of any object
 * type and Encapsulates the Array in Private Variables, Allowing
 * Mutation and Access of Array through Member Functions.
 *
 *  Created on: Sep 25, 2017
 *      Author: Clayton Glenn
 */

#ifndef SRC_RESIZABLEARRAY_H_
#define SRC_RESIZABLEARRAY_H_

#include <iostream>
#include <ostream>
#include <iomanip>
#include <string>

using namespace std;

/**
 * Templated Resizable Array. Creates a Dynamic Array of any object
 * type and Encapsulates the Array in Private Variables, Allowing
 * Mutation and Access of Array through Member Functions.
 *
 * Author: Clayton Glenn
 */
template<class T>
class ResizableArray {
public:

	//Public Member Functions
	ResizableArray();									//CONSTRUCTOR
	ResizableArray(int capacity);						//CONSTRUCTOR
	ResizableArray(const ResizableArray<T>& ra);		//COPY CONSTRUCTOR
	~ResizableArray();									//DESTRUCTOR
	void operator=(const ResizableArray<T>& ra);		//OVERLOADED =OPERATOR
	template<class T1>									//OVERLOADED <<OPERATOR
	friend std::ostream& operator<<(std::ostream& os,
			const ResizableArray<T1>* ra);

	//Public Accessor Functions
	int getSize() const;			//CAPACITY FUNCTION ||	FIND SIZE OF ARRAY
	T at(int index) const;			//SINGLE OBJECT     ||	FIND CERTAIN OBJECT
	int binarySearch(int l, int r, T x);

	//Public Modifier Functions
	void add(T object);						//SINGLE OBJECT		||  ADD OBJECT
	void addAt(T object, int index);//SINGLE OBJECT		||  ADD OBJECT AT INDEX
	void replaceAt(T object, int index);//SINGLE OBJECT		||  MUTATE OBJECT AT INDEX
	void removeAt(int index);	//SINGLE OBJECT		||  REMOVE OBJECT AT INDEX
	void swap(int index1, int index2);

private:
	//Private Variables
	T * array;							//VARIABLE  		||  PRIVATE ARRAY
	int capacity;						//VARIABLE  		||  PRIVATE CAPACITY
	int size;								//VARIABLE  		||  PRIVATE SIZE

	//Private Capacity Functions
	void doubleCapacity();		//CAPACITY FUNCTION ||  DOUBLE CAPACITY OF ARRAY
	void doubleCapacity(int elements);//CAPACITY FUNCTION ||  ENSURE CAPACITY OF ARRAY
	void halfCapacity();		//CAPACITY FUNCTION ||  HALF CAPACITY OF ARRAY
};

/*
 * Default Constructor for Creating Blank ResizableArray.
 *
 * Author: Clayton Glenn
 */
template<class T>
ResizableArray<T>::ResizableArray() {

	//Initiallize the Private Variables by Default
	this->capacity = 10;
	this->array = new T[this->capacity];
	this->size = 0;

	//Return to Calling Function
	return;
}

/*
 * Overloaded Constructor for Creating ResizableArray with
 * User Specified Elements.
 *
 * Author: Clayton Glenn
 */
template<class T>
ResizableArray<T>::ResizableArray(int capacity) {

	//Initiallize the Private Variables by Default Except
	//for a User Declared Size
	this->capacity = capacity;
	this->array = new T[this->capacity];
	this->size = 0;

	//Return to Calling Function
	return;
}

/*
 * Copy Constructor for Initiallizing ResizableArray
 * with another ResizableArray
 *
 * Author: Clayton Glenn
 */
template<class T>
ResizableArray<T>::ResizableArray(const ResizableArray &ra) {

	//Copy Data from Another ResizableArray Object
	this->array = ra.array;
	this->capacity = ra.capacity;
	this->size = ra.size;

	//Return to Calling Function
	return;
}

/*
 * Destructor for Deleting Array Associated with ResizableArray
 *
 * Author: Clayton Glenn
 */
template<class T>
ResizableArray<T>::~ResizableArray() {

	//Delete the Private Array in the ResizableArray
	delete[] this->array;
	size = 0;
	capacity = 0;

	//Return to Calling Function
	return;
}

/*
 * Overloads =Operator to Initiallize ResizableArray
 *  with another ResizableArray
 *
 * Author: Clayton Glenn
 */
template<class T>
void ResizableArray<T>::operator=(const ResizableArray<T>& ra) {

	//Copy outside ResizableArray to this object
	this = new ResizableArray<T>(ra);

	//Return to Calling Function
	return;
}

/*
 * Overloads Standard Output and Prints ResizableArray Backwards
 * With One Element Per Line.
 *
 * Author: Clayton Glenn
 */
template<class T>
std::ostream& operator<<(std::ostream& os, const ResizableArray<T>* ra) {

	//Print each element of array
	for (int count = 0; count < ra->getSize(); ++count) {
		os << ra->at(count);
	}

	//Return outstream
	return os;
}

/*
 * Accessor Function: Returns the size of the resizable array
 *
 * Author: Clayton Glenn
 */
template<class T>
int ResizableArray<T>::getSize() const {

	//Return the size of the array
	return this->size;
}

/*
 * Accessor Function: Returns a specific object
 * of the resizable array
 *
 * Author: Clayton Glenn
 */
template<class T>
T ResizableArray<T>::at(int index) const {

	//Return a certain index of array
	return this->array[index];
}

/*
 * Mutator Method: Adds an object to the end of
 * the array and increments size
 *
 * Author: Clayton Glenn
 */
template<class T>
void ResizableArray<T>::add(T object) {

	//Double capacity if needed
	this->doubleCapacity();

	//Add object to array
	this->array[this->size] = object;
	this->size++;

	//Return to calling function
	return;
}

/*
 * Mutator Function: Adds an object at a specified
 * index to array and increments size
 *
 * Author: Clayton Glenn
 */
template<class T>
void ResizableArray<T>::addAt(T object, int index) {

	//Throw out of range exception if needed
	if (index >= this->size) {
		throw std::out_of_range("ArrayList<X>::at() : index is out of range");
	}

	//Double capacity if needed
	doubleCapacity();
	for (int count = this->size - 1; count >= index; --count) {
		this->array[count + 1] = this->array[count];
	}

	//Add object at specified index
	this->array[index] = object;
	this->size++;

	//Return to calling function
	return;
}

/*
 * Mutator Function: Replaces an object at a specified
 * index to array
 *
 * Author: Clayton Glenn
 */
template<class T>
void ResizableArray<T>::replaceAt(T object, int index) {

	//Replace object if index is not out of bounds
	if (index < this->size && index >= 0) {
		this->array[index] = object;
	} else {
		throw std::out_of_range("ArrayList<X>::at() : index is out of range");

	}

	//Return to calling function
	return;
}

/*
 * Mutator Function: Removes an object at a specified index
 *
 * Author: Clayton Glenn
 */
template<class T>
void ResizableArray<T>::removeAt(int index) {

	//Check index in bounds
	if (index >= this->size) {
		throw std::out_of_range("ArrayList<X>::at() : index is out of range");
	}

	//Remove a specified element from array
	for (int count = index; count < this->size; ++count) {
		array[count] = array[count + 1];
	}
	this->size--;

	//Halve capacity if needed
	halfCapacity();

	//Return to calling function
	return;
}

/*
 * Private Mutator Method: Doubles the capacity of the resizable array
 *
 * Author: Clayton Glenn
 */
template<class T>
void ResizableArray<T>::doubleCapacity() {

	//Double capacity until sufficient space is allocated
	while ((this->size) >= this->capacity - 3) {
		this->capacity *= 2;
		T * newArray = NULL;
		newArray = new T[this->capacity];
		for (int i = 0; i < this->size; ++i) {
			newArray[i] = this->array[i];
		}
		delete[] this->array;
		this->array = newArray;
	}

	//Return to calling function
	return;
}

/*
 * Private Mutator Method: Halves the capacity of the resizable array
 *
 * Author: Clayton Glenn
 */
template<class T>
void ResizableArray<T>::halfCapacity() {

	//Half capacity until sufficient memory is deleted
	while ((this->size) < this->capacity / 2 - 3) {
		this->capacity /= 2;
		T * newArray = NULL;
		newArray = new T[this->capacity];
		for (int i = 0; i < this->size; ++i) {
			newArray[i] = this->array[i];
		}
		delete[] this->array;
		this->array = newArray;
	}

	//Return to calling function
	return;
}

/*
 * Public Mutator Method: This function swaps two objects at specified indexes.
 *
 * Author: Clayton Glenn
 */
template<class T>
void ResizableArray<T>::swap(int index1, int index2) {
	T temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;
	return;
}

#endif /* SRC_RESIZABLEARRAY_H_ */
