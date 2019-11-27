/*
 * LineList.h
 *
 *  Created on: Sep 22, 2017
 *      Author: cglen
 */

#ifndef LINELIST_H_
#define LINELIST_H_

#include<iostream>
#include<string>

using namespace std;

/**
 * Templated Object Set. Creates a Dynamic Array of any
 * type and Encapsulates the Array in Private Variables, Allowing
 * Mutation and Access of Array through Member Functions.
 *
 * Author: Clayton Glenn
 */
template<class T>
class LineList {
public:

	//Public Member Functions
	LineList();																	//CONSTRUCTOR
	LineList(int arraySize);													//CONSTRUCTOR
	LineList(const LineList<T>& ll);											//COPY CONSTRUCTOR
	~LineList();																//DESTRUCTOR
	void operator=(const LineList<T>& ll);										//OVERLOADED =OPERATOR
	friend ostream& operator<<(ostream& os, const LineList<string>& line); 		//OVERLOADED <<OPERATOR

	//Public Iterator Functions
	int begin() const;										//LINE BEGINNING
	int rbegin() const;										//LINE ENDING
	int end() const;										//LINE ENDING
	int rend() const;										//LINE BEGINNING

	//Public Capacity Functions
	int size() const;										//ARRAY SIZE
	int capacity() const;									//ARRAY CAPACITY
	void shrinkToFit();										//SHRINK LINE CAPACITY

	//Public Element Access Functions
	T at(int index) const;									//SINGLE OBJECT		||  ACCESS AT INDICATED ELEMENT
	T front() const;										//SINGLE OBJECT		||  ACCESS FIRST ELEMENT
	T back() const;											//SINGLE OBJECT		||  ACCESS LAST ELEMENT
	T * data() const;										//ALL OBJECTS		||  ACCESS LINE
	int indexOf(T object) const;							//SINGLE OBJECT		||  ACCESS TO OBJECT AT INDEX
	int lastIndexOf(T object) const;						//SINGLE OBJECT		||  ACCESS TO OBJECT AT LAST INDEX
	T * subData(int start, int end) const;					//MULITPLE OBJECTS	||  ACCESS TO SUB LINE
	bool contains(T object) const;							//SINGLE OBJECT		||  OBJECT IN LINE CHECK
	bool isEmpty() const;									//ALL OBJECTS		||  EMPTY LINE CHECK

	//Public Modifier Functions
	void assign(T object, int index);						//SINGLE OBJECT		||  MUTATE OBJECT AT INDEX
	void pushBack(T object);								//SINGLE OBJECT		||  ADD OBJECT TO LINE END
	void pushFront(T object);								//SINGLE OBJECT		||  ADD OBJECT TO LINE BEGIN
	void popBack();											//SINGLE OBJECT		||  REMOVE OBJECT FROM LINE END
	void popFront();										//SINGLE OBJECT		||  REMOVE OBJECT FROM LINE BEGIN
	void insert(T object, int index);						//SINGLE OBJECT		||  INSERT OBJECT AT INDEX
	void erase(int index);									//SINGLE OBJECT		||  ERASE OBJECT AT INDEX
	void remove(T object);									//SINGLE OBJECT		||  REMOVE OBJECT FROM LINE
	void pushBack(T * collection, int elements);			//MULITPLE OBJECTS	||  ADD COLLECTION TO LINE END
	void pushFront(T * collection, int elements);			//MULITPLE OBJECTS	||  ADD COLLECTION TO LINE BEGIN
	void insert(T * collection, int elements, int index);	//MULITPLE OBJECTS	||  INSERT COLLECTION AT INDEX
	void removeAll(T * collection, int elements);			//MULITPLE OBJECTS	||  REMOVE COLLECTION FROM LINE
	void eraseRange(int start, int end);					//MULITPLE OBJECTS	||  ERASE COLLECTION FROM FROM INDEX RANGE
	void retainAll(T * collection, int elements);			//MULITPLE OBJECTS	||  RETAIN ONLY COLLECTION
	void swap(int index1, int index2);						//MULITPLE OBJECTS	||  SWAP TWO ELEMENTS IN LINE
	void swapObjects(T object1, T object2);					//MULITPLE OBJECTS	||  SWAP TWO OBJECTS IN LINE
	void clear();											//ALL OBJECTS		||  CLEAR LINE
	void sort();											//ALL OBJECTS		||  SORT LINE

private:
	//Private Variables
	T * lineList;					//VARIABLE  		||  PRIVATE ARRAY
	int arraySize;					//VARIABLE  		||  PRIVATE SIZE
	int elementsInArray;			//VARIABLE  		||  PRIVATE ELEMENTS

	//Private Capacity Functions
	void doubleCapacity();					//CAPACITY FUNCTION ||  DOUBLE CAPACITY OF LINE
	void ensureCapacity(int elements);		//CAPACITY FUNCTION ||  ENSURE CAPACITY OF LINE
	void halfCapacity();					//CAPACITY FUNCTION ||  HALF CAPACITY OF LINE
	void insertion(int CTR);				//All OBJECTS		||	SWAP ELEMENTS
};

/*
 * Overloads Standard Output and Prints LineList Backwards
 * With One Element Per Line.
 *
 * Author: Clayton Glenn
 */
template<class T>
ostream& operator<<(ostream& os, const LineList<T>* ll) {
	for (int count = ll->size() - 1; count >= 0; --count) {
		if (count != 0) {
			os << ll->at(count) << endl;
		} else {
			os << ll->at(0);
		}
	}

	return os;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Public Member Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Default Constructor for Creating Blank LineList.
 *
 * Author: Clayton Glenn
 */
template<class T>
LineList<T>::LineList() {

	//Initiallize the Private Variables by Default
	this->arraySize = 10;
	this->lineList = new T[this->arraySize];
	this->elementsInArray = 0;

	//Return to Calling Function
	return;
}

/*
 * Overloaded Constructor for Creating LineList with User Specified Elements.
 *
 * Author: Clayton Glenn
 */
template<class T>
LineList<T>::LineList(int arraySize) {

	//Initiallize the Private Variables by Default Except for a User Declared Size
	this->arraySize = arraySize;
	this->lineList = new T[this->arraySize];
	this->elementsInArray = 0;

	//Return to Calling Function
	return;
}

/*
 * Copy Constructor for Initiallizing LineList with another LineList
 *
 * Author: Clayton Glenn
 */
template<class T>
LineList<T>::LineList(const LineList &LineList) {

	//Copy Data from Another LineList Object
	this->lineList = LineList.lineList;
	this->arraySize = LineList.arraySize;
	this->elementsInArray = LineList.elementsInArray;

	//Return to Calling Function
	return;
}

/*
 * Destructor for Deleting Array Associated with LineList
 *
 * Author: Clayton Glenn
 */
template<class T>
LineList<T>::~LineList() {

	//Delete the Private Array in the LineList
	delete[] this->lineList;
	elementsInArray = 0;
	arraySize = 0;

	//Return to Calling Function
	return;
}

/*
 * Overloads =Operator to Initiallize LineList with another LineList
 *
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::operator=(const LineList<T>& ll) {

	//Copy outside LineList to this object
	this = new LineList<T>(ll);

	//Return to Calling Function
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Public Iterator Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Returns Beginning of LineList
 *
 * Author: Clayton Glenn
 */
template<class T>
int LineList<T>::begin() const {

	//Return Beginning Integer to Calling Function
	return 0;
}

/*
 * Returns Reverse Beginning of LineList
 *
 * Author: Clayton Glenn
 */
template<class T>
int LineList<T>::rbegin() const {

	//Return End of LineList to Calling Function
	if (this->elementsInArray != 0) {
		return this->elementsInArray - 1;
	} else {
		return 0;
	}
}

/*
 * Returns End of LineList
 *
 * Author: Clayton Glenn
 */
template<class T>
int LineList<T>::end() const {

	//Return End of LineList to Calling Function
	if (this->elementsInArray != 0) {
		return this->elementsInArray - 1;
	} else {
		return 0;
	}
}

/*
 * Returns Reverse End of LineList
 *
 * Author: Clayton Glenn
 */
template<class T>
int LineList<T>::rend() const {

	//Returns Zero Integer for Beginning to Calling Function
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Public Capacity Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Returns Size of LineList
 *
 * Author: Clayton Glenn
 */
template<class T>
int LineList<T>::size() const {

	//Return Size of LineList to Calling Function
	return this->elementsInArray;
}

/*
 * Returns Capacity of LineList
 *
 * Author: Clayton Glenn
 */
template<class T>
int LineList<T>::capacity() const {

	//Return Capacity of LineList to Calling Finction
	return this->arraySize;
}

/*
 * Shrinks LineList to Amount of Elements in LineList
 *
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::shrinkToFit() {

	//Create New Perfect Sized Array
	T *newArray = NULL;
	this->arraySize = this->elementsInArray;
	newArray = new T[this->arraySize];

	//Populate Array
	for (int i = 0; i < this->elementsInArray; ++i) {
		newArray[i] = this->lineList[i];
	}

	//Delete Old Array and Copy Array to This LineList
	delete[] this->lineList;
	this->lineList = newArray;

	//Return to Calling Function
	return;
}

/* TODO Comments
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::doubleCapacity() {
	while ((this->elementsInArray) >= this->arraySize - 3) {
		this->arraySize *= 2;
		T *newArray = NULL;
		newArray = new T[this->arraySize];
		for (int i = 0; i < this->elementsInArray; ++i) {
			newArray[i] = this->lineList[i];
		}
		delete[] this->lineList;
		this->lineList = newArray;
	}
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::ensureCapacity(int elements) {
	while ((this->elementsInArray + elements) >= this->arraySize - 3) {
		this->arraySize *= 2;
		T *newArray = NULL;
		newArray = new T[this->arraySize];
		for (int i = 0; i < this->elementsInArray; ++i) {
			newArray[i] = this->lineList[i];
		}
		delete[] this->lineList;
		this->lineList = newArray;
	}
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::halfCapacity() {
	while ((this->elementsInArray) < this->arraySize / 2 - 2) {
		this->arraySize /= 2;
		T *newArray = NULL;
		newArray = new T[this->arraySize];
		for (int i = 0; i < this->elementsInArray; ++i) {
			newArray[i] = this->lineList[i];
		}
		delete[] this->lineList;
		this->lineList = newArray;
	}
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Public Element Access Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Author: Clayton Glenn
 */
template<class T>
T LineList<T>::at(int index) const {
	if (index < this->elementsInArray) {
		return this->lineList[index];
	}
	T object = 2;
	return object;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
T LineList<T>::front() const {
	return this->lineList[0];
}

/*
 * Author: Clayton Glenn
 */
template<class T>
T LineList<T>::back() const {
	return this->lineList[this->elementsInArray - 1];
}

/*
 * Author: Clayton Glenn
 */
template<class T>
T * LineList<T>::data() const {
	return this->lineList;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
int LineList<T>::indexOf(T object) const {
	for (int count = 0; count < this->elementsInArray; ++count) {
		if (this->lineList[count] == object) {
			return count;
		}
	}
	return -1;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
int LineList<T>::lastIndexOf(T object) const {
	for (int count = this->elementsInArray - 1; count >= 0; --count) {
		if (this->lineList[count] == object) {
			return count;
		}
	}
	return -1;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
T * LineList<T>::subData(int start, int end) const {
	if (start >= end) {
		return NULL;
	}
	T * subList = new T[end - start + 1];
	int listElements = 0;
	while (start <= end) {
		subList[listElements] = this->lineList[start];
		start++;
		listElements++;
	}
	return subList;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
bool LineList<T>::contains(T object) const {
	for (int count = 0; count < this->elementsInArray; ++count) {
		if (this->lineList[count] == object) {
			return true;
		}
	}
	return false;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
bool LineList<T>::isEmpty() const {
	if (this->lineList == 0) {
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Public Modifier Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::assign(T object, int index) {
	if (index < this->elementsInArray) {
		this->lineList[index] = object;
	}
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::pushBack(T object) {
	doubleCapacity();
	this->lineList[this->elementsInArray] = object;
	elementsInArray++;
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::pushFront(T object) {
	doubleCapacity();
	for (int count = this->end(); count > this->begin(); --count) {
		lineList[count] = this->lineList[count - 1];
	}
	this->lineList[0] = object;
	this->elementsInArray++;
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::popBack() {
	elementsInArray--;
	halfCapacity();
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::popFront() {
	for (int count = 0; count < elementsInArray; ++count) {
		lineList[count] = lineList[count + 1];
	}
	elementsInArray--;
	halfCapacity();
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::insert(T object, int index) {
	doubleCapacity();
	for (int count = rbegin(); count >= index; --count) {
		this->lineList[count + 1] = this->lineList[count];
	}
	this->lineList[index] = object;
	this->elementsInArray++;
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::erase(int index) {
	for (int count = index; count < elementsInArray; ++count) {
		lineList[count] = lineList[count + 1];
	}
	elementsInArray--;
	halfCapacity();
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::remove(T object) {
	int index = indexOf(object);
	if (index == -1) {
		return;
	}
	for (int count = index; count < elementsInArray; ++count) {
		lineList[count] = lineList[count + 1];
	}
	elementsInArray--;
	halfCapacity();
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::pushBack(T * collection, int elements) {
	ensureCapacity(elements);
	for (int count = this->elementsInArray;
			count < (this->elementsInArray + elements); ++count) {
		this->lineList[count] = collection[count - this->elementsInArray];
	}
	this->elementsInArray += elements;
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::pushFront(T * collection, int elements) {
	ensureCapacity(elements);
	for (int count = elements - 1; count >= 0; --count) {
		this->pushFront(collection[count]);
	}
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::insert(T * collection, int elements, int index) {
	ensureCapacity(elements);
	for (int count = elements - 1; count >= 0; --count) {
		this->insert(collection[count], index);
	}
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::removeAll(T * collection, int elements) {
	int indexes[elements];
	for (int count = 0; count < elements; ++count) {
		indexes[count] = indexOf(collection[count]);
	}
	for (int count = 0; count < elements; ++count) {
		if (indexes[count] != -1) {
			erase(indexes[count]);
		}
	}
	halfCapacity();
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::eraseRange(int start, int end) {
	if (start < 0 || end >= elementsInArray) {
		return;
	}
	if (start >= end) {
		return;
	}
	for (int count = start; count <= end; ++count) {
		erase(start);
	}
	halfCapacity();
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::retainAll(T * collection, int elements) {
	int tempIndexes[elements];
	int numIndexes = 0;
	for (int count = 0; count < elements; ++count) {
		tempIndexes[count] = indexOf(collection[count]);
		if (tempIndexes[count] >= 0) {
			numIndexes++;
		}
	}
	int indexes[numIndexes];
	numIndexes = 0;
	for (int count = 0; count < elements; ++count) {
		if (tempIndexes[count] >= 0) {
			indexes[numIndexes] = tempIndexes[count];
			numIndexes++;
		}
	}
	T * newArray = NULL;
	newArray = new T[numIndexes];
	for (int count = 0; count < numIndexes; ++count) {
		newArray[count] = this->lineList[indexes[count]];
	}
	delete[] lineList;
	this->lineList = newArray;
	this->elementsInArray = numIndexes;
	this->arraySize = numIndexes;
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::swap(int index1, int index2) {
	T temp = lineList[index1];
	lineList[index1] = lineList[index2];
	lineList[index2] = temp;
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::swapObjects(T object1, T object2) {
	int index1 = indexOf(object1);
	int index2 = indexOf(object2);
	if (index1 < 0 || index2 < 0) {
		return;
	}
	T temp = lineList[index1];
	lineList[index1] = lineList[index2];
	lineList[index2] = temp;
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::clear() {
	elementsInArray = 0;
	return;
}

/*
 * Author: Clayton Glenn
 */
template<class T>
void LineList<T>::sort() {
	int ctr = 1, stepBackCTR;
	for (ctr = 1; ctr < elementsInArray; ++ctr) {
		stepBackCTR = ctr;
		insertion(stepBackCTR);
	}
	return;
}

template<class T>
void LineList<T>::insertion(int CTR) {
	if (CTR > 0 && lineList[CTR] < lineList[CTR - 1]) {
		swap(CTR, CTR - 1);
		--CTR;
		insertion(CTR);
	}
	return;
}

#endif /* LINELIST_H_ */
