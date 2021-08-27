#ifndef __P1_THREADS
#define __P1_THREADS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <assert.h>
#include <string>
#include <vector>
#include <sys/wait.h>
#include <sys/types.h>
#include <algorithm>
#include <cmath>
#include <new>

#include "p1_process.h"

struct Student{
	std::string ID;
	float GRADE;
};

struct Args{
	int beginning;
	int end;
	Student *student;
};

//thread initial function
void *sorting(void *arg);

//sorts any range of elements
void mergeSort(int beginning, int end, Student *student);

//mergeSort helper
void merge( int beginning, int middle, int end, Student *student);

//statistics using sorted arrays
double average(Student *student);

double median(Student *student);

double stddev(Student *student);

#endif
