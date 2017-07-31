#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//char * mstrcat( char * dest, char * src) -- It will malloc a new block of enough size and store in it the concatenation of src and dest. The old dest will also be freed, so it is assumed that dest was allocated with malloc or strdup before calling mstrcat. Mstrcat will return the new block with the concatenation of dest and src.

char * mstrcat( char * dest, char * src){
    char * str=dest;
    while(*dest) dest++;
    while((*dest++=*src++)!='\0');
    return str;
}
int main(){
    char sample1[10]="a bannana";
    char sample2[10]="is good";
    
    printf("%s", mstrcat(sample1, sample2));
    return 0;


}
