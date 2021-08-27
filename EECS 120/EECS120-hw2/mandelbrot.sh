#!/bin/bash
#$ -N Mandelbrot
#$ -q class,class16
#$ -pe mpi 64
#$ -R y

# Grid Engine Notes:
# -----------------
# 1) Use "-R y" to request job reservation otherwise single 1-core jobs
#    may prevent this multicore MPI job from running.   This is called
#    job starvation.

# Module load boost
module load boost/1.57.0

# Module load OpenMPI
module load mpich-3.0.4/gcc-4.8.3

# Run the program
for i in {1..3}; do
	mpirun -np 32 ./mandelbrot_joe 8000 8000;
	mpirun -np 32 ./mandelbrot_susie 8000 8000;
	mpirun -np 48 ./mandelbrot_joe 8000 8000;
	mpirun -np 48 ./mandelbrot_susie 8000 8000;
	mpirun -np 64 ./mandelbrot_joe 8000 8000;
	mpirun -np 64 ./mandelbrot_susie 8000 8000;
done
