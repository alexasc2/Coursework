#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 480
#define COLS 640

void header(int row, int col, unsigned char head[32] );

int main( int argc, char **argv )
{
	int x, y, z_0;
	double p,
		   q,
		   z,
		   lamb,
		   irr,
		   spec,
		   bisector,
		   n1,n2,n3,
		   rep,
		   h1,h2,h3,
		   alpha;
	unsigned char	image[ROWS][COLS],head[32];
	FILE		*fp;

	//source
	double S[9][3] = {
		{0,0,1},
		{1/sqrt(3),1/sqrt(3),1/sqrt(3)},
		{1,0,0},
		{0,0,1},
		{0,0,1},
		{0,0,1},
		{0,0,1},
		{0,0,1},
		{0,0,1}
	};
	//r,a,m variables
	double config[9][3] = {
		{50,0.5,1},
		{50,0.5,1},
		{50,0.5,1},
		{10,0.5,1},
		{100,0.5,1},
		{50,0.1,1},
		{50,1,1},
		{50,0.5,0.1},
		{50,0.5,10000},
	};
	header(ROWS,COLS,head);
	const char *filename[9] = {
		"image1.ras",
		"image2.ras",
		"image3.ras",
		"image4.ras",
		"image5.ras",
		"image6.ras",
		"image7.ras",
		"image8.ras",
		"image9.ras",
	};


	//start file creation
	for(int c = 0; c < 9; c++){
		//image reset
		for(int i = 0; i < ROWS; i++){
			for(int j = 0; j < COLS; j++){
				image[i][j] = 0;
			}
		}


		x = COLS/2;
		y = ROWS/2;
		z_0 = 0;
		bisector = 0;
		for(int i = 0; i < ROWS; i++){
			for(int j = 0; j < COLS; j++){
				rep = config[c][0] * config[c][0] -((j - x)*(j-x) + (i-y)*(i-y));
				if(rep > 0){
					//calc partial deriv
					z = z_0 + sqrt(rep);
					p = -(j-x)/(z-z_0);
					q = (i-y)/(z-z_0);

					//calc normals
					n1 = -p/sqrt(p*p+q*q+1);
					n2 = -q/sqrt(p*p+q*q+1);
					n3 = 1/sqrt(p*p+q*q+1);

					lamb = (n1 * S[c][0]) + (n2 * S[c][1]) + (n3 * S[c][2]);
					if(lamb >= 0){
						bisector = sqrt(S[c][0]*S[c][0] + S[c][1]*S[c][1] + (1+S[c][2])*(1+S[c][2]));

						h1 = S[c][0]/bisector;
						h2 = S[c][1]/bisector;
						h3 = (1+S[c][2])/bisector;
						alpha = acos(n1*h1+n2*h2+n3*h3);
						spec = exp(-(alpha/config[c][2])*(alpha/config[c][2]));
						irr = config[c][1]*lamb + (1-config[c][1])*spec;

						image[i][j] = irr*255;
					}
				}
			}
		}



		if (!( fp = fopen( filename[c], "wb" ) ))
		{
		  fprintf( stderr, "error: could not open \n");
		  exit( 1 );
		}
		fwrite(head,4,8,fp);
		for (int i = 0 ; i < ROWS ; i++ )
		  fwrite( image[i], sizeof(char), COLS, fp );
		fclose( fp );
	}

	return 0;
}

void header( int row, int col, unsigned char head[32] )
{
	int *p = (int *)head;
	char *ch;
	int num = row * col;

	/* Choose little-endian or big-endian header depending on the machine. Don't modify this */
	/* Little-endian for PC */
	
	*p = 0x956aa659;
	*(p + 3) = 0x08000000;
	*(p + 5) = 0x01000000;
	*(p + 6) = 0x0;
	*(p + 7) = 0xf8000000;

	ch = (char*)&col;
	head[7] = *ch;
	ch ++; 
	head[6] = *ch;
	ch ++;
	head[5] = *ch;
	ch ++;
	head[4] = *ch;

	ch = (char*)&row;
	head[11] = *ch;
	ch ++; 
	head[10] = *ch;
	ch ++;
	head[9] = *ch;
	ch ++;
	head[8] = *ch;
	
	ch = (char*)&num;
	head[19] = *ch;
	ch ++; 
	head[18] = *ch;
	ch ++;
	head[17] = *ch;
	ch ++;
	head[16] = *ch;
	

	/* Big-endian for unix */
	/*
	*p = 0x59a66a95;
	*(p + 1) = col;
	*(p + 2) = row;
	*(p + 3) = 0x8;
	*(p + 4) = num;
	*(p + 5) = 0x1;
	*(p + 6) = 0x0;
	*(p + 7) = 0xf8;
*/
}
