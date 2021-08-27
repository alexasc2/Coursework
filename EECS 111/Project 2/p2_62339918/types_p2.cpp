#include "types_p2.h"
#include "utils.h"

void Person::set_gender(int data) { gender = data; }
int Person::get_gender(void)      { return gender; }

void Person::set_time(long data) { time_to_stay_ms = data; }
long Person::get_time(void) { return time_to_stay_ms; }
int Person::ready_to_leave(void) {
	struct timeval t_curr;
	gettimeofday(&t_curr, NULL);

	if (get_elasped_time(t_start, t_curr) >= time_to_stay_ms) { return 1; }
	else { return 0; }
}




void Person::start(void) {
	gettimeofday(&t_start, NULL);
	printf("(%lu)th person enters the fittingroom: \n", order);
	printf(" - (%lu) milliseconds after the creation\n", get_elasped_time(t_create, t_start));
}

void Person::complete(void) {
	gettimeofday(&t_end, NULL);
	printf("(%lu)th person comes out of the fittingroom: \n", order);
	printf(" - (%lu) milliseconds after the creation\n", get_elasped_time(t_create, t_end));
	printf(" - (%lu) milliseconds after using the fittingroom\n", get_elasped_time(t_start, t_end));
}

Person::Person() {
	gettimeofday(&t_create, NULL);
}



// You need to use this function to print the Fittingroom's status
void Fittingroom::print_status(void) {
	printf("Print fittingroom status\n");
}


int Fittingroom::man_wants_to_enter(Person& p){
	int r;
	if(status == MENPRESENT || status == EMPTY){
		r = 0;
		//change the fittingroom
		stalls.push_back(p);
		status = MENPRESENT;
		size++;
	}else{
		r = 1;
	}
	return r;
}

void Fittingroom::man_leaves(){
	assert(status != EMPTY);
	struct timeval t_pop, t_i_start;
	gettimeofday(&t_i_start, NULL);

	Person p = stalls.back();
	stalls.pop_back();

	gettimeofday(&t_pop,NULL);
	long q = get_elasped_time(t_i_start,t_pop);

	printf("[%lu ms][Fitting Room] (Man) goes into the fitting room, State is (ManPresent): Total: %lu (Men: %d, Women: %d) \n",q,stalls.size(),size,0);

	usleep(MSEC(p.get_time()));

	gettimeofday(&t_pop,NULL);
	q = get_elasped_time(t_i_start,t_pop);

	size--;
	if(size == 0){
			status = EMPTY;
			printf("[%lu ms][Fitting Room] (Man) left the fitting room, State is (EMPTY): Total: %lu (Men: %d, Women: %d)\n",q,stalls.size(),0,0);
	}else{
		printf("[%lu ms][Fitting Room] (Man) left the fitting room, State is (ManPresent): Total: %lu (Men: %d, Women: %d)\n",q,stalls.size(),size,0);
	}
}

int Fittingroom::woman_wants_to_enter(Person& p){
	int r;
	if(status == WOMENPRESENT || status == EMPTY){
		r = 0;
		//change the fittingroom
		stalls.push_back(p);
		status = WOMENPRESENT;
		size++;
	}else{
		r = 1;
	}
	return r;
}

void Fittingroom::woman_leaves(){
	assert(status != EMPTY);
	struct timeval t_pop, t_i_start;
	gettimeofday(&t_i_start, NULL);

	Person p = stalls.back();
	printf("%lu\n",p.get_time());
	stalls.pop_back();

	gettimeofday(&t_pop,NULL);
	long q = get_elasped_time(t_i_start,t_pop);

	printf("[%lu ms][Fitting Room] (Woman) goes into the fitting room, State is (WomanPresent): Total: %lu (Men: %d, Women: %d) \n",q,stalls.size(),0,size);

	usleep(MSEC(p.get_time()));

	gettimeofday(&t_pop,NULL);
	q = get_elasped_time(t_i_start,t_pop);

	size--;
	if(size == 0){
			status = EMPTY;
			printf("[%lu ms][Fitting Room] (Woman) left the fitting room, State is (EMPTY): Total: %lu (Men: %d, Women: %d)\n",q,stalls.size(),0,0);
	}else{
		printf("[%lu ms][Fitting Room] (Woman) left the fitting room, State is (WomanPresent): Total: %lu (Men: %d, Women: %d)\n",q,stalls.size(),0, size);
	}
}

