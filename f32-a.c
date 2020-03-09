#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int decimalPlace(unsigned int);

int main() {
  unsigned int ieee32Value = 0;
  float mantissaFloat = 0;
  int exponent = 0;
  int signedBit = 0;
  float finalValue = 0;

  ieee32Value = 0b11000000010001111110010111111101;

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

  printf("Here is your final value: %f \n", finalValue);

  return 0;

}