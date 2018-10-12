#include <stdio.h>

//Declaring variables
int cents;
int pennies, nickels, dimes, quarters;
int main(void)

{
	//Setting up infinite loop
	while (1) {
		
		//Retreiving input from user
		printf("Please give an amount in cents less than 100: ");
		scanf("%d", &cents);
		printf("%d cents: ", cents);
		
		//Calculating number of each type of coin
		if (cents>=1 && cents<=99) {
			int quarters=0;
			if (cents>=25) {
				quarters = cents/25;
				cents = cents - quarters*25;
			}
			int dimes=0;
			if (cents>=10) {
				dimes = cents/10;
				cents = cents - dimes*10;
			}
			int nickels=0;
			if (cents>=5) {
				nickels = cents/5;
				cents = cents - 5*nickels;
			}
			pennies = cents;
			
			//Creating sentence stating each number of coin
			if (quarters>0) {
				printf("%d quarter", quarters);
				if (quarters>1) {
					printf("s");
				}
				if (dimes>0||nickels>0||pennies>0) {
					printf(", ");
				} else {
					printf(".\n");
				}
			}
			if (dimes>0) {
				printf("%d dime", dimes);
				if (dimes>1) {
					printf("s");
				}
				if (nickels>0||pennies>0) {
					printf(", ");
				} else {
					printf(".\n");
				}
			}
			if (nickels>0) {
				printf("%d nickel", nickels);
				if (nickels>1) {
					printf("s");
				}
				if (pennies>0) {
					printf(", ");
				} else {
					printf(".\n");
				}
			}
			if (pennies>0) {
				printf("%d cent", pennies);
				if (pennies>1) {
					printf("s");
				}
				printf(".\n");
			}
			
		//Ending loop when invalid output provided
		} else {
			printf("Goodbye.\n");
			return 0;
		}
	}
}