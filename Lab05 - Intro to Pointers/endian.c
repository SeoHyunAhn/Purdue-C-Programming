/*
 In Little-Endian, the least significant byte of the integer is stored the lowest address in memory. In Big-Endian, the least significant byte is stored in the highest address in memory.
 */

#include <stdio.h>

int isLittleEndian() {
  int a = 0x05;
  char * p = (char *) &a;
   if (*p==0x05) {
      return 1;
     }
     return 0;
     }

main(){
 if (isLittleEndian()) {
    printf("Machine is Little Endian\n");
     }
  else {
    printf("Machine is Big Endian\n");
  }
  }
