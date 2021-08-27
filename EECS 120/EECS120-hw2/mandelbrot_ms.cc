/**
 *  \file mandelbrot_ms.cc
 *
 *  \brief Implement your parallel mandelbrot set in this file.
 */

#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <vector>
#include <string>

#include "render.hh"

#define TAG 0
#define ENDTAG 1
#define ROOT 0

using namespace std;

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
	int rank, size;
	int height, width;
	double minX = -2.1;
	double maxX = 0.7;
	double minY = -1.25;
	double maxY = 1.25;
	double time = 0.0;

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
	int ms_img[height][width];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	int end = 0;
	int flag = 0;

	MPI_Barrier(MPI_COMM_WORLD);
	double start_time;
	start_time = MPI_Wtime();


	//master process
	if(rank == ROOT){
		int height_count = 0;
		int count;
		int end_tag;
		MPI_Request request;

		//p_status records the row the process is using
		vector<int> p_status(size, 0);

		while(height_count != height){
			//loop through cores
			for(int i = 1; i < size; i++){
				MPI_Iprobe(i, TAG, MPI_COMM_WORLD, &flag, &status);

				MPI_Get_count(&status, MPI_INT, &count);

				if(count != width && p_status[i] == 0){
					if(height_count != height){
						MPI_Isend(&height_count, 1, MPI_INT, i, TAG, MPI_COMM_WORLD, &request);
						height_count++;
					}
					p_status[i] = height_count;
				}else if(count == width && p_status[i] != 0){
					int row[width];

					MPI_Recv(&row, width, MPI_INT, i, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

					for(int j = 0; j < width; j++){
						ms_img[p_status[i]][j] = row[j];
					}
					p_status[i] = 0;

					if(height_count != height){
						MPI_Isend(&height_count, 1, MPI_INT, i, TAG, MPI_COMM_WORLD, &request);
						height_count++;
					}
				}
			}
		}

		for(int i = 1; i < size; i++){
			MPI_Isend(&end_tag, 1, MPI_INT, i, ENDTAG, MPI_COMM_WORLD,&request);
		}
	}
	//slave process
	else{
		y = minY;
		while(!end){
			MPI_Iprobe(0,ENDTAG,MPI_COMM_WORLD,&end,MPI_STATUS_IGNORE);

			if(end != 1){
				MPI_Iprobe(0,TAG,MPI_COMM_WORLD,&flag,MPI_STATUS_IGNORE);

				if(flag){
					int row;
					int send_row[width];
					MPI_Recv(&row, 1, MPI_INT, ROOT, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

					y = it*row;

					for(int j = 0; j < width; j++){
						x = minX;
						send_row[j] = mandelbrot(x,y);
						x += jt;
					}
					MPI_Request request;
					MPI_Isend(&send_row, width, MPI_INT, ROOT, TAG, MPI_COMM_WORLD, &request);
				}
			}
		}
	}

	time += MPI_Wtime() - start_time;
	MPI_Barrier(MPI_COMM_WORLD);

	if(rank == ROOT){
			printf("Size: %d MS Time: %f\n", height, time);

			gil::rgb8_image_t img(height, width);
			auto img_view = gil::view(img);

		  	for(int i = 0; i < height; i++){
		  		for(int j = 0; j < width; j++){
					img_view(j, i) = render(ms_img[i][j]/512.0);
		  		}
		  	}
		  	string name = "mandelbrot_joe_" + to_string(width) + ".png";
		  	gil::png_write_view(name, const_view(img));
		}

	MPI_Finalize();
}

/* eof */
