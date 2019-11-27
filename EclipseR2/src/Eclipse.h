/*
 * Eclipse.h
 *
 * This class creates an Eclipse Object that reads a line
 * into columns through its constructor.
 * It also has private variables that flag the
 * whole object as an err if the is a certain
 * index that has unlikely errs. The object can
 * be printed to the console as a comma delimited line.
 *
 *  Created on: Oct 9, 2017
 *      Author: Clayton Glenn
 */

#ifndef SRC_ECLIPSE_H_
#define SRC_ECLIPSE_H_

#include <iostream>
#include <iomanip>
#include "MonthEnum.h"

using namespace std;

/**
 * ECLIPSE OBJECT
 *
 * This class creates an Eclipse Object that reads
 * a line into columns through its constructor.
 * It also has private variables that flag the
 * whole object as an err if the is a certain
 * index that has unlikely errs. The object can
 * be printed as a columned data file.
 *
 * Author: Clayton Glenn
 */
class Eclipse {
public:

	//Public Member Functions
	Eclipse(std::string line, int& lineNum);
	Eclipse(const Eclipse &e);
	~Eclipse();
	void operator=(const Eclipse &e);
	friend ostream& operator<<(ostream& os, Eclipse* e);

	//Mutator Functions
	void setErr(string line);

	//Accessor Functions
	bool hasErr()const;
	string what() const;
	int getCatNum() const;
	int getCanPlate() const;
	int getYear() const;
	string getMonth() const;
	int getMonthNum()const;
	int getDay()const;
	string getTdOfGreat()const;
	int getDT()const;
	int getLuna()const;
	int getSaros()const;
	string getType()const;
	float getGamma()const;
	float getEclMag()const;
	string getLatitude()const;
	string getLongitude()const;
	int getSunAlt()const;
	int getSunAzm()const;
	int getPathWidth()const;
	string getCentDur()const;

private:

	//Private Variables
	int catNum, canPlate, year, day, dT, luna, saros, sunAlt, sunAzm, pathWidth;
	string tdOfGreat, type, latitude, longitude, centDur, input;
	float gamma, eclMag;
	Month month;

	//char incrementers
	unsigned int cc, start, colCtr;

	//err Handling
	string errLine;

	//Private Helper Method
	void skip_spaces(string line);
	bool isInteger(std::string & s);
	bool isDouble(std::string & s);
	int compareInts();
	int compareStrings();
	int compareDoubles();
};

#endif /* ECLIPSE_H_ */
