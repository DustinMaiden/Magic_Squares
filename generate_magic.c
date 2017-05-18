//////////////////////////////////////////
// Main File : generate_magic.c		//
// Semester  : CS 354 Fall 2016 001	//
//					//
// Author    : Dustin Maiden		//
// Email     : dmaiden@wisc.edu		//
// CS Login  : maiden			//
/////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>


// Structure representing Square
// size: dimension(number of rows/columns) of the square
// array: 2D array of integers
typedef struct _Square {
	int size;
	int **array;
} Square;

/* Get function to obtain desired square size from user
 *
 * Returns integer, which is the row and column height  
*/
int get_square_size();

/* generates a magic square 
 *
 * size - the number of rows and columns
 * filename - filename for generating square 
*/
void generate_magic(int size, char *filename);

/* Write the magic square to a file
 *
 * square - magic square to write to file
 * filename - filename to create/edit
 */
void write_to_file(Square * square, char *filename);

/* Main Function
 *
 * 1. Obtain filename to create/edit
 * 2. Obtain size of magic square from user
 * 3. Generate magic square
 * 4. Write square to fil5
 */
int main(int argc, char *argv[])
{

	//error handling - too many and too few CLAs	
        if(argc>2){
        printf("Usage : ./verify_magic <filename>\n");
        exit(1);
        }
        if(argc<2){
        printf("Usage : ./verify_magic <filename>\n");
        exit(1);
        }

	// Check input arguments to get filename
	char *OutputFile=argv[1];
	
	// Get size from user, validate for parameters >=3 and odd
	int size = get_square_size();
	if(size <3 || size%2 ==0){
		printf("Size must be an odd number >= 3.\n");
		exit(1);
	}

	// Generate the magic square	
        generate_magic(size,OutputFile);

	
	return 0;
}

// get_square_size prompts the user for the magic square size
// checks if it is an odd number >= 3 and returns the number
int get_square_size()
{
	int input;
	printf("Enter size of magic square, must be odd \n");
	scanf("%d",&input);
	return input;
}

// generate_magic constructs a magic square of size given from the user
// construction using the Siamese algorithm and returns the Square struct
void generate_magic(int n, char *filename )
{
	char *ProgramFile = filename;
	
	//struct and memory allocation
	Square square = {n};
	square.array=(int **)malloc(n*sizeof(int *));

	int x;
	for (x=0;x<n;x++){
	square.array[x] = (int *)malloc(n*sizeof(int));
	}
	square.size=n;


	int fullsize = n*n; //total # of int's in matrix
	int row = 0;        // start at top row
	int col = n/2;      // start in the middle column
	int index;

	for (index=1; index<=fullsize; ++index){
	//pointer to pointer notation    
	//place integer starting from 1 going to n*n
    		*(*(square.array+col)+row)=index;  
    		row--; // move down a row
    		col++; // move up a col

	//magic squares are easily generated using modular arithmetic
	//to generate the square, when the n-th integer is a mutliple
	// of n, set it at the desired location 
	// utilizing the "up and to the right" method = r-- && col++
		int modulo=index%n;
    		if (modulo == 0) { 
      			row += 2; 
      			-- col; 
    		}
    		else {
			//if you are on the columns edge, need to back up
			if (col == n) 
        		col -= n;
      		else 	//if you are off of the matrix for a row, move to bottom
			if (row < 0) 
        		row += n;
    		}		
  	}


	write_to_file(&square,ProgramFile);
	
	//memory de-allocation
	int y;
	for (y=0;y<n;y++){
		free(square.array[y]);
	}
	free(square.array);


}

// write_to_file opens up a new file(or overwrites the existing file)
// and writes out the square in the format expected by verify_magic.c
void write_to_file(Square * square, char *filename)
{

	char *ProgramFile = filename;
	FILE *output = fopen(ProgramFile,"w");

	//if the file can be opened
	//write magic square to file
	if(output){	

	//write row size (=column size)
	fprintf(output,"%d ", square->size);
	fprintf(output,"\n");
	int n = square->size;	
		
	//print magic square to file
	int a,b;
        for (a=0; a<n; a++){
        	for (b=0; b<n; b++){
        	fprintf(output,"%d", *(*(square->array+a)+b));
        		if(b<n-1)
			fprintf(output,",");     
        	}	
		fprintf(output,"\n");
	}	
	fclose(output);

	}
	else{
	printf("Cannot open file for reading.\n");
	exit(1);
	}
}
