#include <stdlib.h>


//Find Max value

int findMax(int numbers[], unsigned int n){
	int max=numbers[0];
	int i=0;
	for(; i<n; i++){
		if(max<numbers[i])
			max=numbers[i];
	}
	return max;
}
