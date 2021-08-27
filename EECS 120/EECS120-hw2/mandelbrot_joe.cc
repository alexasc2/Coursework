/**
 *  \file mandelbrot_joe.cc
 *
 *  \brief Implement your parallel mandelbrot set in this file.
 */
#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <vector>
#include <string>

#include "render.hh"

using namespace std;

#define ROOT 0
#define RUNS 5

int
mandelbrot(double x, double y) {
  int maxit = 511;
  double cx = x;
  double cy = y;
  double newx, newy;

  int it = 0;
  for (it = 0; it < maxit && (x*x + y*y) < 4; ++it) {
    newx = x*x - y*y + cx;
    newy = 2*x*y + cy;
    x = newx;
    y = newy;
  }
  return it;
}

int
main (int argc, char* argv[])
{
  /* Lucky you, you get to write MPI code */
		int rank, size;
		int height, width;
		double minX = -2.1;
		double maxX = 0.7;
		double minY = -1.25;
		double maxY = 1.25;
		double joe_time = 0.0;

		if (argc == 3) {
			height = atoi (argv[1]);
			width = atoi (argv[2]);
			assert (height > 0 && width > 0);
		} else {
			fprintf (stderr, "usage: %s <height> <width>\n", argv[0]);
			fprintf (stderr, "where <height> and <width> are the dimensions of the image.\n");
			return -1;
		}

		double it = (maxY - minY)/height;
		double jt = (maxX - minX)/width;
		double x, y;

		MPI_Init(&argc,&argv);

		MPI_Comm_size(MPI_COMM_WORLD, &size);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		int process_height = height/size;

		MPI_Barrier(MPI_COMM_WORLD);
		double start_time;
		start_time = MPI_Wtime();

		vector<int> p_img;
		vector<int> joe_img;

		if(rank == ROOT){
			joe_img.resize(width*height);
		}

		y = minY + (rank * process_height) * it;
		for(int i = rank*process_height; i < rank*process_height + process_height; i++){
			x = minX;
			for(int j = 0; j < width; j++){
				p_img.push_back(mandelbrot(x,y));
				x += jt;
			}
			y += it;
		}

		MPI_Gather(&p_img.front(), width*process_height, MPI_INT, &joe_img.front(), width*process_height, MPI_INT, ROOT, MPI_COMM_WORLD);

		joe_time += MPI_Wtime() - start_time;
		MPI_Barrier(MPI_COMM_WORLD);
		if(rank == ROOT){
			printf("Size: %d Joe Time: %f\n", height, joe_time);

			gil::rgb8_image_t img(height, width);
			auto img_view = gil::view(img);

			int count = 0;
		  	for(int i = 0; i < height; i++){
		  		for(int j = 0; j < width; j++){
					img_view(j, i) = render(joe_img[count]/512.0);
					count++;
		  		}
		  	}
		  	string name = "mandelbrot_joe_" + to_string(width) + ".png";
		  	gil::png_write_view(name, const_view(img));
		}

	  	MPI_Finalize();
}

/* eof */
