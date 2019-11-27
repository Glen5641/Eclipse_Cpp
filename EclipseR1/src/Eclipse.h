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
#include <ostream>
#include <iomanip>
#include <string>
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
 */
class Eclipse {
public:

	//Public Member Functions
	Eclipse(std::string line, int& lineNum);
	Eclipse(const Eclipse &e);
	~Eclipse();
	void operator=(const Eclipse &e);
	friend ostream& operator<<(ostream& os, Eclipse* e) {

		if (!e->hasErr()) {
			if (e->getType().at(0) == 'P') {
				os << setw(5) << std::right << e->getCatNum() << setw(5)
						<< e->getCanPlate() << setw(7) << e->getYear()
						<< setw(4) << e->getMonth() << setw(3) << e->getDay()
						<< setw(10) << e->getTdOfGreat() << setw(7)
						<< e->getDT() << setw(7) << e->getLuna() << setw(5)
						<< e->getSaros() << setw(4) << e->getType() << setw(10)
						<< e->getGamma() << setw(8) << e->getEclMag() << setw(7)
						<< e->getLatitude() << setw(7) << e->getLongitude()
						<< setw(4) << e->getSunAlt() << setw(5)
						<< e->getSunAzm() << endl;
			} else {
				os << setw(5) << std::right << e->getCatNum() << setw(5)
						<< e->getCanPlate() << setw(7) << e->getYear()
						<< setw(4) << e->getMonth() << setw(3) << e->getDay()
						<< setw(10) << e->getTdOfGreat() << setw(7)
						<< e->getDT() << setw(7) << e->getLuna() << setw(5)
						<< e->getSaros() << setw(4) << e->getType() << setw(10)
						<< e->getGamma() << setw(8) << e->getEclMag() << setw(7)
						<< e->getLatitude() << setw(7) << e->getLongitude()
						<< setw(4) << e->getSunAlt() << setw(5)
						<< e->getSunAzm() << setw(5) << e->getPathWidth()
						<< setw(8) << e->getCentDur() << endl;
			}
		}

		return os;
	}

	//Mutator Functions
	void setErr(string line);
	bool hasErr();
	string what();

	//Accessor Functions
	int getCatNum();
	int getCanPlate();
	int getYear();
	string getMonth();
	int getMonthNum();
	int getDay();
	string getTdOfGreat();
	int getDT();
	int getLuna();
	int getSaros();
	string getType();
	float getGamma();
	float getEclMag();
	string getLatitude();
	string getLongitude();
	int getSunAlt();
	int getSunAzm();
	int getPathWidth();
	string getCentDur();

private:

	//Private Enum
	enum Month {
		OTH = 0,
		JAN = 1,
		FEB = 2,
		MAR = 3,
		APR = 4,
		MAY = 5,
		JUN = 6,
		JUL = 7,
		AUG = 8,
		SEP = 9,
		OCT = 10,
		NOV = 11,
		DEC = 12
	};

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

#endif /* SRC_ECLIPSE_H_ */
