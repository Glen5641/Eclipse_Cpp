/*
 * EclipseR0.3.h
 *
 * ArrayList Template
 *
 *  Created on: Sep 17, 2017
 *      Author: Clayton Glenn
 */

#ifndef ECLIPSER0_3_H_
#define ECLIPSER0_3_H_

#include <string>

using namespace std;

/**
 * Templated Object ArrayList. Creates a Dynamic Array of any
 * type and Encapsulates the Array in Private Variables, Allowing
 * Mutation and Access of Array through Member Functions.
 *
 * Author: Clayton Glenn
 */
template<class T>
class ArrayList {
public:
	ArrayList();												//Constructor
	ArrayList(int size);										//Constructor
	ArrayList(const ArrayList &array);									//Copy
	~ArrayList();													//Destructor
	friend ostream& operator<<(ostream& os, const ArrayList<string>& al);//Cout Operator

	int getCapacity() const;										//Accessor
	T get(int index) const;											//Accessor
	T * toArray() const;											//Accessor
	int length() const;												//Accessor
	bool contains(T object) const;									//Accessor
	int indexOf(T object) const;									//Accessor
	int lastIndexOf(T object) const;								//Accessor
	string toString() const;										//Accessor

	void add(T object);												//Mutator
	void add(T object, int index);									//Mutator
	void addAll(T * array, int size);								//Mutator
	void set(T object, int index);									//Mutator
	void removeObject(T object);									//Mutator
	void remove(int index);											//Mutator
	void trimToSize();												//Mutator
	void trimToSize(int index);										//Mutator
	void sort();													//Mutator

private:
	T * array;												//Private Variable
	int size;												//Private Variable
	int elementsInArray;									//Private Variable

	void ensureCapacity();									//Helper Function
	void ensureCapacity(int size);							//Helper Function
	void halfCapacity();									//Helper Function
};

/*
 * CONSTRUCTOR: Creates a size 10 arraylist with zero elements
 */
template<class T>
ArrayList<T>::ArrayList() {

	//Initiallize the Private Variables by Default
	this->size = 10;
	this->array = new T[this->size];
	this->elementsInArray = 0;

	//Return to Calling Function
	return;
}

/*
 * CONSTRUCTOR: Creates a user-defined size arraylist with zero elements
 */
template<class T>
ArrayList<T>::ArrayList(int size) {

	//Initiallize the Private Variables by Default Except for a User Declared Size
	this->size = size;
	this->array = new T[this->size];
	this->elementsInArray = 0;

	//Return to Calling Function
	return;
}

/*
 * DESTRUCTOR: Destroys Array in ArrayList
 */
template<class T>
ArrayList<T>::~ArrayList() {

	//Delete the Private Array in the ArrayList
	delete[] this->array;

	//Return to Calling Function
	return;
}

/*
 * COPY CONSTRUCTOR: Copies the data of one ArrayList into this ArrayList
 */
template<class T>
ArrayList<T>::ArrayList(const ArrayList &arrayList) {

	//Copy Data from Another Arraylist Object
	this->array = arrayList.array;
	this->size = arrayList.size;
	this->elementsInArray = arrayList.elementsInArray;

	//Return to Calling Function
	return;
}

/*
 *This function returns the max capacity of the ArrayList
 */
template<class T>
int ArrayList<T>::getCapacity() const {

	//Return Size to Calling Function
	return this->size;
}

/*
 * This function adds an object to the end of the ArrayList
 */
template<class T>
void ArrayList<T>::add(T object) {

	//Check for ArrayList Capacity
	ensureCapacity();

	//Add Object to end of ArrayList and Increment Elements in ArrayList
	this->array[this->elementsInArray] = object;
	this->elementsInArray++;

	//Return to Calling Function
	return;
}

/*
 * This function allows user to add data into any element of arraylist
 */
template<class T>
void ArrayList<T>::add(T object, int index) {

	//Check for ArrayList Capacity
	ensureCapacity();

	//Add Object to User Specified Element of ArrayList and Increment Elements in ArrayList
	for (int count = this->size - 2; count >= index; --count) {
		this->array[index + 1] = this->array[index];
	}
	this->array[index] = object;
	this->elementsInArray++;

	//Return to Calling Function
	return;
}

/*
 * This function allows user to add an array into the ArrayList
 */
template<class T>
void ArrayList<T>::addAll(T * array, int elements) {

	//Check for ArrayList Capacity
	ensureCapacity(elements);

	//Add all the elements of an Array into the End of the ArrayList
	for (int count = this->elementsInArray;
			count < (this->elementsInArray + elements); ++count) {
		this->array[count] = array[count - this->elementsInArray];
	}

	//Increment Elements in ArrayList by Amount Specified by Outer Array
	this->elementsInArray += elements;

	//Return to Calling Function
	return;
}

/*
 * This function cuts the capacity of the ArrayList by half
 */
template<class T>
void ArrayList<T>::halfCapacity() {

	T *newArray = NULL;

	//While Half Elements are needed to Ensure Capacity, Half Size of ArrayList
	while (this->elementsInArray < (this->size / 2 - 1)) {
		this->size /= 2;
		newArray = new T[this->size];

		//Populate the New ArrayList with old ArrayList's Elements
		for (int i = 0; i < this->size; ++i) {
			if (i < (this->size / 2)) {
				newArray[i] = this->array[i];
			}
		}
		//Delete the Old ArrayList and Reinitiallize ArrayList with New
		delete[] this->array;
		this->array = newArray;
	}

	//Return to Calling Function
	return;
}

/*
 * This Function ensures the ArrayList's Capacity, and doubles the size accordingly
 */
template<class T>
void ArrayList<T>::ensureCapacity() {

	T *newArray = NULL;

	//While Elements are needed to Ensure Capacity, Double Size of ArrayList
	while (this->elementsInArray >= this->size - 1) {
		this->size *= 2;
		newArray = new T[this->size];

		//Populate the New ArrayList with old ArrayList's Elements
		for (int i = 0; i < this->size; ++i) {
			if (i < (this->size / 2)) {
				newArray[i] = this->array[i];
			}
		}
		//Delete the Old ArrayList and Reinitiallize ArrayList with New
		delete[] this->array;
		this->array = newArray;
	}

	//Return to Calling Function
	return;
}

/*
 * This Function ensures the ArrayList's Capacity, and doubles the size accordingly
 */
template<class T>
void ArrayList<T>::ensureCapacity(int size) {

	//While Elements are needed to Ensure Capacity, Double Size of ArrayList
	while ((this->elementsInArray + size) >= this->size - 1) {
		this->size *= 2;
		T *newArray = NULL;
		newArray = new T[this->size];

		//Populate the New ArrayList with old ArrayList's Elements
		for (int i = 0; i < this->size; ++i) {
			if (i < (this->size / 2)) {
				newArray[i] = this->array[i];
			}
		}

		//Delete the Old ArrayList and Reinitiallize ArrayList with New
		delete[] this->array;
		this->array = newArray;
	}

	//Return to Calling Function
	return;
}

/*
 * This function returns the Array Data from the ArrayList object
 */
template<class T>
T * ArrayList<T>::toArray() const {

	//Return a Copy of Array in ArrayList to Calling Function
	return this->array;
}

/*
 * This function returns the length of the ArrayList
 */
template<class T>
int ArrayList<T>::length() const {

	//Return a Copy of ElementSize in ArrayList to Calling Function
	return this->elementsInArray;
}

/*
 * This function returns a certain element of the ArrayList's Array
 */
template<class T>
T ArrayList<T>::get(int i) const {

	//Return a Copy of an Object in the Array in ArrayList to Calling Function
	if (i < this->elementsInArray) {
		return this->array[i];
	}

	//Return a Copy of the first Object in the Array in ArrayList to Calling Function if Integer is outside of Size
	return this->array[0];
}

/*
 * This function Deletes an element at a certain position and replaces it with a user element
 */
template<class T>
void ArrayList<T>::set(T object, int index) {

	//Check for ArrayList Capacity
	ensureCapacity();

	//If Index is Within ElementSize, Assign Indexed Element as Object
	if (index < this->elementsInArray) {
		this->array[index] = object;
	}

	//Return to Calling Function
	return;
}

/*
 * This function checks to see if the ArrayList contains a certain element
 */
template<class T>
bool ArrayList<T>::contains(T object) const {

	//Step Through ArrayList and See if it Contains a certain Object
	for (int count = 0; count < this->elementsInArray; ++count) {
		if (this->array[count] == object) {

			//If so, Return True to Calling Function
			return true;
		}
	}

	//If not, Return False to Calling Function
	return false;
}

/*
 * This function checks the index of a certain element
 */
template<class T>
int ArrayList<T>::indexOf(T object) const {

	//Step through ArrayList and Find a Match with User Object
	for (int count = 0; count < this->size; ++count) {
		if (this->array[count] == object) {

			//Return the Index of Matched Object
			return count;
		}
	}

	//If no Object Found, Return -1 Flag
	return -1;
}

/*
 * This function returns the last index of a specified element
 */
template<class T>
int ArrayList<T>::lastIndexOf(T object) const {

	//Step Backward from Behind ArrayList Until Match is Found
	for (int count = this->size - 1; count >= 0; --count) {
		if (this->array[count] == object) {

			//Return the Index of Matched Object
			return count;
		}
	}

	//If no Object Found, Return -1 Flag
	return -1;
}

/*
 * This function removes a certain object in the ArrayList
 */
template<class T>
void ArrayList<T>::removeObject(T object) {

	//Step through ArrayList and Find Certain Object
	for (int count = 0; count < this->size; ++count) {
		if (array[count] == object) {

			//Only if Count is not Size - 1
			if (count != size - 1) {

				//Step through Rest of ArrayList
				for (int ctr = count; ctr < this->size; ++ctr) {

					//Only if Count is not Size - 1
					if (ctr != size - 1) {

						//Step Each Element Back in the ArrayList
						array[ctr] = array[ctr + 1];
					}
				}
			}

			//Decrement Element Size in ArrayList
			elementsInArray--;
		}
	}

	//Return to Calling Function
	return;
}

/*
 * This function removes a certain element in the arrayList
 */
template<class T>
void ArrayList<T>::remove(int index) {

	//Step through ArrayList and BackStep Each Element After Index
	for (int count = index; count < this->size; ++count) {
		if (count < size - 1) {
			array[count] = array[count + 1];
		}
	}

	//Decrement Element Size in ArrayList
	elementsInArray--;

	ArrayList<T>::halfCapacity();
	//Return to Calling Method
	return;
}

/*
 * This function trims the size of the array to perfect the array for the moment
 */
template<class T>
void ArrayList<T>::trimToSize() {

	//Create new Array to Store Data and Trim Size
	T *newArray = NULL;
	size = elementsInArray + 1;
	newArray = new T[size];

	//Copy All Elements of Old Array into New Array
	for (int count = 0; count < this->size; ++count) {
		newArray[count] = array[count];
	}

	//Delete Old Array and Reinitiallize New Array with Old Array
	delete[] this->array;
	array = newArray;

	//Return to Calling Function
	return;
}

/*
 * OverLoaded Function that Decreases Size of Array to Trim Null Values
 *
 * Author: Clayton Glenn
 */
template<class T>
void ArrayList<T>::trimToSize(int size) {

	//Create new Array to Store Data and Trim Size to User Specs
	T *newArray = NULL;
	this->size = size;
	elementsInArray = size - 1;
	newArray = new T[size];

	//Copy All Elements of Old Array into New Array
	for (int count = 0; count < this->size; ++count) {
		newArray[count] = array[count];
	}

	//Delete Old Array and Reinitiallize New Array with Old Array
	delete[] this->array;
	array = newArray;

	//Return to Calling Function
	return;
}

/*
 * Function that Creates a String from Array in ArrayList Template
 *
 * Author: Clayton Glenn
 */
template<class T>
string ArrayList<T>::toString() const {

	//Create a String to store Elements in ArrayList
	std::string line = "";

	//Step Through Each Element in the ArrayList
	for (int i = 0; i < elementsInArray; ++i) {
		line += array[i] + "\n";
	}

	//Return Line String to Calling Function
	return line;
}

/*
 * Incomplete Function that Sorts the Array in the ArrayList Template
 *
 * Author: Clayton Glenn
 */
template<class T>
void ArrayList<T>::sort() {
	return;
}

ostream& operator<<(ostream& os, const ArrayList<string>* al) {
	for (int count = al->length() - 1; count > 0; --count) {
		if (count != 0) {
			os << al->get(count) << endl;
		}
	}
	os << al->get(0);

	return os;
}

#endif /* ECLIPSER0_3_H_ */
