#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAX_DIGITS 32

// Problem (1/2)
/*****************************************************************************
 * TODO: convert a number from the given base to decimal
 *
 * Parameters: number -- the number you are converting an integer
 *             base   -- the base of the number you are given
 * 
 * Return: The number as an integer
 *
 * Return Type: int
*****************************************************************************/
int toInteger(char * number, int base) {
// Write Your Code Here
    
    int i=0;
    int sum=0;
    int length=strlen(number)-1;
    for (; i<strlen(number); i++) {
        if (number[i]>='A'&&number[i]<='Z') {
            int temp= number[i]-'A'+10;
            
            sum+=temp*pow(base, length);
            //printf("%d@\n", sum);
            length-=1;
        }
        else{
        sum+=(number[i]-'0')*pow(base, length);
            //printf("%d\n", sum);
            length-=1;
        }
    }
    
	return sum;
}

// Problem (2/2)
/*****************************************************************************
 * TODO: convert a number from the given base to decimal
 *
 * Parameters: number -- the number you are converting a string
 *             base   -- the base you are converting the numebr to
 * 
 * Return: The number as a string in base "base"
 *
 * Return Type: char *
*****************************************************************************/
char * toBase(int number, int base) {
    int array[MAX_DIGITS];
    int temp=0, i=0;
    //char final[MAX_DIGITS];
    char *final = (char*)malloc(sizeof(char) * MAX_DIGITS);
    while (number!=0) {
        temp=number%base;
        array[i] = temp;
        i++;
        number=number/base;
    }
    
    int a=0, count=i-1;
    for (; i>0; i--) {
        final[a]=array[i-1];
      //  printf("final[%d] = %d   (i - 1) = %d\n",a, final[a],i - 1);
        a++;
    }
    
    int j=0;
    while(j<=count){
        if (final[j]>9) {
            final[j]=final[j]-10+'A';
        }
        else if(final[j]>=0&&final[j]<10){
            final[j]+=48;
        }
        j++;
    }
    final[j]='\0';
    
	return final;
}
