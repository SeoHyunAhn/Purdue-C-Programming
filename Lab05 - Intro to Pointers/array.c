
#include <stdio.h>

#include "array.h"

// Return sum of the array
double sumArray(int n, double * array) {
    double sum = 0;
    
    double * p = array;
    double * pend = p+n;
    
    while (p < pend) {
        sum += *p;
        p++;
    }
    
    return sum;
}

// Return maximum element of array
double maxArray(int n, double * array) {
    int i=0;
    double max=*array;
    while (i<max+n) {
        if (max<=*(array+i)) {
            max=*(array+i);
        }
        i++;
    }
    return max;
}

// Return minimum element of array
double minArray(int n, double * array) {
    int i=0;
    double max=*array;
    while (i<max+n) {
        if (max>=*(array+i)) {
            max=*(array+i);
        }
        i++;
    }
    return max;
}

// Find the position int he array of the first element x
// such that min<=x<=max or -1 if no element was found
int findArray(int n, double * array, double min, double max) {
    double *p=array;
    int i=0;
    while (i<12) {
        if (*p>=min && *p<=max) {
            return i;
        }
        p++;
        i++;
    }
    return -1;
}

// Sort array without using [] operator. Use pointers
// Hint: Use a pointer to the current and another to the next element
int sortArray(int n, double * array) {
    int i=0;
    double temp;
    int j;
    for (i=0; i<12; i++){
        for(j=i+1; j<12; j++){
            if (*(array+i)>*(array+j)) {
                temp=*(array+i);
                *(array+i)=*(array+j);
                *(array+j)=temp;
            }
        }
    }
    return 1;
}

// Print array
void printArray(int n, double * array) {
    
    double * p = array;
    double * pend = p+n;
    int i=0;
    while (i < 12) {
        printf("%d:%6f", i, *p);
        printf("\n");
        i++;
        p++;
    }
}

