#include <stdlib.h>
#include <stdio.h>

//strlen
int getlength(char * str){
    int len=0;
    while(str[len]!='\0') len++;
    return len;
}

int getlen(char *str){
    int len = 0;
    
    while(str[len] != '\0'){
        len++;
    }
    
    return len;
}

//Remove whitespace (space, tab, newline) from str
void trimWhite(char * str){
    int i=getlength(str);
    int n=0, j=0;
    char temp[100];
    for( ; n<i; n++){
        if(str[n]!=' '&&str[n]!='\t'&&str[n]!='\r'&&str[n]!='\n'){
            temp[j]=str[n];
            j++;
        }
    }
    temp[j]='\0';
    str=temp;
    
    printf("temp: %s, str: %s\n\n", temp, str);
}

//replace occuring char 'toRemove' from str to 'X'
void blankX(char * str, const char toRemove){
    int i=0;
    int n=getlength(str);
    
    for(i;i<n;i++){
        if(str[i]==toRemove){
            str[i]='X';
        }
    }
    
    printf("%s    @@@\n\n", str);
    
}

//strcpy
int copy(char *dest, char *source){
    
    int i = 0;
    int len = getlen(source) + 1;
    
    for(i = 0; i < len; i++){
        dest[i] = source[i];
    }
    
    return 0;
}

//strcmp
int compare(char *str1, char *str2){
    
    int i = 0;
    
    while(str1[i] != '\0' || str2[i] != '\0'){
        if(str1[i] < str2[i]){
            return -1;
        }
        else if(str1[i] > str2[i]){
            return 1;
        }
        else{
            i++;
        }
    }
    return 0;
}

//strncmp
int ncompare( char* str1,  char *str2, int n){
    
    int i;
    char cutStr1[100];
    char cutStr2[100];
    
    for(i = 0; i < n; i++){
        cutStr1[i] = str1[i];
        cutStr2[i] = str2[i];
    }
    
    cutStr1[i] = '\0';
    cutStr2[i] = '\0';
    
    return compare(cutStr1, cutStr2);
    
    
}


unsigned int wordSearch(char * str, char * keyword){
    int i=0, count=0, word=0;
    int length=getlength(str);
    int keylen=getlength(keyword);
    
    for(i=0;i<length-keylen+1;i++){
        
        if(str[i]==keyword[0]){
            int q=0;
            for (; q<keylen; q++) {
                if(str[i+q]!=keyword[q]){
                    break;
                    printf("%d    1@@@\n\n", word);
                }
                else
                    word++;
            }
            printf("%s    3@@@\n\n", str);
            if(word==keylen){
                
                printf("12    2@@@\n\n");
                if(i==0&&str[i+keylen]==' '){
                    count++;
                    word=0;
                    printf("%d    12@@@\n\n", count);
                }
                if(i+keylen==length&&str[i-1]==' '){
                    count++;
                    word=0;
                    printf("%d    2@@@\n\n", count);
                    
                }
                
                if(str[i + keylen] == ' ' && str[i - 1] == ' '){
                    count++;
                    word=0;
                    printf("%d    3@@@\n\n", count);
                }
            }
        }
    }
    return count;
}

int isBalnaced(char * str){
    int i=0;
    int top=0;
    char stack[100];
    int j=0;
    int n=getlength(str);
    
    for(;i<30;i++){
        
        if(str[i]=='('||str[i]==')'||str[i]=='{'||str[i]=='}'||str[i]=='['||str[i]==']'){
            stack[top]=str[i];
            top++;
        }
        
        if((stack[top-1]==')'&&stack[top-2]=='(')||(stack[top-1]=='}'&&stack[top-2]=='{')){
                stack[top-1]='\0';
                stack[top-2]='\0';
                top-=2;
            
                if(top<0)
                    break;
            }
    }
    if(top>0)
        return 0;
    
    return 1;
    
}



int main(){
    char string[100]="Hello World";
    char oh='o';
    
    char stringsamp[100]="the penguin is in the theater";
    
    char a1[100]="({(aaa)aaa}(x{xx}))";
    char a2[100]="{xxxx(aaaa}";
    char a3[100]="{((aaaa}aa)){xxx)";
    char a4[100]="{(xx){xx}((aaaa))}";
    
    /*trimWhite(string);
     blankX(string, oh);
     int last=wordSearch(stringsamp, "the");
     
     
     printf("%d    @@\n\n", last);
     isBalanced(“”) =1. 
     isBalanced(“”) = 0
     isBalanced(“{”) = 0
     isBalanced(“”) = 1*/
    printf("%d    @@\n\n", isBalnaced(a1));
    printf("%d    @@\n\n", isBalnaced(a2));
    printf("%d    @@\n\n", isBalnaced(a3));
    printf("%d    @@\n\n", isBalnaced(a4));
    
    
    
    
    
    return 0;
    
    
}
