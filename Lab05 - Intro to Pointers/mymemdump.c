/*
 mymemdump(char *p, int len) that dumps in hexadecimal byte by byte the memory starting at “p” len bytes
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mymemdump(FILE * fd, char * p , int len) {
    // Add your code here.
    // You may see p as an array.
    // p[0] will return the element 0
    // p[1] will return the element 1 and so on
    int c;
    int j = 0;
    int i=0;
    while (j < len)
    {
        fprintf(fd, "0x%016lX: ", (unsigned long) p + j);
        // Print address of the beginning of p. You need to print
        // it every 16 bytes

        for ( i = j; i < len && i < j + 16; i ++)
        {
            c = p[i]&0xFF;// Get value at [p]. The &0xFF is to make
            // sure you truncate to 8bits or one byte.
            // Print first byte as hexadecimal
            
            fprintf(fd, "%02X ", c);
        }
        int s = len;
        while (s < j + 16)
        {
            s ++;
            fprintf(fd, "%s ", "  ");
        }
        fprintf(fd, "%s", " ");
        // Print first byte as character
        for ( i = j; i < len && i < j + 16; i ++)
        {
            c = p[i]&0xFF;
            // Print first byte as character. Only print
            // characters >= 32 that are the printable characters.
            
            fprintf(fd, "%c", (c>=32 && c < 127)?c:'.');
        }
        j += 16;
        fprintf(fd,"\n");
    } 
}
