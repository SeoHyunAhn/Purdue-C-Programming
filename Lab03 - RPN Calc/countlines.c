/*
 This program will read the characters from the file that it is passed as argument and it will print the number of lines.
 */
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char ** argv) {
	int c;
	int lines=0;
	
	FILE *fd=fopen(argv[1], "r");
	printf("Program that counts lines.\n");
	while((c=fgetc(fd))!=EOF){ 
		if (c=='\n')
			lines++;
    }

	printf("Total lines: %d\n", lines);
	exit(0);
}
