#include <stdlib.h>
#include <stdio.h>


int getlength(char * str){
	int len=0;
	while(str[len]!='\0'){
		len++;
	}
    return len;
}

void reverseString(char * str){
	int i=0;
	int b=getlength(str);
	char temp[100];
	int a=0;
	for(i=(b-1);i>=0;i--){
		temp[a]=str[i];
		printf("%c   \n ", temp[a]);
		a++;
	}

    temp[b]='\0';
    printf("temp : %s  ");

}


int main(){
	char sample1[]="Here I am";
	reverseString(sample1);


}

