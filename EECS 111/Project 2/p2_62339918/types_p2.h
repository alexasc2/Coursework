#ifndef __TYPES_P2_H
#define __TYPES_P2_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <queue>
#include <assert.h>

#define EMPTY        0
#define WOMENPRESENT 1
#define MENPRESENT   2
#define FULL 3

class Person
{

	int gender; // 0: male 1: female
	std::string str_gender;
	struct timeval t_create;
	struct timeval t_start;
	struct timeval t_end;
	long time_to_stay_ms;


	unsigned long order;
	unsigned long use_order;

public:
	Person();

	void set_gender(int data);
	int get_gender(void);

	void set_time(long data);
	long get_time(void);
	int ready_to_leave(void);

	void start(void);
	void complete(void);
};


// Class for the fittingroom
// You may need to add more class member variables and functions
class Fittingroom {
	// You need to define the data structure to
    // save the information of people using the fittingroom
	// You can probebly use Standard Template Library (STL) vector


public:
	int status,mCount3, wCount3,size;
	std::vector<Person> stalls;
	Fittingroom(){
		status = EMPTY;
		size = 0;
	}

	// You need to use this function to print the Fittingroom's status
	void print_status(void);

	// Call by reference
	// This is just an example. You can implement any function you need
	void add_person(Person& p);

	int man_wants_to_enter(Person& p);

	void man_leaves();

	int woman_wants_to_enter(Person& p);

	void woman_leaves();
};


#endif
