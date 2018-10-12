#include <stdio.h>
#include <math.h>

//Declaring functions for conversions
double convertDecimalToBinary(double);
double convertBinaryToDecimal(double);

int main() {
	//Declaring variables
	double input, output;
	char command;
	
	//Retreiving command for which conversion to make
	printf("Enter B for conversion of Binary to Decimal, OR Enter D for conversion of Decimal to Binary: ");
	scanf(" %c", &command);
	
	if (command == 'B') {
		//Retreiving input from user
		printf("Enter your number: ");
		scanf("%lf", &input);
		//Converting from binary to decimal using function and stating output
		output = convertBinaryToDecimal(input);
		printf("%.0lf in binary = %.0lf in decimal\n", input, output);
	}
	
	else if (command == 'D') {
		//Retreiving input from user
		printf("Enter your number: ");
		scanf("%lf", &input);
		//Converting from decimal to binary using function and stating output
		output = convertDecimalToBinary(input);
		printf("%.0lf in decimal = %.0lf in binary\n", input, output);
	
	//Error statement if invalid input is given
	} else {
		printf("Enter your number: Invalid input; Goodbye\n");
	}
	return 0;
}

//The following function can be used to convert a given binary number into the corresponding decimal number
double convertBinaryToDecimal(double input) {
	//Declaring variables
	double result;
	double remainder;
	double power;
	for (result=0, power=0; input>0; power++) {
		remainder = input%((double) 10);
		input = input/10;
		result = result + remainder*(pow(2, power));
	}
	return result;
}

//The following function can be used to convert a given decimal number into the corresponding binary number
double convertDecimalToBinary(double input) {
	double power;
	double result;
	double remainder;
	//For loop that divides given input by 10 each time
	//Takes remainder and multiplies it by a greater power of 10 each time, adding to the previous result
	//These remainders add up to create a binary number corresponding to the decimal number
	for (result=0, power=0; input>0; power++) {
		remainder = (input%2);
		input = input/2;
		result = (pow(10, power))*remainder + result;
	}
	return result;
}