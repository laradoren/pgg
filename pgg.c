//This program allows you to calculate the system 
//of linear equations using the Gaussian method.
//Program by Нalushko Alina Vasylivna

#include <stdio.h>
#include <stdlib.h>

int input (int width, int height, int a[][height], int b[width]);
int matrix (int width, int height, int a[][height], int b[width], float major[][height+1]);
int output (int width, int height, float major[][height+1], float x[width]);
int triangle (int width, int height, float major[][height+1], float x[width]);
int compat (int width, int height, float major[][height+1], float x[width]);
int gauss (int width, int height, float major[][height+1], float x[width]);
int ranga (int width, int height, float major[][height+1]);
int rangb (int width, int height, float major[][height+1]);
	
int main () {
	const int width  = 5;
	const int height = 5;
	float major[width][height+1];
	int a[width][height];
	int b[width];
	float x[width];
	
	input (width, height, a, b);	
	matrix (width, height, a, b, major);
	triangle (width, height, major, x);
	compat (width, height, major, x);
	
	return 0;
}

//A function that receives the values of coefficients and free members from the keyboard

int input (int width, int height, int a[][height], int b[width]) {
	printf("Please enter the coefficients:\n");
	for ( int i = 0; i < height; i++){
		for( int j = 0; j < width; j++){
			scanf("%d", &a[i][j]);	
		}
	}
	printf("Please enter the free members:\n");
	for ( int i = 0; i < height; i++){
		scanf("%d", &b[i]);
	}
	
	return 0;
}

//The function that forms the main matrix

int matrix (int width, int height, int a[][height], int b[width], float major[][height+1]) {
	for ( int i = 0; i < width; i++){
		for ( int j = 0; j < height; j++){
			major[i][j]=a[i][j];
		}
	}
  for ( int i = 0; i < width; i++){
		major[i][height] = b[i];
	}
	
	return 0;
}

//The function that prints the roots of the equation

int output (int width, int height, float major[][height+1], float x[width]) {
	for( int i = 0; i < width; i++){
		printf( "x%d= %4.2f ", i+1, x[i]);
	}
	
	return 0;
}

//A function that transforms a matrix to a triangular type

int triangle (int width, int height, float major[][height+1], float x[width]) {
	float k;
	for( int m = 1; m < width; m++){
		for ( int i = 0; i < width-m; i++){	
			k = major[i+m][m-1] / major[m-1][m-1];
			for( int j = 0; j < height + 1; j++){
				major[i+m][j+m-1] = major[i+m][j+m-1] - major[m-1][j+m-1]*k;	
			}
		}
	}	
		
	return 0;
}

//The function that verifies the Kronecker-Capelli theorem

int compat (int width, int height, float major[][height+1], float x[width]) {
	if( ranga(width, height, major) == rangb(width, height, major) && rangb(width, height, major)) {
		if( ranga(width, height, major) == rangb(width, height, major) && rangb(width, height, major) < width){
			printf("System is uncertain");
		}else{
			gauss(width, height, major, x);
		}
	}else{
		printf("System in not compatible");
	}
		
	return 0;
}

//Functions that find the matrix rank	

int ranga (int width, int height, float major[][height+1]) {
	int ra = width;
	for (int i = width-1; i >= 0; i--){
		if( major[i][height-1] != 0){
			return ra;
		}else{
			ra = ra -1;
		}
	}
	
	return ra;
}

int rangb (int width, int height, float major[][height+1]) {
	int rb = width;
	for ( int i = width-1; i >= 0; i--){
		if (major[i][height] != 0){
			return rb;
		}else{
		rb = rb-1;
		}
	}
	
	return rb;
}

//The function that finds the roots of the equation

int gauss (int width, int height, float major[][height+1], float x[width]) {
	float res = 0;
	x[width-1] = major[width-1][height]/major[width-1][height-1];
	for( int n = height-2; n >= 0; n--){
		for( int i = 0; i < width-1; i++){
			res += x[i+1]*major[n][i+1];
		}
		x[n] = (major[n][height]-res)/major[n][n];
		res = 0;
	}
	output(width, height, major, x);
	
	return 0;
}





