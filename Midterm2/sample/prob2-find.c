#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


/*int length(unsigned int x){
    unsigned bits;
    unsigned var = (x < 0) ? -x : x;
    for(bits = 0; var != 0; ++bits) var >>= 1;
    return
}
*/
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

//find_sequence (unsigned int num, unsigned int pattern) returns the index of the first occurence the bit ‘pattern’ is found in num. e.g. the bits in num = 10010 and pattern = 1001 should return 1 because the pattern was found at index 1 in num

unsigned int find_sequence (unsigned int num, unsigned int pattern){
    int numberOfBits = floor(log2(num));
    unsigned int tempbit=0;
    int i=0;
    unsigned int temp=num;
    unsigned int mask=~tempbit;
    
    for (; i<32; i++) {
        num=(temp>>i);
       // printBits(mask&num);
        if (mask&num==pattern) {
            //printf("%d@@\n", pattern);
            return i;
        }
    }
    return 0;

//when using '^', if they are same '0' comes up. If one of them is different '1' comes up. When it becomes '0', if it is same with sequence, it is the same pattern.
//make 1111 maske --> right shift num, and use & to check if it is the same pattern
}
    
int main(){
    printBits(10);
    printBits(5);
    printf("%d\n", find_sequence(10, 5));
    printf("\n");
    printBits(12);
    printBits(6);
    printf("%d", find_sequence(12, 6));
    printf("\n");
    printBits(48);
    printBits(50);
    printf("%d", find_sequence(48, 50));
    printf("\n");
    printBits(23);
    printBits(11);
    printf("%d", find_sequence(23, 11));
    printf("\n");
    
    
    
    
    
    
    return 0;
}
