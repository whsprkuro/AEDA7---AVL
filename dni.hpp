/*
 * dni.hpp
 *
 *  Created on: 11 may. 2018
 *      Author: mad18
 */

#pragma once

#include <sstream>
#include <iostream>
#include <stdlib.h>     //srand, rand, strtoul

using namespace std;

class DNI{

private:

	string numdni;

public:

	DNI();
	DNI(string s);
	~DNI();
	void destroy();

	bool operator ==(DNI &d);
	bool operator !=(DNI &d);
	bool operator <(DNI &d);
	bool operator >(DNI &d);
	bool operator <=(DNI &d);
	bool operator >=(DNI &d);
	friend ostream& operator<<(ostream& os, const DNI& dni);
	friend istream& operator>>(istream& is, DNI& dni);

	operator unsigned long();

	string get_numDNI();
	void set_numDNI(string d);
	void mostrar();
};
