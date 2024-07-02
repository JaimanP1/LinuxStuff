#include<stdio.h>
#define ROWS 5
#define COLUMNS 10

int multi[ROWS][COLUMNS];
 
int main(void){
	int row, col;
	for(row = 0; row < ROWS; row++){
		for(col = 0; col < COLUMNS; col++){
			multi[row][col] = row*col;
		}	
	}
	for(row = 0; row < ROWS; row++){
		for(col = 0; col < COLUMNS; col++){
			printf("\n%d", multi[row][col]);
			printf(", alternate method: ");
			printf("%d", *(*(multi + row) + col));
		}
	}
	return 0;
}
