#include "p2_threads.h"
#include "utils.h"

extern pthread_cond_t  cond;
extern pthread_cond_t  cond2;
extern pthread_mutex_t mutex;
extern pthread_mutex_t mutex2;

/*void *threadfunc(void *parm)
{

	int status;
	printf(" [Thread] Start\n");

	printf(" [Thread] Locks\n");
	status = pthread_mutex_lock(&mutex);

    printf(" [Thread] Blocked\n");
    status = pthread_cond_wait(&cond, &mutex);

	printf(" [Thread] Starts again.\n");
	for (int i=0; i<3; i++) {
		printf(" [Thread] Complete thread after (%d) seconds\n", (3-i));
		usleep(MSEC(1000));
	}

	printf(" [Thread] Unlocks\n");
	status = pthread_mutex_unlock(&mutex);
	printf(" [Thread] Complete\n");
}*/

//Adds people to the line and waits for data
void *input(void *arg){
	Args *args = (struct Args *)arg;
	int wCount = args->gender;
	int mCount = args->gender;
	int fRand,waitRand,validPerson;
	long t;

	struct timeval t_push, t_i_start;
	srand(time(0));

	gettimeofday(&t_i_start, NULL);

	do{
		validPerson = 0;
		fRand = rand()%2;
		Person p;

		if(fRand == 1 && wCount != 0){
				waitRand = rand()%5+1;
				wCount--;
				args->wCount2++;
				validPerson = 1;
		}else if(fRand == 0 && mCount != 0){
				waitRand = rand()%5+1;
				mCount--;
				args->mCount2++;
				validPerson = 1;
		}

		if(validPerson == 1){

		//CRITICAL: add person to queue and wait for queue to evaluate
			//LOCK
		pthread_mutex_lock(&mutex);
		p.set_gender(fRand);
		args->line.push_back(p);
		usleep(MSEC(waitRand));

		gettimeofday(&t_push, NULL);

		pthread_cond_signal(&cond);
		args->count1--;
		//UNLOCK
		pthread_mutex_unlock(&mutex);
		t = get_elasped_time(t_i_start,t_push);
		if(fRand == 0){
			printf("[%lu ms][Input] A person (Man) goes into the queue.\n",t);
		}else{
			printf("[%lu ms][Input] A person (Woman) goes into the queue.\n",t);
		}
	}
	}while(args->count1 != 0);
	pthread_exit(NULL);
}

//Manages the line for the fitting room
void *queue(void *arg){
	Args *args = (struct Args *)arg;
	struct timeval t_pop, t_i_start;
	long q;
	gettimeofday(&t_i_start, NULL);
	Fittingroom fRoom = args->fRoom;
	srand(time(0));

	while(args->count2 != 0){
		pthread_mutex_lock(&mutex);
		//wait for input to produce a customer
		while(args->line.size() == 0){
				pthread_cond_wait(&cond,&mutex);
		}
		/*Queue has a customer
		 *Searches for a valid customer and leaves the queue for the stall
		 *Prints the status of the queue
		 */
		for(int i = 0; i < args->line.size(); i++){
			Person p = args->line[i];
			assert(p.get_gender() == 1 || p.get_gender() == 0);
			//printf("TESTLINE %d\n",i);
			if((fRoom.man_wants_to_enter(p) == 0) && p.get_gender() == 0){
				pthread_cond_signal(&cond2);
				p.set_time(rand()%(10-3 + 1)+3);

				args->line.erase(args->line.begin()+i);

				gettimeofday(&t_pop,NULL);
				q = get_elasped_time(t_i_start,t_pop);
				i = args->line.size();
				args->mCount2--;
				args->count2--;
				printf("[%lu ms][Queue] Send (Man) into the fitting room (Stay %lu ms). Total: %lu (Men: %d, Women: %d)\n",q,p.get_time(),args->line.size(),args->mCount2,args->wCount2);
				break;
			}else if((fRoom.woman_wants_to_enter(p) == 0) && p.get_gender() == 1){
				pthread_cond_signal(&cond2);
				p.set_time(rand()%(10-3 + 1)+3);

				args->line.erase(args->line.begin()+i);

				gettimeofday(&t_pop,NULL);
				q = get_elasped_time(t_i_start,t_pop);
				i = args->line.size();
				args->wCount2--;
				args->count2--;
				printf("[%lu ms][Queue] Send (Woman) into the fitting room (Stay %lu ms). Total: %lu (Men: %d, Women: %d)\n",q,p.get_time(),args->line.size(),args->mCount2,args->wCount2);
				break;
			}
		}pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

void *stall(void *arg){
	Args *args = (struct Args *)arg;
	Fittingroom fRoom = args->fRoom;

	while(args->count3 != 0){
		pthread_mutex_lock(&mutex2);
		while(fRoom.stalls.size() == 0){
			pthread_cond_wait(&cond2,&mutex2);
		}
		if(fRoom.status == WOMENPRESENT){
			fRoom.woman_leaves();
			args->count3--;
		}else if (fRoom.status == MENPRESENT){
			fRoom.man_leaves();
			args->count3--;
		}pthread_mutex_lock(&mutex2);
	}
	pthread_exit(NULL);
}