#include <stdlib.h>
#include <stdio.h>
/*
Given a string of 1’s and 0’s, construct a new string that is the 1’s complement of str, and return that string. The 1’s complement is obtained by inverting all the bits in the binary representation of the number (swapping 0s for 1s and vice versa)
*/
char *firstComplement(const char *str){
	int length=5;
	int i=0;
    
    char new[length];

	for(;i<length-1;i++){
		if(str[i]=='0')
			new[i]='1';
		else
			new[i]='0';
	}
    new[i] = '\0';
    char *forReturn = new;
    
    return forReturn;
}


int main(){
	char result[100];
    const char first[]="0011";
    int i = 0;
    char *getReturn = firstComplement(first);
    while(result[i] != '\0' || getReturn[i] != '\0'){
        result[i] = getReturn[i];
        i++;
    }
    

	printf("result: %s \n", result);
	return 0;
	
}


