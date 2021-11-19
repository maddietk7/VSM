/*
 * Program: binstr2hex.c
 * Purpose: Converts binary to hexadecimal
 * Author:  Maddie TK
 * Date:    10/11/2021
 */
#include <stdio.h>
#include <string.h>

int binstr2hex(char b[]) {
  int i;
  int sum = 0;
  int total = 1;
  for (i = strlen(b) - 1; i >= 0; i--) {
    sum += total*(b[i]-'0');
    total *= 2;
  }
  return sum;
}

int main() {
  char b[17];
  while (scanf("%s\n", b) != EOF) {
    printf("%04x\n", binstr2hex(b)); //prints hex of decimal
  }
}
