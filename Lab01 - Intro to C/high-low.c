#include <stdio.h>
//

int main(int argc, char **argv) {
char finalans='y';
char feedback;
char ch=0;
  printf("Welcome to the High Low game...\n");
do{
int high=100;
int low=1;
int mid;

       printf("Think of a number between 1 and 100 and press <enter>\n");
	char ent=getchar();
	if(ent=='\n'){
	do{
	  mid=(low+high)/2;
	  printf("Is it higher than %d? (y/n)\n", mid);
	  scanf("%c", &feedback);
	getchar();
	  if (feedback!='y' && feedback!='n'){
		printf("Type y or n\n");
	  }
	  else if(feedback=='y'){
		  low=mid+1;
	  }
 	 else if (feedback=='n'){
		high=mid-1;				
	 }
	}while(high>=low);
        printf("\n>>>>>> The number is %d\n", low);
	printf("\nDo you want to continue playing (y/n)?");
	scanf("%c", &finalans);
	getchar();
	}
	}while(finalans=='y');
	if (finalans=='n'){
	printf("Thanks for playing\n");
	}

}
