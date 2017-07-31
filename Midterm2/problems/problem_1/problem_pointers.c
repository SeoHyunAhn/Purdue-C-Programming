#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Problem (1/4)
/******************************************************************************
 * TODO: Print the array.
 *       The format should be (array index)(colon)(array element)(newline) 
 * 
 * Parameters: n -- the number of elements in the array
 *             array -- a double array
 *
 * Return: void 
 *
 * Return Type: void
 *****************************************************************************/
void printArray(int n, double * array) {
// Write Your Code Here
    int i=0;
    while (i<n) {
        printf("%d:%f\n", i, array[i]);
        i++;
    }
}

// Problem (2/4)
/******************************************************************************
 * TODO: Return the minimum element of array 
 * 
 * Parameters: array -- a double array
 *             n -- the number of elements in the array
 *
 * Return: minimum element in array 
 *
 * Return Type: double
 *****************************************************************************/
double minArray(int n, double * array) {
// Write Your Code Here
    double temp=array[0];
    int i;
    for (i=0; i<n; i++) {
        if (array[i]<temp) {
            temp=array[i];
        }
    }
    
	return temp;
}

// Problem ( 3/4 ) 
/******************************************************************************
 * TODO: Reverse the given string 'str'. 
 * E.g. reverse_str("smile") should return "elims"
 * 
 * Parameters: str -- The given string to be reversed.
 *
 * Return: A pointer to str, str should be reversed 
 *
 * Return Type: char pointer
 *****************************************************************************/
char * reverse_str (char * str ) {
    // Write Your Code Here
    
    int n=strlen(str)-1;
    int pop=(n/2)+1;
    char temp;
    int i=0;
    while (i<pop) {
        temp=str[n-i];
        str[n-i]=str[i];
        str[i]=temp;
        i++;
        //printf("%s @@\n\n", str);
    }
    return str;
}

// Problem ( 4/4 ) 
/******************************************************************************
 * TODO: Determine if the string str2 is a permutation of str1. A permutation
 * is the rearranging of characters in a different order. 
 * E.g. the string "act" is a permutation of "cat" 
 *
 * Hint: count the occurences of each letter
 * 
 * Parameters: str1 -- The original string
 *	       str2 -- Determine if this string is a permutation of str1 
 *
 * Return: 1 if str2 is a permutation
 *         0 if str2 is not a permutation
 *
 * Return Type: integer
 *****************************************************************************/
int is_permutation ( char * str1, char * str2 ) {
    // Write Your Code Here
    
    if (strlen(str1)!=strlen(str2)) {
        return 0;
    }
    int flag=0;
    int i=0;
    int j=0;
    for (;i<strlen(str1);i++) {
        for (;j<strlen(str2);j++) {
            if (str2[j]==str1[i]) {
                flag++;
            }
        }
    }
   // printf("%d\n\n", flag);
    if (flag==(strlen(str2)-1) || flag==1) {
        return 1;
    }
    return 0;
}









