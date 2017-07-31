/*
 *  CS 24000 First mid-semester exam.
 *   Problem #1-4
 *
 *  long int exponent(int base, unsigned int exp) 
 *
 *  Arguments:
 *		int base
 *		unsigned int exp
 *		
 *  Function return: 
 *      long int
 *
 *  Description:
 *		The function raises base to the exponent
 *      Example:  exponent(3, 8)
 *			3 * 3 * 3 * 3 * 3 * 3 * 3 * 3  or 3 ^ 8
 *
 *    The function only accepts 1 <= base <= 5 and 1 <= exp <= 15 
 *  
 *  Error:
 *		Function returns -1 if base or exp are out of range
 *
 */
 
 /* ======================== Start your edits here =========================== */
 
 /*
  *  NOTE NOTE NOTE NOTE NOTE
  *  You are not allowed to add any other libraries or library includes in addition
  *   to <stdlib.h> other than <math.h> (if you believe you need it).
  */

 #include <stdlib.h>
 
 /* 
  * Complete the function below for the exam
  */

 long int exponent(int base, unsigned int exp) 
 {
	if(1<=exp&&exp<=15&&1<=base&&base<=5){
	int result=1, i=0;
	for( ; i<exp; i++){
		result*=base;
	}
	return result;
	}
	else
		return -1;
 }
  
 /* ======================== End your edits here =========================== */

 /*
 ************************************************************************
  *  Do NOT change any of the lines between here and the end of the file!
 ************************************************************************
  */

#include <stdio.h>

char *Usage = "Usage: %s <n> <m>\t\t with 1 <= n <= 5, 1 <= m <= 15\n";

int main(int argc, char *argv[])
{
	unsigned int exp;
	int base;
	long int result;
	
	if (argc != 3) 
	{
		fprintf(stderr, Usage, argv[0]);
		exit(1);
	}
	
	base = (int) strtol(argv[1], NULL, 10);
	exp = (unsigned int) strtoul(argv[2], NULL, 10);
	result = exponent(base, exp);
	
	if (result >= 0)
		printf("%d to the power of %u is %ld\n", base, exp, result);
	else
		fprintf(stderr, "exponent returned value %ld\n", result);
		
	return (result == -1);
}
	
	
