#include <stdlib.h>


int computeSum(int numbers[], unsigned int n){
	int i=0;
	int sum=0;
	for(; i<n; i++){
		sum+=numbers[i];
	}
	return sum;
}
