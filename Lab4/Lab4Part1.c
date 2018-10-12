#include <stdio.h>

int main() {
	//Declaring variables
	int rows, rowNumber, precedingSpaces, spacesBetween, finalRow;
	
	//Retreiving input from user
	printf("Enter the number of rows in the triangle: ");
	scanf("%d", &rows);
	
	//Printing triangle for 1 row
	if (rows == 1) {
		printf("^");
	
	} else {
		//The following for loop build all rows of the triangle except the last one
		for (rowNumber=rows; rowNumber>=2; rowNumber--) {
			//The following for loop prints the spaces before the first '^'
			for (precedingSpaces=1; precedingSpaces<rowNumber; precedingSpaces++) {
				printf(" ");
			}
			//Printing the first '^'
			printf("^");
			
			if (rowNumber == rows) {
				//Goes to second row without printing spaces and '^' if it is the first row
				printf("\n");
			
			} else {
				//The following for loop prints spaces between the two '^'
				for (spacesBetween=1; spacesBetween<((rows-rowNumber)*2); spacesBetween++) {
					printf(" ");
				}
				
				//Printing the second '^'
				printf("^\n");
			}
		}
		
		//The following for loop builds the last row of the triangle
		for (finalRow=1; finalRow<(rows*2); finalRow++) {
			printf("^");
		}
	}	
	printf("\n");
	return 0;
}