/*
 Write a program to convert a given number from one base to another. The format is:
 convert <basefrom> <baseto> <number>
 */

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


int convert(int basefrom, char *number){
    
    int length=strlen(number)-1;
    int i=0;
    int sum=0;
    int a=0;

    for (; length>=0; length--) {
        int forI = (int)number[length]-'0';
        
        if (number[length]>='A' && number[length]<='Z'){
            switch (number[length]) {
                case 'A':
                    sum+=(10)*pow(basefrom, a);
                    break;
                case 'B':
                    sum+=(11)*pow(basefrom, a);
                    break;
                case 'C':
                    sum+=(12)*pow(basefrom, a);
                    break;
                case 'D':
                    sum+=(13)*pow(basefrom, a);
                    break;
                case 'E':
                    sum+=(14)*pow(basefrom, a);
                    break;
                case 'F':
                    sum+=(15)*pow(basefrom, a);
                    break;
                default:
                    break;
            }
        }
        
        else if(forI>=0 && forI<basefrom){
            sum+=forI*pow(basefrom, a);
        }
        else if(forI>basefrom){
            printf("Wrong digit in number.\n");
            exit(1);
        }
        a++;
    }
    return sum;
}

char* back(int baseto, int sum){
    int i=0;
    int array[30];
    char* final = malloc(30);
    int remain=0;
    int cut=0;
    
    
    for(;i<32;i++){
        cut = sum / baseto;
        remain = sum % baseto;
        sum=cut;
        array[i]=remain;
        
        if(cut==0){
            break;
        }
    }
    
    int j=0;
    int count=i;
    
    for( ; i>=0; i--){
            final[j]=array[i];
            j++;
        
    }
    
    j=0;
    while(j<=count){
        if(final[j]>9){
            final[j] = final[j] - 10 + 'A';
        }
        else if(final[j]>=0 && final[j]<10){
            final[j]=final[j]+48;
        }
        j++;
    }
    
    final[j]='\0';
    
    
    return final;
}

/*
 agrv의 1칸 =base from
 2칸 base to
 3칸 number
 (c>='a' && c<='z') || (c>='A' && c<='Z')

 
 base from --> 10진수 number
 10진수 number --> divide by base to
 
 */


int main(int argc, char ** argv)
{
    int i=0;
    
    if(argc<4){
        printf("Usage:  convert <basefrom> <baseto> <number>\n");
        exit(1);
    }
    
    int basefrom = atoi(argv[1]);
    int baseto = atoi(argv[2]);
    char *number = argv[3];
    
    printf("Number read in base %d: %s\n", basefrom, number);
    
    int sum = convert(basefrom, number);
    printf("Converted to base 10: %d\n", sum);

    char* converted = back(baseto, sum);
    printf("Converted to base %d: %s\n", baseto, converted);

    
    return 1;
}
