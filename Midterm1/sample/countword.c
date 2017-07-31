#include <stdlib.h>
#include <stdio.h>

//count number of words in str
int getlength( char * str){
	int i=0;

	while(str[i]!='\0'){
	i++;
	}
return i;
}

unsigned int countWord(char *str, unsigned int length){

	int i=0;
	int strLen=getlength(str);
	int count=0;
	int wordlength=0;
    printf("sample: %s,len:%d\n", str,strLen);
	for(;i<strLen;i++){
		if(str[i]==' '||str[i]=='\n'||str[i]=='\t'||str[i]=='\r'||str[i]=='\0'){
            if(wordlength>0&&(wordlength<=length)){
				count++;
                wordlength=0;
                printf("count:%d\n",count);
                printf("count: %c\n",str[i+1]);
            }
            else{
                wordlength=0;
            }
		}
		else{
			wordlength++;
		}
	}
	return count;
}

int main(){
    char sample[100]="what is the word for censor word function";
    
    int n;
    n= countWord(sample, 4);
    
    printf("sample: %s, number: %d     \n", sample, n);
    return 0;
}
