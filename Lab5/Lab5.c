#include <stdio.h>
#include <math.h>

void triangle(double);
double choose(double, double), factorial(double);

int main() {
	double rows;
	//Loop that repeatedly builds triangles until the user inputs a negative value 
	do {
		//Retreiving input from user
		printf("Enter the number of rows: ");
		scanf("%lf", &rows);
		//Using triangle function to build triangle of given number of rows
		if (rows>=0) {
			triangle(rows);
		}
	} while (rows>=0);
	//Terminating program when negative input given
	return 0;
}

//The following function builds a Pascal's triangle with a given number of rows
void triangle (double rows) {
	//For loop builds one row of the triangle during each cycle
	for (double n=0; n<rows; n++) {
		//For loop that prints the number of spaces before the first number of a row
		for (double space=0; space<3*(rows-(n+1)); space++) {
			printf(" ");
		}
		//For loop printing each number of each row one at a time
		for (double r=n; r>=0; r--) {
			double C = choose(n, r);
			printf("%.0lf", C);
			if (r>0) {
				//Printing spaces after each digit (number of spaces is 6-n, where n is number of digits)
				for (double s=0; s<(6-(log10(C)+1)); s++) {
					printf(" ");
				}
			}
		}
		//Going to next row of the triangle
		printf("\n");
	}
}

//The following function chooses r from n
double choose(double n, double r) {
	double C = (factorial(n))/((factorial(r))*(factorial(n-r)));
	return C;
}

//The following function calculates the factorial of a given number
double factorial(double number) {
	if (number==0) {
		number=1;
	} else {
		for (double i=number-1; i>0; i--) {
			number = number*i;
		}
	}
	return number;
}