#ifndef __P1_PROCESS
#define __P1_PROCESS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <string>
#include <vector>
#include <sstream>
#include <sys/wait.h>
#include <sys/types.h>
#include <algorithm>

#include "p1_threads.h"

/*Main multiprocessing/multithreading function controller
	-creates child processes connected to the main process (# determined by input)
	-parses data into vector(then to struct array)
	-sorts through multithreading and calculates data
	-rewrites data into new output files
*/
void get_statistics(std::string class_name[], int num_processes, int num_threads);

#endif
