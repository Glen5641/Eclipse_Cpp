/*
 * EclipseR2.h
 *
 * Necessary methods for eclipseR2 main function
 *
 *  Created on: Sep 10, 2017
 *      Author: Clayton Glenn
 */

#ifndef ECLIPSER2_H_
#define ECLIPSER2_H_
#include <iostream>
#include <string>

using namespace std;

/**
 * Function used to double the size of an array
 */
string * doubleSize(string *array, int& size) {

	size *= 2;
	string *data = NULL;
	data = new string[size];

	for (int i = 0; i < size; ++i) {
		if (i < (size / 2)) {
			data[i] = array[i];
		} else {
			data[i] = "";
		}
	}

	delete[] array;

	return data;
}

/**
 * Function used to test an array
 * if it has doubled in size
 */
void doubleSizeTest() {
	string *data = NULL;
	int rows = 10;
	data = new string[rows];

	for (int i = 0; i < rows; ++i)
		data[i] = "Hey, ";

	data = doubleSize(data, rows);

	for (int i = 0; i < rows; ++i)
		cout << data[i];

	return;
}

/**
 * Function borrowed from stack overflow and manipulated to fit format
 * to check if string is an integer
 *
 * Author: paercebal & Clayton Glenn
 */
bool isInteger(const std::string & s) {

	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
		return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	if (*p != '\0' || p == s){
			return false;
	}
	return true;
}

/**
 * Function derived from isInteger function from stack overflow
 * to check if string is a double
 *
 * Author: paercebal & Clayton Glenn
 */
bool isDouble(std::string & s) {

	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) {
		return false;
	}

	char* p;
	strtod(s.c_str(), &p);

	if (*p != '\0' || p == s){
		return false;
	}
	return true;
}

#endif /* ECLIPSER2_H_ */
