#ifndef __P2_THREADS_H
#define __P2_THREADS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <vector>
#include "types_p2.h"
#include <assert.h>

struct Args{
	int gender;
	int stalls;
	std::vector<Person> line;
	int count1; //Input thread counter
	int count2; //Queue thread counter
	int count3; //Stall threads counter
	int wCount2;
	int mCount2;
	Fittingroom fRoom;
};

/*class Args{
	public:
		int gender;
		int stalls;
		std::vector<Person> line;
		int count;
		struct timeval& t_global_start;
		Fittingroom fRoom;
		Args();
};*/

void *threadfunc(void *parm);

void *input(void *arg);

void *queue(void *arg);

void *stall(void *arg);

#endif
