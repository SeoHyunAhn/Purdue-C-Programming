/*
 Prints a byte dump similar to MemoryDump but using a file insteqad of memory.
 Where “file” is the name of the file to print. The parameter “maxbytes” is optional and indicates  the number of bytes to print. If “maxbytes” does not exist, then it will print the entire file.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void filedump(char * p , int len) {
    
    int c;
    int j=0;
    int i=0;
    int add = 0;
    while (j < len)
    {
        printf( "0x0000000000%05X0: ",add);
        add++;
        for ( i = j; i < len && i < (j + 16); i ++)
        {
            c = p[i]&0xFF;
            printf( "%02X ", c);
        }
        int temp = len;
        while (temp < j + 16)
        {
            temp++;
            printf( "%s ", "  ");
        }
        printf( "%s", " ");
        for ( i = j; i < len && i < j + 16; i ++)
        {
            c = p[i]&0xFF;
            
            printf( "%c", (c>=32 && c < 127)?c:'.');
        }
        j += 16;
        printf("\n");
    }
}


int main(int argc, char **argv) {
    int maxbyte;
    int fileSize;
    
    FILE *fin=fopen(argv[1], "r");
    
    if(fin == NULL){
        printf("Error opening file \"invalidfile\"\n");
        exit(1);
    }
    fseek(fin, 0L, SEEK_END);  // Go to the end of the file fin
    fileSize = ftell(fin); // Get current file pointer
    fseek(fin, 0L, SEEK_SET); // Go back to the beginning of the file.
    
    if (argc==3 &&fileSize>atoi(argv[2])) {
        maxbyte= atoi(argv[2]);
        char *name = (char *) malloc(sizeof(char)*100000);
        fread(name, maxbyte, 1, fin);
        filedump(name, maxbyte);
        free(name);
    }else {
        char *name = (char *) malloc(sizeof(char)*100000);
        fread(name, fileSize, 1, fin);
        filedump(name, fileSize);
        free(name);
    }
    
}


