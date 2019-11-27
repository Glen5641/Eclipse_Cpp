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
 * Constructor for eclipse object that manipulates a data
 * line into 18 different variables and checks for any
 * possible errors in the data line
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

	//Check if line is blank
	if (line == "") {
		errLine = "Error in data row ";
		errLine += to_string(lineCount);
		errLine += ": ";
		errLine += "Invalid Line";
	}

	//CATALOG NUMBER - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 1";
			colCtr--;
		}
	}

	//Convert to Integer or set error
	if (errLine.length() == 0) {
		string word = line.substr(start, cc - start);
		if (isInteger(word)) {
			char * p;
			catNum = strtol(word.c_str(), &p, 10);
		} else {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Column 1 is not a Whole Number";
		}
	}

	//CANON PLATE - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 2";
			colCtr--;
		}
	}

	//Convert to Integer or set error
	if (errLine.length() == 0) {
		string word = line.substr(start, cc - start);
		if (isInteger(word)) {
			char * p;
			canPlate = strtol(word.c_str(), &p, 10);
		} else {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Column 2 is not a Whole Number";
		}
	}

	//CALENDAR YEAR - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 3";
			colCtr--;
		}
	}

	//Convert to Integer or set error
	if (errLine.length() == 0) {
		string word = line.substr(start, cc - start);
		if (isInteger(word)) {
			char * p;
			year = strtol(word.c_str(), &p, 10);
		} else {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Column 3 is not a Whole Number";
		}
	}

	//CALENDAR MONTH - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 4";
			colCtr--;
		}
	}

	//Convert to Month or set error
	if (errLine.length() == 0) {
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
		}
	}

	//CALENDAR DAY - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 5";
			colCtr--;
		}
	}

	//Convert to Integer or set error
	if (errLine.length() == 0) {
		string word = line.substr(start, cc - start);
		if (isInteger(word)) {
			char * p;
			day = strtol(word.c_str(), &p, 10);
		} else {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Column 5 is not a Whole Number";
		}
	}

	//TD OF GREATEST ECLIPSE - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 6";
			colCtr--;
		}
	}
	if (errLine.length() == 0) {
		tdOfGreat = line.substr(start, cc - start);
	}

	//DT
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 7";
			colCtr--;
		}
	}

	//Convert to Integer or set error
	if (errLine.length() == 0) {
		string word = line.substr(start, cc - start);
		if (isInteger(word)) {
			char * p;
			dT = strtol(word.c_str(), &p, 10);
		} else {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Column 7 is not a Whole Number";
		}
	}

	//LUNA NUMBER - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 8";
			colCtr--;
		}
	}

	//Convert to Integer or set error
	if (errLine.length() == 0) {
		string word = line.substr(start, cc - start);
		if (isInteger(word)) {
			char * p;
			luna = strtol(word.c_str(), &p, 10);
		} else {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Column 8 is not a Whole Number";
		}
	}

	//SAROS NUMBER - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 9";
			colCtr--;
		}
	}

	//Convert to Integer or set error
	if (errLine.length() == 0) {
		string word = line.substr(start, cc - start);
		if (isInteger(word)) {
			char * p;
			saros = strtol(word.c_str(), &p, 10);
		} else {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Column 9 is not a Whole Number";
		}
	}

	//ECLIPSE TYPE - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 10";
			colCtr--;
		}
	}
	if (errLine.length() == 0) {
		type = line.substr(start, cc - start);
	}

	//GAMMA - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 11";
			colCtr--;
		}
	}

	//Convert to Double or set error
	if (errLine.length() == 0) {
		string word = line.substr(start, cc - start);
		if (isDouble(word)) {
			char * p;
			gamma = strtod(word.c_str(), &p);
		} else {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Column 11 is not a Decimal Number";
		}
	}

	//ECLIPSE MAGNITUDE - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 12";
			colCtr--;
		}
	}

	//Convert to Double or set error
	if (errLine.length() == 0) {
		string word = line.substr(start, cc - start);
		if (isDouble(word)) {
			char * p;
			eclMag = strtod(word.c_str(), &p);
		} else {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Column 12 is not a Decimal Number";
		}
	}

	//LATITUDE - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 13";
			colCtr--;
		}
	}
	if (errLine.length() == 0) {
		latitude = line.substr(start, cc - start);
	}

	//LONGITUDE - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			"Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 14";
			colCtr--;
		}
	}
	if (errLine.length() == 0) {
		longitude = line.substr(start, cc - start);
	}

	//SUN ALTITUDE - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			"Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 15";
			colCtr--;
		}
	}

	//Convert to Integer or set error
	if (errLine.length() == 0) {
		string word = line.substr(start, cc - start);
		if (isInteger(word)) {
			char * p;
			sunAlt = strtol(word.c_str(), &p, 10);
		} else {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Column 15 is not a Whole Number";
		}
	}

	//SUN AZM - get input or set error
	if (errLine.length() == 0) {
		try {
			skip_spaces(line);
			colCtr++;
		} catch (out_of_range &oor) {
			"Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Out of Range with Column 16";
			colCtr--;
		}
	}

	//Convert to Integer or set error
	if (errLine.length() == 0) {
		string word = line.substr(start, cc - start);
		if (isInteger(word)) {
			char * p;
			sunAzm = strtol(word.c_str(), &p, 10);
		} else {
			errLine = "Error in data row ";
			errLine += to_string(lineCount);
			errLine += ": Column 16 is not a Whole Number";
		}
	}

	if (errLine.length() == 0 || errLine == "error") {
		if (type.at(0) != 'P') { //If type is P, then there are 18
			//columns, not 16

			//PATH WIDTH - get input or set error
			if (errLine.length() == 0) {
				try {
					skip_spaces(line);
					colCtr++;
				} catch (out_of_range &oor) {
					"Error in data row ";
					errLine += to_string(lineCount);
					errLine += ": Out of Range with Column 17";
					colCtr--;
				}
			}

			//Convert to Integer or set error
			if (errLine.length() == 0) {
				string word = line.substr(start, cc - start);
				if (isInteger(word)) {
					char * p;
					pathWidth = strtol(word.c_str(), &p, 10);
				} else {
					errLine = "Error in data row ";
					errLine += to_string(lineCount);
					errLine += ": Column 17 is not a Whole Number";
				}
			}

			//CENTRAL DURATION - get input or set error
			if (errLine.length() == 0) {
				try {
					skip_spaces(line);
					colCtr++;
				} catch (out_of_range &oor) {
					"Error in data row ";
					errLine += to_string(lineCount);
					errLine += ": Out of Range with Column 18";
					colCtr--;
				}
			}
			if (errLine.length() == 0) {
				centDur = line.substr(start, cc - start);
				colCtr++;
			}

			//Column Check
			if (colCtr != 18 && errLine == "error") {
				errLine = "Error in data row ";
				errLine += to_string(lineCount);
				errLine += ": ";
				errLine += to_string(colCtr + 1);
				errLine += " found. Should be 18";
			}
		} else {

			//Column Check
			if (colCtr != 16 && errLine == "error") {
				errLine = "Error in data row ";
				errLine += to_string(lineCount);
				errLine += ": ";
				errLine += to_string(colCtr + 1);
				errLine += " found. Should be 16";
			}
		}
	}
}

/*
 * Copy Constructor for eclipse object that copies data into 18 different
 *variables
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
 * = operator for eclipse object that copies data into 18 different variables
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
 * Function that returns a true or false depending on if eclipse has an error
 *
 * Author: Clayton Glenn
 */
bool Eclipse::hasErr() {
	if (errLine.length() != 0)
		return true;
	else
		return false;
}

/*
 * Function that returns cat num
 *
 * Author: Clayton Glenn
 */
int Eclipse::getCatNum() {
	return catNum;
}

/*
 * Function that returns Can plate
 *
 * Author: Clayton Glenn
 */
int Eclipse::getCanPlate() {
	return canPlate;
}

/*
 * Function that returns calendar year
 *
 * Author: Clayton Glenn
 */
int Eclipse::getYear() {
	return year;
}

/*
 * Function that returns Month String
 *
 * Author: Clayton Glenn
 */
string Eclipse::getMonth() {
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
 * Function that returns Month Number
 *
 * Author: Clayton Glenn
 */
int Eclipse::getMonthNum() {
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
 * Function that returns Day
 *
 * Author: Clayton Glenn
 */
int Eclipse::getDay() {
	return day;
}

/*
 * Function that returns TdOfGreat
 *
 * Author: Clayton Glenn
 */
string Eclipse::getTdOfGreat() {
	return tdOfGreat;
}

/*
 * Function that returns dT
 *
 * Author: Clayton Glenn
 */
int Eclipse::getDT() {
	return dT;
}

/*
 * Function that returns Luna
 *
 * Author: Clayton Glenn
 */
int Eclipse::getLuna() {
	return luna;
}

/*
 * Function that returns Saros
 *
 * Author: Clayton Glenn
 */
int Eclipse::getSaros() {
	return saros;
}

/*
 * Function that returns Type
 *
 * Author: Clayton Glenn
 */
string Eclipse::getType() {
	return type;
}

/*
 * Function that returns Gamma
 *
 * Author: Clayton Glenn
 */
float Eclipse::getGamma() {
	return gamma;
}

/*
 * Function that returns Eclipse Magnitude
 *
 * Author: Clayton Glenn
 */
float Eclipse::getEclMag() {
	return eclMag;
}

/*
 * Function that returns Latitude
 *
 * Author: Clayton Glenn
 */
string Eclipse::getLatitude() {
	return latitude;
}

/*
 * Function that returns Longitude
 *
 * Author: Clayton Glenn
 */
string Eclipse::getLongitude() {
	return longitude;
}

/*
 * Function that returns Sun alt
 *
 * Author: Clayton Glenn
 */
int Eclipse::getSunAlt() {
	return sunAlt;
}

/*
 * Function that returns Sun Azm
 *
 * Author: Clayton Glenn
 */
int Eclipse::getSunAzm() {
	return sunAzm;
}

/*
 * Function that returns Path Width
 *
 * Author: Clayton Glenn
 */
int Eclipse::getPathWidth() {
	return pathWidth;
}

/*
 * Function that returns Cent dur
 *
 * Author: Clayton Glenn
 */
string Eclipse::getCentDur() {
	return centDur;
}

/*
 * Function that returns Error Line
 *
 * Author: Clayton Glenn
 */
string Eclipse::what() {
	return errLine;
}

/*
 * Function that Set the error line of the eclipse
 *
 * Author: Clayton Glenn
 */
void Eclipse::setErr(string line) {
	errLine = line;
}

/*
 * Function that skips the spaces of the data line
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
