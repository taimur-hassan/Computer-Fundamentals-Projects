#include <stdio.h>

//Declaring variables
double input1, input2, result;
const char a='a', s='s', m='m', d='d';
char command;

int main(void) {

		//Retrieving inputs from user
		printf("Enter first number: ");
		scanf("%lf", &input1);
		
		printf("Enter second number: ");
		scanf("%lf", &input2);
		
		printf("Enter calculation command (one of a, s, m, or d): ");
		scanf(" %c", &command);
		
		if (command == a || command == s || command == m || command == d) {
			//Adding when addition command provided
			if (command == a) {
				result = input1 + input2;
				printf("Sum of %.2lf and %.2lf is %.2lf\n", input1, input2, result);
			}
			//Subtracting when subtraction command provided
			if (command == s) {
				result = input1 - input2;
				printf("Difference of %.2lf from %.2lf is %.2lf\n", input1, input2, result);
			}
			//Multiplying when multiplication command provided
			if (command == m) {
				result = input1 * input2;
				printf("Product of %.2lf and %.2lf is %.2lf\n", input1, input2, result);
			}
			//Dividing when division command provided
			if (command == d) {
				if (input2!=0) {
					result = input1 / input2;
					printf("Division of %.2lf by %.2lf is %.2lf\n", input1, input2, result);
				//Displaying error code when divisor is zero
				} else {
					printf("Error, trying to divide by zero\n");
				}
			}
		//Displaying error message when invalid commmand is provided
		} else {
			printf("Error, unknown calculation command given\n");
		}
}