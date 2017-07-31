#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//inverse_bits ( unsigned int num ) -- invert the bits in the number ex. 1010 should be converted to 0101

unsigned int inverse_bits ( unsigned int num ){
    int count =sizeof(num)*8 -1;
    return ~num;
}


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
    printf("\n");
    // Write Your Code Here
}

int main(){
    unsigned int sample1=1;
    unsigned int sample2=15;
    unsigned int sample3=12;
    unsigned int sample4=4;

    printBits(sample1);
    printBits(inverse_bits(sample1));
    printf("\n");
    printBits(sample2);
    printBits(inverse_bits(sample2));
    printf("\n");
    printBits(sample3);
    printBits(inverse_bits(sample3));
    printf("\n");
    printBits(sample4);
    printBits(inverse_bits(sample4));
    printf("\n");
    
    
    
    
    
    return 0;
}
