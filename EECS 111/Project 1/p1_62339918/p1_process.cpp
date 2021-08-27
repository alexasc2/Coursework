#include "p1_process.h"

void get_statistics(std::string class_name[], int num_processes, int num_threads) {

	// You need to create multiple processes here (each process
	// handles at least one file.)
	
	
	// Each process should use the sort function which you have defined  		
	// in the p1_threads.cpp for multithread sorting of the data. 
	
	// Your code should be able to get the statistics and generate
	// the required outputs for any number of child processes and threads.
	
	/*Pre-fork declarations*/
	std::string inputdir = "input/";
	std::string outputdir = "output/";
	std::string filetype = ".csv";
	std::string sorted = "_sorted";
	std::string stats = "_stats";
	int status;
	/*Forking*/
	for(int i = 0; i < num_processes ; i++){
		//Isolates fork to just 1 fork
		pid_t pid = fork();
		if(pid == 0){
			printf("Child process is created. (pid: %d)\n", getpid());
			/*Divide Files*/
			if((i+1)/(num_processes) == 0){
				//File input
				std::vector<Student> studentinfo;
				std::string filename = inputdir;
				filename.append(class_name[i]);
				filename.append(filetype);
				std::ifstream fin;
				fin.open(filename.c_str());

				//File check
				if(fin.is_open()){
					std::string line;
					getline(fin,line);//first line out
					while(getline(fin,line)){
						std::stringstream s(line);
						std::string value;
						Student newstudent;

						//File parse
						getline(s,value,',');
						newstudent.ID = value.c_str();
						getline(s,value);
						newstudent.GRADE = atof(value.c_str());

						studentinfo.push_back(newstudent);			
					}
				}
				fin.close();

				pthread_t threads[num_threads];
				int studentsize = studentinfo.size();
				int intervals = studentsize/num_threads;
				Student *student = new Student[studentsize];

				for(int e = 0; e < studentsize; e++){

						student[e] = studentinfo[e];
				}

				for(int t = 0; t < num_threads; t++){
					Args arg;
					if((t+1) == num_threads){
						arg.beginning = t*intervals;
						arg.end = studentsize-1;
					}else{
						arg.beginning = t*intervals;
						arg.end = (t+1)*intervals-1;
					}
					arg.student = student;
					pthread_create(&threads[t],NULL,sorting,&arg);
				}

				for(int t = 0; t < num_threads; t++){
					pthread_join(threads[t],NULL);
				}
				assert(studentsize > 0);
				merge(0,(studentsize/2-1)/2,studentsize/2-1,student);
				merge(studentsize/2,studentsize/2+(studentsize-1-studentsize/2)/2,studentsize-1,student);
				merge(0,(studentsize-1)/2,studentsize-1,student);

				std::string filename2 = outputdir;
				filename2.append(class_name[i]);
				filename2.append(stats);
				filename2.append(filetype);

				std::ofstream oout;
				oout.open(filename2.c_str());
				oout << "Average,Median,Std. Dev\n";
				oout << average(student) << "," << median(student) << "," << stddev(student) << "\n";

				filename = outputdir;
				filename.append(class_name[i]);
				filename.append(sorted);
				filename.append(filetype);
				std::ofstream oin;
				oin.open(filename.c_str());
				oin << "Rank,Student ID,Grade\n";

				for(int l = studentsize - 1; l >= 0;l--){
						oin << studentsize - l << "," << student[l].ID << "," << student[l].GRADE << "\n";
					}
				oout.close();
				oin.close();
			}
			else{
				for(int j = i; j <= num_processes; j++){
					//File input
				std::vector<Student> studentinfo;
				std::string filename = inputdir;
				filename.append(class_name[i]);
				filename.append(filetype);
				std::ifstream fin;
				fin.open(filename.c_str());
				//File check
				if(fin.is_open()){
					std::string line;
					getline(fin,line);//first line out
					while(getline(fin,line)){
						std::stringstream s(line);
						std::string value;
						Student newstudent;

						//File parse
						getline(s,value,',');
						newstudent.ID = value.c_str();
						getline(s,value);
						newstudent.GRADE = atof(value.c_str());

						studentinfo.push_back(newstudent);			
					}
				}
				fin.close();

				pthread_t threads[num_threads];
				int studentsize = studentinfo.size();
				int intervals = studentsize/num_threads;
				Student *student = new Student[studentsize];

				for(int e = 0; e < studentsize; e++){

						student[e] = studentinfo[e];
				}

				for(int t = 0; t < num_threads; t++){
					Args arg;
					if((t+1) == num_threads){
						arg.beginning = t*intervals;
						arg.end = studentsize-1;
					}else{
						arg.beginning = t*intervals;
						arg.end = (t+1)*intervals-1;
					}
					arg.student = student;
					pthread_create(&threads[t],NULL,sorting,&arg);
				}

				for(int t = 0; t < num_threads; t++){
					pthread_join(threads[t],NULL);
				}

				merge(0,(studentsize/2-1)/2,(studentsize/2-1),student);
				merge(studentsize/2,studentsize/2+(studentsize-1-studentsize/2)/2,studentsize-1,student);
				merge(0,(studentsize-1)/2,studentsize-1,student);

				std::string filename2 = outputdir;
				filename2.append(class_name[i]);
				filename2.append(stats);
				filename2.append(filetype);

				std::ofstream oout;
				oout.open(filename2.c_str());
				oout << "Average,Median,Std. Dev\n";
				oout << average(student) << "," << median(student) << "," << stddev(student) << "\n";

				filename = outputdir;
				filename.append(class_name[i]);
				filename.append(sorted);
				filename.append(filetype);
				std::ofstream oin;
				oin.open(filename.c_str());
				oin << "Rank,Student ID,Grade\n";

				for(int l = studentsize - 1; l >= 0;l--){
						oin << studentsize - l << "," << student[l].ID << "," << student[l].GRADE << "\n";
					}
				oout.close();
				oin.close();
				}
			}
			//End Child Work
			printf("Child process is terminated. (pid: %d)\n", getpid());
			exit(0);
		}//end if
	}
	for(int b  = 0; b < num_processes;b++){
		wait(&status);
	}
}

