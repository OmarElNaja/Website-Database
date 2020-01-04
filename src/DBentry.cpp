/* 
 * File:   DBentry.cpp
 * Author: najaomar
 *
 * Created on November 21, 2019, 4:35 PM
 */

#include <iostream>

using namespace std;

#include "DBentry.h"

// The default constructor
DBentry::DBentry()
{
    name = '\0';
    IPaddress = 0;
    active = false;
}

// A constructor that initializes the 3 data members to the given inputs
DBentry::DBentry (string _name, unsigned int _IPaddress, bool _active)
{
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}

// The destructor
DBentry::~DBentry()
{
    
}

// Sets the domain name, which we will use as a key
void DBentry::setName(string _name)
{
    name = _name;
}

// Sets the IPaddress data
void DBentry::setIPaddress(unsigned int _IPaddress)
{
    IPaddress = _IPaddress;
}
    
// Sets whether or not this entry is active
void DBentry::setActive (bool _active)
{
    active = _active;
}

// Returns the name
string DBentry::getName() const
{
    return name;
}

// Returns the IPaddress data
unsigned int DBentry::getIPaddress() const
{
    return IPaddress;
}

// Returns whether or not this entry is active
bool DBentry::getActive() const
{
    return active;
}

// Prints the entry in the format 
// name : IPaddress : active  followed by newline.
// Active is printed as a string (active or inactive).
ostream& operator<< (ostream& out, const DBentry& rhs)
{
    if (rhs.active)
        cout << rhs.name << " : " << rhs.IPaddress << " : active" << endl;
    else
        cout << rhs.name << " : " << rhs.IPaddress << " : inactive" << endl;
}