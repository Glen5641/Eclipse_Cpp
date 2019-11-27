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

#include <string>
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
	friend bool operator==(Eclipse* e1, Eclipse* e2);
	friend bool operator>(Eclipse* e1, Eclipse* e2);
	friend bool operator<(Eclipse* e1, Eclipse* e2);

	//Accessor Functions
	bool hasErr() const;
	string what() const;
	int getCatNum() const;
	int getCanPlate() const;
	int getYear() const;
	string getMonth() const;
	int getMonthNum() const;
	int getDay() const;
	string getTdOfGreat() const;
	int getDT() const;
	int getLuna() const;
	int getSaros() const;
	string getType() const;
	float getGamma() const;
	float getEclMag() const;
	string getLatitude() const;
	string getLongitude() const;
	int getSunAlt() const;
	int getSunAzm() const;
	int getPathWidth() const;
	string getCentDur() const;

	//Mutator Functions
	void setErr(string line);

private:

	//Private Helper Method
	void skip_spaces(string line);
	bool isInteger(std::string & s);
	bool isDouble(std::string & s);
	int setInt(string word, int lineCount);
	string setString(string word, int lineCount);
	float setDouble(string word, int lineCount);
	void setInvalidLine(int lineCount);
	void setOutOfRange(int lineCount);

	//Private Variables
	int catNum, canPlate, year, day, dT, luna, saros, sunAlt, sunAzm, pathWidth;
	string tdOfGreat, type, latitude, longitude, centDur, input;
	float gamma, eclMag;
	Month month;

	//char incrementers
	unsigned int cc, start, colCtr;

	//err Handling
	string errLine;
};

#endif /* ECLIPSE_H_ */
