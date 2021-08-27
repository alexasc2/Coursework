#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include "types_p2.h"
#include "p2_threads.h"
#include "utils.h"


pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
pthread_cond_t  cond2  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
struct timeval t_global_start;

int main(int argc, char** argv)
{
	// This is to set the global start time
	gettimeofday(&t_global_start, NULL);

	int             status = 0;
	int             work = 0;
	int 			join_status = 0;


	Args arg;
	Fittingroom fRoom;
	arg.fRoom = fRoom;
	//argument check
	if(argc == 3 && (atoi(argv[1]) > 0 && atoi(argv[2]) > 0))
	{
			arg.gender = atoi(argv[1]);
			arg.stalls= atoi(argv[2]);
			arg.count1 = arg.gender*2;
			arg.count2 = arg.gender*2;
			arg.count3 = arg.gender*2;
	}else{
		printf("[ERROR] Expecting 2 arguments with integral value greater than zero.\n");
		printf("[USAGE] p1_exec <number of men/women> <number of stalls>\n");

		return 0;
	}

	arg.mCount2 = 0;
	arg.wCount2 = 0;
	pthread_t       tid[2+arg.stalls];

	if(pthread_create(&tid[0], NULL, input, &arg)) {
		fprintf(stderr, "Error creating thread\n");		
	}

	if(pthread_create(&tid[1], NULL, queue, &arg)){
		fprintf(stderr, "Error creating thread\n");		
	}
	
	for(int i = 2; i < arg.stalls+2; i++){
		if(pthread_create(&tid[i], NULL, stall, &arg)) {
			fprintf(stderr, "Error creating thread\n");		
		}
	}


	for(int i = 0; i < arg.stalls+2; i++){
		join_status = pthread_join(tid[i],NULL);
		if(join_status) {
			fprintf(stderr, "Error joining thread\n");	
		}
	}

	/*// Example code for sleep and class usage
	Person p1;
	p1.set_order(1);

	usleep(MSEC(200));
	p1.start();


	usleep(MSEC(150));
	p1.complete();
	///////////////////////////////////////////*/


	/*if(pthread_create(&tid, NULL, threadfunc, NULL)) {
		fprintf(stderr, "Error creating thread\n");		
	}
	usleep(MSEC(10));

	for (int i=0; i<5; i++) {
		printf("Wake up thread after (%d) seconds\n", (5-i));
		usleep(MSEC(1000));
	}

	printf("Wake up thread\n");
	status = pthread_cond_signal(&cond);

	 wait for the second thread to finish 
	if(pthread_join(tid, NULL)) {
		fprintf(stderr, "Error joining thread\n");	
	}

	*/

	return 0;


}

