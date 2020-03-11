#include <stdio.h>
#include <stdlib.h>

char* float32_to_ASCII(unsigned int);
int itoa(int, char *);
int digitPlaces(float);
int digitLength(unsigned int);

int main() {
	unsigned int valueToConvert = 0b11000000100001110110111111010010;//some IEEE-574 integer goes here
	char *finalStringValue = NULL;
	
	finalStringValue = float32_to_ASCII(valueToConvert);

	printf("This is the string equivalent to the IEE-754 value entered: %s \n", finalStringValue);

	free(finalStringValue);

  return 0;
}

int itoa(int number, char *string) {

	int i = 0;
	int remainder = 0;
	int arrayFront = 0;
	int arrayEnd = 0;
	int tempOne = 0;
	int tempTwo = 0;


	if(number == 0) {

		string[i] = '0';
		string[++i] = '\0';

		return 0;
	}


	if(number < 0 ) {

		string[i++] = '-';
		number = number*(-1);
	}

	while(number != 0) {

		remainder = number % 10;
		string[i++] = remainder + '0';
		number = number / 10;
	}

	arrayEnd = i-1;
	if(string[arrayFront] == '-')
		arrayFront++;
		
	while(arrayFront < arrayEnd) {
		tempOne = string[arrayFront];
		tempTwo = string[arrayEnd];

		string[arrayFront++] = tempTwo;
		string[arrayEnd--] = tempOne;

	}

	string[i] = '\0'; 

    return 0;
}

char* float32_to_ASCII(unsigned int ieee32Value)
{
	
	float mantissaFloat = 0;
	int exponent = 0;
	int signedBit = 0;
	float finalValue = 0;
	int integerSide= 0;
	int decimalSide = 0;
	int numberPlaces = 0;
	int numberLeftSideLength = 0;
	int numberRightSideLength = 0;
	int totalNumberLength = 0;
	char *integerStringBuffer = NULL;
	char *decimalStringBuffer =  NULL;
	char *finalValueString = NULL;
	int bufferPosition = 0;
	char singleCharacter[1] = {};
	float tempValue = 0.0;
	int bufferPostionTwo = 0;
	
	signedBit =  ((1 << 1) - 1) & (ieee32Value >> (32 - 1));

	if(signedBit == 0)
	signedBit = 1;
	else if(1)
	signedBit = -1;
	else
	exit(EXIT_FAILURE);

	exponent = ((1 << 8) - 1) & (ieee32Value >> (24 - 1));

	exponent = exponent - 127;

	for(int i = 23; i >= 0; i--) {
	float value = 1;
	int bit = ((1 << 1) - 1) & (ieee32Value >> (i - 1));

	if(bit == 1) {
	  for(int x = 0; x<= 23-i; x++) {
		value /= 2;
	  }
	}

	if(value < 1)
	  mantissaFloat += value; 
	}

	finalValue = signedBit*(mantissaFloat + 1);    

	if(exponent > 0) {

		for(int i = exponent; i > 0; i--) {
			finalValue = finalValue*2;
		}

	} else {
		
		exponent *= -1;
		for(int i = exponent; i > 0; i--) {
			finalValue = finalValue/2;
		}	

	}
	
	if(finalValue >= 0)
	{
		integerSide = finalValue;
		tempValue = (finalValue - integerSide);
		numberPlaces = digitPlaces(tempValue);
		tempValue *= numberPlaces;
		decimalSide = tempValue;
	}
	else
	{
		integerSide = finalValue;
		tempValue = (finalValue - integerSide) * -1;
		numberPlaces = digitPlaces(tempValue);
		tempValue *= numberPlaces;
		decimalSide = tempValue;
	}
	
	numberRightSideLength = digitLength(decimalSide);
	numberLeftSideLength = digitLength(integerSide) + 1;
	totalNumberLength = numberRightSideLength + numberLeftSideLength + 2;

	finalValueString = (char *)malloc(sizeof(char) * totalNumberLength);
	integerStringBuffer = (char *)malloc(sizeof(char) * numberLeftSideLength);
	decimalStringBuffer = (char *)malloc(sizeof(char) * numberRightSideLength);

	itoa(integerSide, integerStringBuffer);
	itoa(decimalSide, decimalStringBuffer);

	while(((singleCharacter[0] = integerStringBuffer[bufferPosition]) != '\0'))
		finalValueString[bufferPosition++] = singleCharacter[0];
	
	finalValueString[bufferPosition++] = '.';

	while(((singleCharacter[0] = decimalStringBuffer[bufferPostionTwo++]) != '\0'))
		finalValueString[bufferPosition++] = singleCharacter[0];

	finalValueString[bufferPosition] = '\0';

	free(integerStringBuffer);
	free(decimalStringBuffer);

	return finalValueString;
}

int digitPlaces(float in)
{									
	int count = 1;
	int compare = 1;
	float compareTwo = 0;

	if (in == 0) return 0;

	while (!(compare == compareTwo)) {

		count = count*10;
		compare = in * count;
		compareTwo = in * count;

	}

	return count;
}

int digitLength(unsigned int in)
{									
	int count = 0;
	if (in == 0) return 0;
	while (in != 0) 
	{
		in /= 10;
		count++;
	}
	return count;
}
