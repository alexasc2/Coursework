#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ROWS		(int)480
#define COLUMNS		(int)640
#define MAX 		(int)255

void clear( unsigned char image[][COLUMNS] );
void header( int row, int col, unsigned char head[32] );

int main( int argc, char **argv )
{

	int				i, j, k, threshold[3], max[3];
	FILE			*fp;
	unsigned char	image[ROWS][COLUMNS], ximage[ROWS][COLUMNS], yimage[ROWS][COLUMNS], head[32];
	char			filename[6][50], ifilename[50], ch;

	//Alex Choi's Variables
	threshold[0] = 101;
	threshold[1] = 25;
	threshold[2] = 51;
	float calcX, calcY, calcSGM;

	strcpy( filename[0], "image1" );
	strcpy( filename[1], "image2" );
	strcpy( filename[2], "image3" );
	header ( ROWS, COLUMNS, head );

	printf( "Maximum of Gx, Gy, SGM\n" );
	for ( k = 0; k < 3; k ++)
	{
		clear( ximage );
		clear( yimage );

		/* Read in the image */
		strcpy( ifilename, filename[k] );
		if (( fp = fopen( strcat(ifilename, ".raw"), "rb" )) == NULL )
		{
		  fprintf( stderr, "error: couldn't open %s\n", ifilename );
		  exit( 1 );
		}			
		for ( i = 0; i < ROWS ; i++ )
		  if ( fread( image[i], sizeof(char), COLUMNS, fp ) != COLUMNS )
		  {
			fprintf( stderr, "error: couldn't read enough stuff\n" );
			exit( 1 );
		  }
		fclose( fp );

		max[0] = 0; //maximum of Gx
		max[1] = 0; //maximum of Gy
		max[2] = 0; //maximum of SGM

		/* Compute Gx, Gy, SGM, find out the maximum and normalize*/
		for(i = 0; i < ROWS; i++){
			for(j = 0; j < COLUMNS; j++){
				if(i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1){
					ximage[i][j] = 0;
					yimage[i][j] = 0;

				}
			}
		}
		
		//start and end within the boundaries of the image for each loop
		//Find MAX Gx and Gy
		for(i = 1; i < ROWS - 1; i++){
			for(j = 1; j < COLUMNS - 1; j++){
				calcX = abs(image[i-1][j-1] 
					+ 2*image[i][j-1] 
					+ image[i+1][j-1] 
					- image[i][j+1] 
					- 2*image[i+1][j+1] 
					- image[i-1][j+1]);

				if(calcX > max[0]){max[0] = calcX;}

				calcY = abs(image[i+1][j-1] 
					+ 2*image[i+1][j]
					+ image[i+1][j+1] 
					- image[i-1][j-1] 
					- 2*image[i-1][j] 
					- image[i-1][j+1]);

				if(calcY > max[1]){max[1] = calcY;}
			}
		}

		//Find SGM
		for(i = 1; i < ROWS - 1; i++){
			for(j = 1; j < COLUMNS - 1; j++){
				calcX = abs(image[i-1][j-1] 
					+ 2*image[i][j-1] 
					+ image[i+1][j-1] 
					- image[i][j+1] 
					- 2*image[i+1][j+1] 
					- image[i-1][j+1]);

				calcY = abs(image[i+1][j-1] 
					+ 2*image[i+1][j]
					+ image[i+1][j+1] 
					- image[i-1][j-1] 
					- 2*image[i-1][j] 
					- image[i-1][j+1]);

				ximage[i][j] = (((float)calcX)/max[0])*MAX;
				yimage[i][j] = (((float)calcY)/max[1])*MAX;
				calcSGM = ximage[i][j]*ximage[i][j]+yimage[i][j]*yimage[i][j];

				if(calcSGM > max[2]){max[2] = calcSGM;}
			}
		}

		//SGM normalization
		for(i = 0; i < ROWS; i++){
			for(j = 0; j < COLUMNS; j++){
				if(i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1){
					image[i][j] = 0;
				}
				calcSGM = ximage[i][j]*ximage[i][j]+yimage[i][j]*yimage[i][j];
				image[i][j] = (((float)calcSGM)/max[2])*255;
			}
		}

		/* Write Gx to a new image*/
		strcpy( ifilename, filename[k] );
		if (!( fp = fopen( strcat( ifilename, "-x.ras" ), "wb" ) ))
		{
		  fprintf( stderr, "error: could not open %s\n", ifilename );
		  exit( 1 );
		}
		fwrite( head, 4, 8, fp );
		
		for( i = 0; i < ROWS; i++){
			fwrite(ximage[i],1,COLUMNS,fp);
		}
		
	    fclose( fp );
					
		/* Write Gy to a new image */
		strcpy( ifilename, filename[k] );
		if (!( fp = fopen( strcat( ifilename, "-y.ras" ), "wb" ) ))
		{
		  fprintf( stderr, "error: could not open %s\n", ifilename );
		  exit( 1 );
		}
		fwrite( head, 4, 8, fp );
	
		for( i = 0; i < ROWS; i++){
			fwrite(yimage[i],1,COLUMNS,fp);
		}
	
		fclose( fp );

		

		/* Write SGM to a new image */
		strcpy( ifilename, filename[k] );
		if (!( fp = fopen( strcat( ifilename, "-s.ras" ), "wb" ) ))
		{
		  fprintf( stderr, "error: could not open %s\n", ifilename );
		  exit( 1 );
		}
		fwrite( head, 4, 8, fp );
	
		for( i = 0; i < ROWS; i++){
			fwrite(image[i],1,COLUMNS,fp);
		}
	
		fclose( fp );
		
		
		/* Compute the binary image */

		for(i = 0; i < ROWS; i++){
			for(j = 0; j < COLUMNS; j++){
				if(image[i][j] >= threshold[k]){image[i][j] = MAX;}
				else{image[i][j] = 0;}
			}
		}
		
		/* Write the binary image to a new image */
		strcpy( ifilename, filename[k] );
		if (!( fp = fopen( strcat( ifilename, "-b.ras" ), "wb" ) ))
		{
		  fprintf( stderr, "error: could not open %s\n", ifilename );
		  exit( 1 );
		}
		fwrite( head, 4, 8, fp );
		for( i = 0; i < ROWS; i++){
			fwrite(image[i],1,COLUMNS,fp);
		}
		fclose( fp );

		printf( "%d %d %d\n", max[0], max[1], max[2] );

	}

	printf( "Press any key to exit: " );
	gets( &ch );
	return 0;
}

void clear( unsigned char image[][COLUMNS] )
{
	int	i,j;
	for ( i = 0 ; i < ROWS ; i++ )
		for ( j = 0 ; j < COLUMNS ; j++ ) image[i][j] = 0;
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
