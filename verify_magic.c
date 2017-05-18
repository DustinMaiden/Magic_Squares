/////////////////////////////////////////////////////////
// Main File:	verify_magic.c
// Semester:	CS 354 Fall 2016 Lecture 001
//
// Author:	Dustin Maiden
// Email	dmaiden@wisc.edu
// CS Login	maiden
//
/////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure representing Square
typedef struct _Square {
	int size;
	int **array;
} Square;


/* Read input from file and Build Potential Magic Square
 * filename - file to read formatted integer matrix
 */ 
void construct_square(char *filename);


/* Verify if integer matrix is a magic square or not
 * square - integer matrix to be checked for magic square
 * Returns an integer denoting if the test is true or false 
 */
int verify_magic(Square * square);


/* xxxxxxx MAIN FUNCTION xxxxxxxxx */ 
int main(int argc, char *argv[])
{
	//error handling - too many and too few CLAs
	if(argc>2){
	printf("Usage : ./generate_magic <filename>\n");
	exit(1);
	}
	if(argc<2){
	printf("Usage : ./generate_magic <filename>\n");
	exit(1);
	}


	// Check input arguments to get filename
	char *ProgramFile=argv[1];
	FILE *m_square = fopen(ProgramFile,"r");

	//If the file can be opened
	//Contruct Square -> Verify Square	
	if(m_square){	
	construct_square(ProgramFile);
	}
	
	// if the file cannot be opened
	else{
	printf("File cannot be opened\n");
	exit(1);	
	}

	return 0;
}


/* construct_square reads the input file to initialize a square struct
// from the contents of the file and then passes this struct to be 
// verified whether it is a magic square or not*/
void construct_square(char *filename)
{
	char *ProgramFile = filename;
	FILE *square = fopen(ProgramFile,"r");
	
	int n;
	int q;
	
	//Begin reading file for matrix size
	fscanf(square,"%d",&n);
//	printf("Number of rows and columns: %i",n);
	
 	// Initialize a new Square struct of that size	
   	Square Square = {n};	
	Square.array=(int **)malloc(n*sizeof(int *));
	
	int i;
	for(i=0; i<n; i++)
		Square.array[i] = (int *)malloc(n*sizeof(int));
	
	//Read formatted integers and create matrix using pointer notation
	int a,b;
	for (a=0; a<n; a++){
          	for (b=0; b<n; b++){	
			fscanf(square,"%d,",&q);
			*(*(Square.array+a)+b)=q;
//			printf(" %d ",*(*(Square.array+a)+b));
			}
		}

	fclose(square);

	//verify the struct just created
	int verify_test =  verify_magic(&Square);
		if(verify_test == 1){
			printf("false\n");
			exit(1);
		}
		else if(verify_test == 2){
			printf("true\n");
		}

	//memory de allocation
	int y;
	for(y=0; y<n; y++)
		free(Square.array[y]);
	free(Square.array);
	
}

// verify_magic verifies if the square is a magic square
// returns 1(true) or 0(false)
// a magic square has the sum of each row equal to the sum of each column
// and equal to the sum of the main and opposite diaganol

int verify_magic(Square * square)
{

	int rows = square->size;

	//a bunch of counters to use to calculate
	// row sums, column sums, and diagonal sums
	// using for loops
	int k;
	int i,j;
	int l,m;
	int o,p;
	int q,r;
	

 	//find magic number
	int magicNum=0;
	for(k=0;k<rows;k++){
		magicNum+= *(*(square->array+0)+k);
	}

	//find sum of each row
	for(i=0;i<rows;i++){
		int tempSum=0;
		for(j=0;j<rows;j++){
			tempSum += *(*(square->array+i)+j);
		}

		if(tempSum == magicNum){
		//the sum of the row equals the magic number	
		}	
		else {	return 1;	
		}
	
	}		
	
	//find sum of each column
	for(l=0;l<rows;l++){
		int tempSum2=0;
		for(m=0;m<rows;m++){
			tempSum2 += *(*(square->array+m)+l);
		}
	
		if(tempSum2 == magicNum){
		//the sum of the column equals the magic number			
		}
		else {return 1;
		}

	}

	// find sum of main diaganol
	int tempSum3 = 0;
	for(o=0;o<rows;o++){	
		for(p=0;p<rows;p++){
			if(o == p){
				tempSum3 += *(*(square->array+o)+p);
			}
		}
	}	

	if(tempSum3 == magicNum){
	//the main diagonal equals the magic number
	}
	else {return 1;
	}

	// Check secondary diagonal
	int tempSum4 = 0;
	for(q=rows-1;q>-1;q--){	
		for(r=rows-1;r>-1;r--){
			if(q == r){
				tempSum4 += *(*(square->array+q)+r);	
			}
		}
	}
	
	if(tempSum4 == magicNum){
	//the opposite diagonal equals the magic number
	}
	else {return 1;
	}

	return 2;
}
