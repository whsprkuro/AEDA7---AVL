/*
 * dni.cpp
 *
 *  Created on: 11 may. 2018
 *      Author: mad18
 */

#include "dni.hpp"

DNI::DNI(){ //valor aleatorio entre 0 y 99999999
	numdni = "";

	for (int i = 0; i < 8; ++i){ //coge cada número del DNI y le da un valor aleatorio entre 0 y 9
		int n = rand() % 10;

		ostringstream convert;
		convert << n;
		numdni += convert.str();
	}
}

DNI::~DNI(){
	destroy();
}

void DNI::destroy(){
	numdni.erase(numdni.begin(), numdni.end());
}

bool DNI::operator ==(DNI &d){
	return numdni.compare(d.get_numDNI()) == 0;
}

bool DNI::operator !=(DNI &d){
	return numdni.compare(d.get_numDNI()) != 0;
}

bool DNI::operator <(DNI &d){
	return numdni.compare(d.get_numDNI()) < 0;
}

bool DNI::operator >(DNI &d){
	return numdni.compare(d.get_numDNI()) > 0;
}

bool DNI::operator <=(DNI &d){
	return numdni.compare(d.get_numDNI()) <= 0;
}

bool DNI::operator >=(DNI &d){
	return numdni.compare(d.get_numDNI()) >= 0;
}

ostream& operator<<(ostream& os, const DNI& dni){
    return os << dni.numdni;
}

istream& operator>>(istream& is, DNI& dni){
	return is >> dni.numdni;
}

string DNI::get_numDNI(){
	return numdni;
}

void DNI::set_numDNI(string d){
	numdni = d;
}
