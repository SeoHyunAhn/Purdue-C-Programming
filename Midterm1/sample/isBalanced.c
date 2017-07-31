#include <stdlib.h>
#include <stdio.h>
int top=0;
char stack[100];

char stack_pop(){
	char temp=stack[top];
	stack[top]=stack[top+1];
	top--;

	return temp;
}

void stack_push(char val){
    stack[top]=val;
	top++;
	
}

int getlength(char * str){
	int i=0; 
	int count=0;

	while(str[i]!='\0'){
	i++;
	count++;
	}
return count;
}

/*
 Given a string str that contain parentheses “()” , curly braces “{ }” or square brackets “[ ]”, return 1 if for every type of opening character there is a matching closing character, 0 otherwise. Note that different characters should not overlap with each others
 */
int isBalanced(char * str){
	int i=0, j=0;
	int length=getlength(str);
    
     printf("length: %d \n", length);
	for(;i<length;i++){

        if((stack[top-2]=='('&&stack[top-1]==')')||(stack[top-2]=='{'&&stack[top-1]=='}')||(stack[top-2]=='['&&stack[top-1]==']')){
			
            for(j=0;j<2;j++){
            stack[top-1]='\0';
            top--;
                if(top<0)
                    break;
            }
            continue;
        }
    
        if(str[i]=='('||str[i]==')'||str[i]=='{'||str[i]=='}'||str[i]=='['||str[i]==']'){
            stack_push(str[i]);
        }
    }
    if(top==0){
        return 1;
    }
    
        return 0;


}


int main(int argc, const char * argv[]){
    char a1[]="({(aaa)aaa}(x{xx}))";
    char a2[]="{xxxx(aaaa}";
    char a3[]="{((aaaa}aa)){xxx)";
    char a4[]="{(xx){xx}((aaaa))}";
    
    printf("1. %d     @@@\n", isBalanced(a1));
     printf("2. %d     @@@\n", isBalanced(a2));
     printf("3. %d     @@@\n", isBalanced(a3));
     printf("4. %d     @@@\n", isBalanced(a4));

    return 0;
}
