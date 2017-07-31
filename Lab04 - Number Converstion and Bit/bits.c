#include <stdio.h>
#include <stdlib.h>


// It prints the bits in bitmap as 0s and 1s.
void printBits(unsigned int bitmap)
{
    int i=31;
    unsigned int tempbit;
    for (; i>=0&&(tempbit=(1<<i)); i--) {
        if(bitmap&tempbit)
            putchar('1');
        else
            putchar('0');
    }
    printf("\n10987654321098765432109876543210\n");
}

// Sets the ith bit in *bitmap with the value in bitValue (0 or 1)
void setBitAt( unsigned int *bitmap, int i, int bitValue ) {
    unsigned int tempbit=(1<<i);
    if (bitValue){
        *bitmap=((*bitmap)|tempbit);
    }else {
        *bitmap=((*bitmap)&(~tempbit));
    }
}

// It returns the bit value (0 or 1) at bit i
int getBitAt( unsigned int bitmap, unsigned int i) {
    unsigned int tempbit=(1<<i);
    if (tempbit&bitmap){
        return 1;
    }
    else
        return 0;
}

// It returns the number of bits with a value "bitValue".
// if bitValue is 0, it returns the number of 0s. If bitValue is 1, it returns the number of 1s.
int countBits( unsigned int bitmap, unsigned int bitValue) {
    unsigned int tempbit;
    int count0=0;
    int count1=0;
    int i=0;
    for(;(i<32)&&(tempbit=(1<<i));i++){
        if(bitmap&tempbit)
            count0++;
        else
            count1++;
    }
    if(bitValue==0)
        return count1;
    else
        return count0;
}

// It returns the number of largest consecutive 1s in "bitmap".
// "*position" is set to the beginning of the sequence.
int maxContinuousOnes(unsigned int bitmap, int * position) {
    int array[100][2];
    int i=0,count=0;
    unsigned int tempbit;
    int j=0;
    for(;(i<32)&&(tempbit=(1<<i));i++){
        if(tempbit&bitmap){
            count++;
        }else{
            if(count>0){
                array[j][0]=count;
                array[j][1]=i-count;
                j++;
            }
            count=0;
        }	
    }
    int max=0;
    i=0;
    for(;i<j;i++)
        if(array[i][0]>array[max][0])
            max=i;
    
    *position=array[max][1];
    
    return array[max][0];
}
