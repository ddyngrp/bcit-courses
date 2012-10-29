#include <iostream>

using std::cout;
using std::endl; 
using std::cin; 

#include "Ctor_Examples.h"

int ctor_ex::obj_count = 0;   // initialize the static member
                              //   declared in the ctor_ex class

ctor_ex::ctor_ex ()
{
	this->intPtr = new int;  // dynamically create an int and have the 
	                         //    member intPtr point to it.
	*(this->intPtr)= 0;      // assign to the int just created dynamically 
	                         //    the int value 0
	cout << "ctor_ex object " << ++ctor_ex::obj_count << " created with ctor_ex::ctor_ex ()\n";
	this->object_no = ctor_ex::obj_count; // so that we know later which object we are destroying.
}

ctor_ex::ctor_ex (int arg1)
{
	this->intPtr = new int;  // dynamically create an int and have the 
	                         //    member intPtr point to it.
	*(this->intPtr)= arg1;   // assign to the int just created dynamically 
	                         //    the int value passed as an argument to this ctor
	cout << "ctor_ex object " << ++ctor_ex::obj_count << " created with ctor_ex::ctor_ex (int )\n";
	this->object_no = ctor_ex::obj_count; // so that we know later which object we are destroying.
}

ctor_ex::ctor_ex (int * iPtr)
{
	this->intPtr = new int;  // dynamically create an int and have the 
	                         //    member intPtr point to it.
	*(this->intPtr)= *iPtr;  // assign to the int just created dynamically 
	                         //    the int value pointed to by the int pointer passed as an argument to this ctor
	cout << "ctor_ex object " << ++ctor_ex::obj_count << " created with ctor_ex::ctor_ex (int *)\n";
	this->object_no = ctor_ex::obj_count; // so that we know later which object we are destroying.
}

// This copy ctor does more than a simple memberwise copy (aka shallow copy),
//     which is why we need to implement a copy ctor for this class.
// The assignment operator should also be overloaded for this class.  We will
//     learn how to do so later in the course.

ctor_ex::ctor_ex (const ctor_ex & obj)
{
	this->intPtr = new int;
    *(this->intPtr)= *(obj.intPtr);
    cout << "ctor_ex object " << ++ctor_ex::obj_count << " created with ctor_ex::ctor_ex (const ctor_ex &)\n";
    this->object_no = ctor_ex::obj_count; // so that we know later which object we are destroying.
}

ctor_ex::~ctor_ex (void)
{
	delete (this->intPtr);  // free up the int dynamically created in one of the ctors
	cout << "ctor_ex object " << this->object_no << " destroyed\n";
}