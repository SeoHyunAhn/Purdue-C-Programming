#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//strcspn( char * str, char * reject ) -- return the length of the initial segment of 'str' which consists of characters entirely of characters that are not in reject. Example: strcspn(“abc123”, “d2” ) should return 4, because “abc1” does not contain “d2”.
//

int hello( char * str, char * reject ){
    int i, j;
    int count=0;
    for (i = 0; reject[i]; i++) {
        for (j = 0; str[j]; j++) {
            if (str[j] == reject[i]){
                if(count>j)
                    count=j;
                if (i==0) {
                    count=j;
                }
                break;
            }
        }
        
    }
    return count;
    
    
}

int main() {
    char sample1[10]= "a banana";
    char sample2[40]="hello to everyone who done their work";
    printf("%d\n", hello(sample1, "bn"));
    printf("%d\n", hello(sample2, "wd"));
    return 0;
}
