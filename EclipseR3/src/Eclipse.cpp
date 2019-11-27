/*
 * Eclipse.h
 *
 * This class creates an Eclipse Object that reads a line
 *  into columns through its constructor. It also has private
 *  variables that flag the whole object as an err if the is
 *  a certain index that has unlikely errs. The object can
 *  be printed to the console as a comma delimited line.
 *
 *  Created on: Oct 9, 2017
 *      Author: Clayton Glenn
 */

#include "Eclipse.h"

/*
 * CONSTRUCTOR:
 * Constructor for eclipse object that manipulates a data
 * line into 18 different variables and checks for any
 * possible errors in the data line. These 18 variables
 * are then placed in private variables in the Eclipse Object.
 *
 * Author: Clayton Glenn
 */
Eclipse::Eclipse(string line, int& lineCount) {

	//Initiallize all variables in eclipse object just for safety concerns
	colCtr = 0;
	catNum = 0;
	canPlate = 0;
	year = 0;
	month = OTH;
	day = 0;
	tdOfGreat = "";
	dT = 0;
	luna = 0;
	saros = 0;
	type = "";
	gamma = 1.0;
	eclMag = 1.0;
	latitude = "";
	longitude = "";
	sunAlt = 0;
	sunAzm = 0;
	pathWidth = 0;
	centDur = "";
	cc = 0, start = 0;
	errLine = "";
	string word;

	//Check if line is blank get out
	if (line == "") {
		setInvalidLine(lineCount);
		return;
	}

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//CATALOG NUMBER
	catNum = setInt(line.substr(start, cc - start), lineCount);
	if (errLine.length() > 0) {
		return;
	}

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//CANON PLATE
	canPlate = setInt(line.substr(start, cc - start), lineCount);
	if (errLine.length() > 0) {
		return;
	}

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//CALENDAR YEAR
	year = setInt(line.substr(start, cc - start), lineCount);
	if (errLine.length() > 0) {
		return;
	}

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//CALENDAR MONTH
	input = line.substr(start, cc - start);
	if (input == "Jan") {
		month = JAN;
	} else if (input == "Feb") {
		month = FEB;
	} else if (input == "Mar") {
		month = MAR;
	} else if (input == "Apr") {
		month = APR;
	} else if (input == "May") {
		month = MAY;
	} else if (input == "Jun") {
		month = JUN;
	} else if (input == "Jul") {
		month = JUL;
	} else if (input == "Aug") {
		month = AUG;
	} else if (input == "Sep") {
		month = SEP;
	} else if (input == "Oct") {
		month = OCT;
	} else if (input == "Nov") {
		month = NOV;
	} else if (input == "Dec") {
		month = DEC;
	} else {
		month = OTH;
	}

	//Check month if valid
	if (month == 0) {
		errLine = "Error in data row ";
		errLine += to_string(lineCount);
		errLine += ": Column 4 is not a Month";
		return;
	}

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//CALENDAR DAY
	day = setInt(line.substr(start, cc - start), lineCount);
	if (errLine.length() > 0) {
		return;
	}

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//TD OF GREATEST ECLIPSE
	tdOfGreat = line.substr(start, cc - start);

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//DT
	dT = setInt(line.substr(start, cc - start), lineCount);
	if (errLine.length() > 0) {
		return;
	}

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//LUNA NUMBER
	luna = setInt(line.substr(start, cc - start), lineCount);
	if (errLine.length() > 0) {
		return;
	}

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//SAROS
	saros = setInt(line.substr(start, cc - start), lineCount);
	if (errLine.length() > 0) {
		return;
	}

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	type = line.substr(start, cc - start);

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//GAMMA
	gamma = setDouble(line.substr(start, cc - start), lineCount);
	if (errLine.length() > 0) {
		return;
	}

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//ECLIPSE MAGNITUDE
	eclMag = setDouble(line.substr(start, cc - start), lineCount);
	if (errLine.length() > 0) {
		return;
	}

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//LATITUDE
	latitude = line.substr(start, cc - start);

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//LONGITUDE
	longitude = line.substr(start, cc - start);

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//SUN ALTITUDE
	sunAlt = setInt(line.substr(start, cc - start), lineCount);
	if (errLine.length() > 0) {
		return;
	}

	//Skip the spaces in the line or report error if the line is out of range
	try {
		skip_spaces(line);
		colCtr++;
	} catch (out_of_range &oor) {
		setOutOfRange(lineCount);
		return;
	}

	//SUN AZM
	sunAzm = setInt(line.substr(start, cc - start), lineCount);
	if (errLine.length() > 0) {
		return;
	}

	if (type.at(0) != 'P') { //If type is P, then there are 18
		//columns, not 16

		//Skip the spaces in the line or report error if the line is out of range
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			setOutOfRange(lineCount);
			return;
		}

		//PATH WIDTH
		pathWidth = setInt(line.substr(start, cc - start), lineCount);

		//Skip the spaces in the line or report error if the line is out of range
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			setOutOfRange(lineCount);
			return;
		}

		//CENTRAL DURATION
		centDur = line.substr(start, cc - start);

	} else {
		//Column Check
		if (colCtr != 16 && errLine.length() > 0) {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": ";
			errLine += to_string(colCtr + 1);
			errLine += " found. Should be 16";
		}
	}
	return;
}

/*
 * COPY CONSTRUCTOR:
 * Copy Constructor for eclipse object that copies data of one eclipse into 18 different
 * variables of this eclipse.
 *
 * Author: Clayton Glenn
 */
Eclipse::Eclipse(const Eclipse& e) {
	catNum = e.catNum;
	canPlate = e.canPlate;
	year = e.year;
	month = e.month;
	day = e.day;
	tdOfGreat = e.tdOfGreat;
	dT = e.dT;
	luna = e.luna;
	saros = e.saros;
	type = e.type;
	gamma = e.gamma;
	eclMag = e.eclMag;
	latitude = e.latitude;
	longitude = e.longitude;
	sunAlt = e.sunAlt;
	sunAzm = e.sunAzm;
	pathWidth = e.pathWidth;
	centDur = e.centDur;
	colCtr = e.colCtr;
	cc = e.cc;
	start = e.start;
	errLine = e.errLine;
}

/*
 * OPERATOR=:
 * = operator for eclipse object that copies an eclipse's data
 * into the 18 different variables of the eclipse.
 *
 * Author: Clayton Glenn
 */
void Eclipse::operator=(const Eclipse& e) {
	catNum = e.catNum;
	canPlate = e.canPlate;
	year = e.year;
	month = e.month;
	day = e.day;
	tdOfGreat = e.tdOfGreat;
	dT = e.dT;
	luna = e.luna;
	saros = e.saros;
	type = e.type;
	gamma = e.gamma;
	eclMag = e.eclMag;
	latitude = e.latitude;
	longitude = e.longitude;
	sunAlt = e.sunAlt;
	sunAzm = e.sunAzm;
	pathWidth = e.pathWidth;
	centDur = e.centDur;
	colCtr = e.colCtr;
	cc = e.cc;
	start = e.start;
	errLine = e.errLine;
}

/*
 * OPERATOR<<:
 * Function that returns an ostream object full of an
 * eclipses information in the form of a readable string.
 *
 * Author: Clayton Glenn
 */
std::ostream& operator<<(ostream& os, Eclipse* e) {

	if (!e->hasErr()) {
		if (e->getType().at(0) == 'P') {
			os << setw(5) << std::right << e->getCatNum() << setw(5)
					<< e->getCanPlate() << setw(7) << e->getYear() << setw(4)
					<< e->getMonth() << setw(3) << e->getDay() << setw(10)
					<< e->getTdOfGreat() << setw(7) << e->getDT() << setw(7)
					<< e->getLuna() << setw(5) << e->getSaros() << setw(4)
					<< e->getType() << setw(10) << e->getGamma() << setw(8)
					<< e->getEclMag() << setw(7) << e->getLatitude() << setw(7)
					<< e->getLongitude() << setw(4) << e->getSunAlt() << setw(5)
					<< e->getSunAzm() << endl;
		} else {
			os << setw(5) << std::right << e->getCatNum() << setw(5)
					<< e->getCanPlate() << setw(7) << e->getYear() << setw(4)
					<< e->getMonth() << setw(3) << e->getDay() << setw(10)
					<< e->getTdOfGreat() << setw(7) << e->getDT() << setw(7)
					<< e->getLuna() << setw(5) << e->getSaros() << setw(4)
					<< e->getType() << setw(10) << e->getGamma() << setw(8)
					<< e->getEclMag() << setw(7) << e->getLatitude() << setw(7)
					<< e->getLongitude() << setw(4) << e->getSunAlt() << setw(5)
					<< e->getSunAzm() << setw(5) << e->getPathWidth() << setw(8)
					<< e->getCentDur() << endl;
		}
	}

	return os;
}

bool operator==(Eclipse* e1, Eclipse* e2) {
	if (e1->getCatNum() == e2->getCatNum()) {
		return true;
	}
	return false;
}
bool operator>(Eclipse* e1, Eclipse* e2) {
	if (e1->getCatNum() > e2->getCatNum()) {
		return true;
	}
	return false;
}
bool operator<(Eclipse* e1, Eclipse* e2) {
	if (e1->getCatNum() < e2->getCatNum()) {
		return true;
	}
	return false;
}

/*
 * HASERR:
 * Function that returns a true or false depending
 * on if eclipse has an error
 *
 * Author: Clayton Glenn
 */
bool Eclipse::hasErr() const {
	if (errLine.length() != 0)
		return true;
	else
		return false;
}

/*
 * WHAT:
 * Function that returns this eclipse's Error Line.
 * It is only called if eclipse has an error.
 *
 * Author: Clayton Glenn
 */
string Eclipse::what() const {
	return errLine;
}

/*
 * GETCATNUM:
 * Function that returns this eclipse's cat num
 *
 * Author: Clayton Glenn
 */
int Eclipse::getCatNum() const {
	return catNum;
}

/*
 * GETCANPLATE:
 * Function that returns this eclipse's Can plate
 *
 * Author: Clayton Glenn
 */
int Eclipse::getCanPlate() const {
	return canPlate;
}

/*
 * GETYEAR:
 * Function that returns this eclipse's calendar year
 *
 * Author: Clayton Glenn
 */
int Eclipse::getYear() const {
	return year;
}

/*
 * GETMONTH:
 * Function that returns this eclipse's Month String
 *
 * Author: Clayton Glenn
 */
string Eclipse::getMonth() const {
	switch (month) {
	case 12:
		return "Dec";
	case 11:
		return "Nov";
	case 10:
		return "Oct";
	case 9:
		return "Sep";
	case 8:
		return "Aug";
	case 7:
		return "Jul";
	case 6:
		return "Jun";
	case 5:
		return "May";
	case 4:
		return "Apr";
	case 3:
		return "Mar";
	case 2:
		return "Feb";
	case 1:
		return "Jan";
	default:
		return "";
	}
}

/*
 * GETMONTHNUM:
 * Function that returns this eclipse's Month Number
 *
 * Author: Clayton Glenn
 */
int Eclipse::getMonthNum() const {
	switch (month) {
	case 12:
		return 12;
	case 11:
		return 11;
	case 10:
		return 10;
	case 9:
		return 9;
	case 8:
		return 8;
	case 7:
		return 7;
	case 6:
		return 6;
	case 5:
		return 5;
	case 4:
		return 4;
	case 3:
		return 3;
	case 2:
		return 2;
	case 1:
		return 1;
	default:
		return 0;
	}
}

/*
 * GETDAY:
 * Function that returns this eclipse's Day
 *
 * Author: Clayton Glenn
 */
int Eclipse::getDay() const {
	return day;
}

/*
 * GETTDOFGREAT:
 * Function that returns this eclipse's TdOfGreat
 *
 * Author: Clayton Glenn
 */
string Eclipse::getTdOfGreat() const {
	return tdOfGreat;
}

/*
 * GETDT:
 * Function that returns this eclipse's dT
 *
 * Author: Clayton Glenn
 */
int Eclipse::getDT() const {
	return dT;
}

/*
 * GETLUNA:
 * Function that returns this eclipse's Luna
 *
 * Author: Clayton Glenn
 */
int Eclipse::getLuna() const {
	return luna;
}

/*
 * GETSAROS:
 * Function that returns this eclipse's Saros
 *
 * Author: Clayton Glenn
 */
int Eclipse::getSaros() const {
	return saros;
}

/*
 * GETTYPE:
 * Function that returns this eclipse's Type
 *
 * Author: Clayton Glenn
 */
string Eclipse::getType() const {
	return type;
}

/*
 * GETGAMMA:
 * Function that returns this eclipse's Gamma
 *
 * Author: Clayton Glenn
 */
float Eclipse::getGamma() const {
	return gamma;
}

/*
 * GETECLMAG:
 * Function that returns this eclipse's Eclipse Magnitude
 *
 * Author: Clayton Glenn
 */
float Eclipse::getEclMag() const {
	return eclMag;
}

/*
 * GETLATITUDE:
 * Function that returns this eclipse's Latitude
 *
 * Author: Clayton Glenn
 */
string Eclipse::getLatitude() const {
	return latitude;
}

/*
 * GETLONGITUDE:
 * Function that returns this eclipse's Longitude
 *
 * Author: Clayton Glenn
 */
string Eclipse::getLongitude() const {
	return longitude;
}

/*
 * GETSUNALT:
 * Function that returns this eclipse's Sun alt
 *
 * Author: Clayton Glenn
 */
int Eclipse::getSunAlt() const {
	return sunAlt;
}

/*
 * GETSUNAZM:
 * Function that returns this eclipse's Sun Azm
 *
 * Author: Clayton Glenn
 */
int Eclipse::getSunAzm() const {
	return sunAzm;
}

/*
 * GETPATHWIDTH:
 * Function that returns this eclipse's Path Width
 *
 * Author: Clayton Glenn
 */
int Eclipse::getPathWidth() const {
	return pathWidth;
}

/*
 * GETCENTDUR:
 * Function that returns this eclipse's Cent dur
 *
 * Author: Clayton Glenn
 */
string Eclipse::getCentDur() const {
	return centDur;
}

/*
 * SETERR:
 * Function that Set the error line of the eclipse
 *
 * Author: Clayton Glenn
 */
void Eclipse::setErr(string line) {
	errLine = line;
}

/*
 * SKIP_SPACES:
 * Function that skips the spaces of the data line
 * that has all information to be stored in the eclipse.
 *
 * Author: Clayton Glenn
 */
void Eclipse::skip_spaces(string line) {
	while (isspace(line.at(cc)) && cc < line.length()) {
		cc++;
	}
	start = cc;
	while (cc < line.length()) {
		if (isspace(line.at(cc))) {
			break;
		} else {
			cc++;
		}
	}
}

/*
 * ISINTEGER:
 * Function that returns True if string is integer
 *
 * Author: Clayton Glenn
 */
bool Eclipse::isInteger(std::string & s) {

//If quick fails, get out quick
	if (s.empty()
			|| ((!isdigit(s[0])) && (s[0] != '-' && s.length() == 1)
					&& (s[0] != '+')))
		return false;

//If only 0, return true
	if (s[0] == '0' && s.length() == 1) {
		return true;
	}

//pull numbers out of string
	char * p;
	strtol(s.c_str(), &p, 10);

//If non numbers detected, return false
	if (*p != '\0' || p == s) {
		return false;
	}

//Default, return true to main
	return true;
}

/*
 * GETDOUBLE:
 * Function that returns true if string is a double
 *
 * Author: Clayton Glenn
 */
bool Eclipse::isDouble(std::string & s) {

//If quick fails, get out quick
	if (s.empty()
			|| ((!isdigit(s[0])) && (s[0] != '-' && s.length() == 1)
					&& (s[0] != '+')))
		return false;

//If only 0, return true
	if (s[0] == '0' && s.length() == 1) {
		return true;
	}

//Pull numbers and decimals out of string
	char* p;
	strtod(s.c_str(), &p);

//If non numbers detected, return false
	if (*p != '\0' || p == s) {
		return false;
	}

//Default, return true to main
	return true;
}

/*
 * SETINTEGER:
 * Takes a word and converts it to an integer
 * and returns the integer to the calling function
 *
 * Author: Clayton Glenn
 */
int Eclipse::setInt(string word, int lineCount) {
	if (isInteger(word)) {
		char * p;
		return strtol(word.c_str(), &p, 10);
	} else {
		errLine = "Error in data row ";
		errLine += to_string(lineCount);
		errLine += ": Column ";
		errLine += to_string(colCtr);
		errLine += " is not a Whole Number";
	}
	return -1;
}

/*
 * SETDOUBLE:
 * Takes a word and converts it to a double
 * and returns the double to the calling function
 *
 * Author: Clayton Glenn
 */
float Eclipse::setDouble(string word, int lineCount) {
	if (isDouble(word)) {
		char * p;
		return strtod(word.c_str(), &p);;
	} else {
		errLine = "Error in data row ";
		errLine += to_string(lineCount);
		errLine += ": Column ";
		errLine += to_string(colCtr);
		errLine += " is not a Decimal Number";
	}
	return -1.0;
}

/*
 * SETINVALIDLINE:
 * Function that sets the errorline with an
 * invalid line message for display to the user
 *
 * Author: Clayton Glenn
 */
void Eclipse::setInvalidLine(int lineCount) {
	errLine = "Error in data row ";
	errLine += to_string(lineCount);
	errLine += ": ";
	errLine += "Invalid Line";
}

/*
 * SETOUTOFRANGE:
 * Function that sets the errorline with an out
 * of range message for display to the user
 *
 * Author: Clayton Glenn
 */
void Eclipse::setOutOfRange(int lineCount) {
	errLine = "Error in data row ";
	errLine += to_string(lineCount);
	errLine += ": Out of Range with Column ";
	errLine += to_string(colCtr);
}
