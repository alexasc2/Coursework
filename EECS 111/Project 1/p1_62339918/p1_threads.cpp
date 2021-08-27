#include "p1_threads.h"

// This file includes functions that actually perform the
// computation. You can create a thread with these function
// or directly call this function


/*See header files for function description*/
void *sorting(void *arg){
	Args *args = (struct Args *)arg;

	mergeSort(args->beginning,args->end,args->student);
	return NULL;
}

void mergeSort(int beginning, int end, Student *student){
	int middle = beginning + (end - beginning)/2;
	if(beginning < end){

		mergeSort(beginning,middle,student);
		mergeSort(middle+1,end,student);

		merge(beginning, middle, end, student);
	}
}

void merge( int beginning, int middle, int end, Student *student){
	Student *left = new Student[middle - beginning + 1];
	Student *right = new Student[end - middle];


	for(int i = 0; i < middle - beginning + 1; i++){
		left[i] = student[i + beginning];		
	}

	for(int i = 0; i < end - middle; i++){
		right[i] = student[i + middle + 1];
	}

	int leftCounter = 0; 
	int rightCounter = 0;
	int total = beginning;

	while(leftCounter < middle - beginning + 1 && rightCounter < end - middle){
		if(left[leftCounter].GRADE > right[rightCounter].GRADE){
			student[total] = right[rightCounter];
			rightCounter++;
			total++;
		}else{
			student[total] = left[leftCounter];
			leftCounter++;
			total++;
		}
	}

	while(leftCounter < middle - beginning + 1){
		student[total] = left[leftCounter];
		leftCounter++;
		total++;
	}

	while(rightCounter < end - middle){
		student[total] = right[rightCounter];
		rightCounter++;
		total++;
	}

}

double average(Student *student){
	double sum = 0.0;

	for(int i = 0; i < (int)sizeof(student);i++){
		sum += student[i].GRADE;
	}

	return (float)sum/(sizeof(student));
}

double median(Student *student){

	if(sizeof(student)%2 == 0){
		return (student[(sizeof(student)-1)/2].GRADE + student[sizeof(student)/2].GRADE)/2;
	}
	else{
		return student[sizeof(student)/2].GRADE;
		} 
}

double stddev(Student *student){
	double sum = 0.0;
	double summation;

	for(int i = 0; i < (int)sizeof(student);i++){
		sum += student[i].GRADE;
	}

	double mean = sum/sizeof(student);

	for(int i = 0; i < (int)sizeof(student);i++){
		summation += pow(student[i].GRADE-mean,2);
	}

	double sqrtresult = sqrt(summation/sizeof(student));

	return sqrtresult;
}