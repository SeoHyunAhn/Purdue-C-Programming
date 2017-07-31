#include <stdlib.h>

//Find min value
int findMin(int numbers[], unsigned int n){
	int i=0;
	int min=numbers[0];

	for(; i<n; i++){
		if(min>numbers[i])
			min=numbers[i];
	}
	return min;
}
