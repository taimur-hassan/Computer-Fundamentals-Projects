#include <stdio.h>

int main(void) {
	
	const char k='k', K='K', b='b', B='B', r='r', R='R', o='o', O='O', e='e', E='E', g='g', G='G', u='u', U='U', v='v', V='V', y='y', Y='Y';
	const char w='w', W='W', l='l', L='L', s='s', S='S';
	char firstBand, secondBand, multiplierBand, toleranceBand;
	int band1, band2, bandsOneAndTwo;
	double multiplier, resistance, tolerance, finalResistance;
	
	//Retreiving input for bands from user
	printf("Please enter the 1st band: \n");
	scanf(" %c", &firstBand);
	printf("Please enter the 2nd band: \n");
	scanf(" %c", &secondBand);
	printf("Please enter the multiplier band: \n");
	scanf(" %c", &multiplierBand);
	printf("Please enter the tolerance band: \n");
	scanf(" %c", &toleranceBand);
	
	//Determining value for first band (and stating colour of first band)
	if (firstBand==k||firstBand==K) {
		band1 = 0;
		printf("Resistor bands: Black ");
	} else if(firstBand==b||firstBand==B) {
		band1 = 1;
		printf("Resistor bands: Brown ");
	} else if(firstBand==r||firstBand==R) {
		band1 = 2;
		printf("Resistor bands: Red ");
	} else if(firstBand==o||firstBand==O) {
		band1 = 3;
		printf("Resistor bands: Orange ");
	} else if(firstBand==e||firstBand==E) {
		band1 = 4;
		printf("Resistor bands: Yellow ");
	} else if(firstBand==g||firstBand==G) {
		band1 = 5;
		printf("Resistor bands: Green ");
	} else if(firstBand==u||firstBand==U) {
		band1 = 6;
		printf("Resistor bands: Blue ");
	} else if(firstBand==v||firstBand==V) {
		band1 = 7;
		printf("Resistor bands: Violet ");
	} else if(firstBand==y||firstBand==Y) {
		band1 = 8;
		printf("Resistor bands: Grey ");
	} else if(firstBand==w||firstBand==W) {
		band1 = 9;
		printf("Resistor bands: White ");
	}
	
	//Determining value for second band (and stating colour of second band)
	if (secondBand==k||secondBand==K) {
		band2 = 0;
		printf("Black ");
	} else if(secondBand==b||secondBand==B) {
		band2 = 1;
		printf("Brown ");
	} else if(secondBand==r||secondBand==R) {
		band2 = 2;
		printf("Red ");
	} else if(secondBand==o||secondBand==O) {
		band2 = 3;
		printf("Orange ");
	} else if(secondBand==e||secondBand==E) {
		band2 = 4;
		printf("Yellow ");
	} else if(secondBand==g||secondBand==G) {
		band2 = 5;
		printf("Green ");
	} else if(secondBand==u||secondBand==U) {
		band2 = 6;
		printf("Blue ");
	} else if(secondBand==v||secondBand==V) {
		band2 = 7;
		printf("Violet ");
	} else if(secondBand==y||secondBand==Y) {
		band2 = 8;
		printf("Grey ");
	} else if(secondBand==w||secondBand==W) {
		band2 = 9;
		printf("White ");
	}
	
	//Combining bands one and two to create 2 digit number
	bandsOneAndTwo = (10*band1) + band2;
	
	//Determining multiplier value from multiplier band (and stating colour of multiplier band)
	if (multiplierBand==k||multiplierBand==K) {
		multiplier = 1;
		printf("Black ");
	} else if(multiplierBand==b||multiplierBand==B) {
		multiplier = 10;
		printf("Brown ");
	} else if(multiplierBand==r||multiplierBand==R) {
		multiplier = 100;
		printf("Red ");
	} else if(multiplierBand==o||multiplierBand==O) {
		multiplier = 1000;
		printf("Orange ");
	} else if(multiplierBand==e||multiplierBand==E) {
		multiplier = 10000;
		printf("Yellow ");
	} else if(multiplierBand==g||multiplierBand==G) {
		multiplier = 100000;
		printf("Green ");
	} else if(multiplierBand==u||multiplierBand==U) {
		multiplier = 1000000;
		printf("Blue ");
	} else if(multiplierBand==v||multiplierBand==V) {
		multiplier = 10000000;
		printf("Violet ");
	} else if(multiplierBand==l||multiplierBand==L) {
		multiplier = 0.1;
		printf("Gold ");
	} else if(multiplierBand==s||multiplierBand==S) {
		multiplier = 0.01;
		printf("Silver ");
	}
	
	//Applying multiplier to 2 digit number
	resistance = bandsOneAndTwo * multiplier;
	
	//Determining tolerance value from tolerance band (and stating colour of tolerance band)
	if (toleranceBand==b||toleranceBand==B) {
		tolerance = 1;
		printf("Brown\n");
	} else if (toleranceBand==r||toleranceBand==R) {
		tolerance = 2;
		printf("Red\n");
	} else if (toleranceBand==g||toleranceBand==G) {
		tolerance = 0.5;
		printf("Green\n");
	} else if (toleranceBand==u||toleranceBand==U) {
		tolerance = 0.25;
		printf("Blue\n");
	} else if (toleranceBand==v||toleranceBand==V) {
		tolerance = 0.10;
		printf("Violet\n");
	} else if (toleranceBand==y||toleranceBand==Y) {
		tolerance = 0.05;
		printf("Yellow\n");
	} else if (toleranceBand==l||toleranceBand==L) {
		tolerance = 5;
		printf("Gold\n");
	} else if (toleranceBand==s||toleranceBand==S) {
		tolerance = 10;
		printf("Silver\n");
	}
	
	//Converting Ohms KOhms/Mohms (if necessary) and stating resistance value
	if (resistance<1000) {
		printf ("Resistance: %.2lf Ohms +/- %.2lf%%", resistance, tolerance);
	} else if (resistance>=1000&&resistance<1000000) {
		finalResistance = resistance/1000;
		printf ("Resistance: %.2lf KOhms +/- %.2lf%%", finalResistance, tolerance);
	} else if (resistance>=1000000) {
		finalResistance = resistance/1000000;
		printf ("Resistance: %.2lf MOhms +/- %.2lf%%", finalResistance, tolerance);
	}
	
	return 0;
}