#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//maxContinuousOnes(unsigned int num, int * position) -- Find the maximum number of consecutive ones bits in num. Set position equal to the start of the sequence where the max number of ones occurs. Return the count of the maximum number of ones in a consecutive sequence.

int maxContinuousOnes(unsigned int num, int * position) {
    int i = 0;
    int k = 0;
    int occur = 0;
    int occurMax = 0;
    char bit[33];
    unsigned int remain = 0;
    unsigned int div = num;
    
    for(i = 0; i < 32 ; i++){
        bit[i] = '0';
    }
    
    bit[32] = '\0';
    i = 0;
    
    while(1){
        
        remain = (div % 2);
        
        if(remain == 1){
            bit[31 - i] = '1';
        }
        
        div = (div / 2);
        
        if(div == 0){
            break;
        }
        
        i++;
    }
    
    printf("%s\n",bit);
    printf("10987654321098765432109876543210\n");
    
    
    
    while(bit[k] != '\0'){
        
        if(bit[k] == '1'){
            
            occur++;
            
            if(occurMax < occur){
                occurMax = occur;
                *position = (k - occur);
            }
            
        }
        else if(bit[k] == '0'){
            occur = 0;
        }
        
        
        k++;
    }
    
    return occurMax;
}

int main(){
    unsigned int sample1=39;
    unsigned int sample2 = 15;
    int pos=1;
    int pos1=0;
    int pos2=4;
    
    printf("%d\n", maxContinuousOnes(sample1, &pos));
    printf("%d\n", maxContinuousOnes(sample1, &pos1));
    printf("%d\n", maxContinuousOnes(sample1, &pos2));
    printf("%d\n", maxContinuousOnes(sample2, &pos1));
    printf("%d\n", maxContinuousOnes(sample2, &pos));


}
