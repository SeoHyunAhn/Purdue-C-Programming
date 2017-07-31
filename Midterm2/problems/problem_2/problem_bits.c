#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Problem (1/4)
/******************************************************************************
 * TODO: Print the bits in bitmap as 0s and 1s
 * 
 * Parameters: bitmap -- print the binary representation of this number
 *
 * Return: void 
 *
 * Return Type: void
 *****************************************************************************/
void printBits(unsigned int bitmap)
{
    int i=31;
    unsigned int tempbit;
    for (; i>=0&&(tempbit=(1<<i)); i--) {
        if (bitmap&tempbit) {
            putchar('1');
        }
        else
            putchar('0');
    }
    printf("\n10987654321098765432109876543210\n");
    // Write Your Code Here 
}


// Problem (2/4)
/******************************************************************************
 * TODO: Set the ith bit in *bitmap with the value in bitValue (0 or 1)
 * 
 * Parameters: bitmap -- unsigned integer
 *	       i -- index of the bit to be changed
 *             bitValue -- change the ith bit to this value
 *
 * Return: void 
 *
 * Return Type: void
 *****************************************************************************/
void setBitAt( unsigned int *bitmap, int i, int bitValue ) 
{
    unsigned int tempbit=(1<<i);
    if (bitValue) {
        *bitmap=((*bitmap)|tempbit);
    }
    else
        *bitmap=((*bitmap)&(~tempbit));
    
    // Write Your Code Here 
}

// Problem (3/4)
/******************************************************************************
 * TODO: Return the bit value (0 or 1) at the ith bit of the bitmap
 * 
 * Parameters: bitmap -- unsigned integer
 *	       i -- index of the bit to be retrieved
 *
 * Return: the ith bit value 
 *
 * Return Type: integer
 *****************************************************************************/
int getBitAt( unsigned int bitmap, unsigned int i) {
    unsigned int tempbit=(1<<i);
    if (tempbit&bitmap){
        return 1;
    }
    else
        return 0;
}

// Problem (4/4)
/******************************************************************************
 * TODO: Return the number of bits with the value 'bitValue'
 *	 If the bitValue is 0, return the number of 0s. If the bitValue is 1,
 *	 return the number of 1s.
 * 
 * Parameters: bitmap -- unsigned integer
 *	       bitValue -- count how many times this number, either 0 or 1,
 *	       appears in bitmap
 *
 * Return: count of 0s or 1s in bitmap 
 *
 * Return Type: integer
 *****************************************************************************/
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

