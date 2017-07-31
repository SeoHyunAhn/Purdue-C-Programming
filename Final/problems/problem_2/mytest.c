#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pointer_to_function.h"

// extern is just because these functions are defined in the problem file
extern int intMatches(int key, void * element);
extern int studentIdMatches(int key, void * element);

int main(int argc, char ** argv) {
	if (argc < 2) {
		printf("test_mysort [test1|...|test4]");
		exit(1);
	}

	if (!strcmp(argv[1], "test1")) {
		int x, key;
		int match;

		x = 43, key = 43;
		printf("%d = %d: %s\n",key, x, intMatches(key, (void *) &x) ? "TRUE" : "FALSE");

		x = 82, key = 26;
		printf("%d = %d: %s\n",key, x, intMatches(key, (void *) &x) ? "TRUE" : "FALSE");

		x = 23, key = 80;
		printf("%d = %d: %s\n",key, x, intMatches(key, (void *) &x) ? "TRUE" : "FALSE");

		x = 0, key = 0;
		printf("%d = %d: %s\n",key, x, intMatches(key, (void *) &x) ? "TRUE" : "FALSE");

		x = 1, key = -1;
		printf("%d = %d: %s\n",key, x, intMatches(key, (void *) &x) ? "TRUE" : "FALSE");

	} else if (!strcmp(argv[1], "test2")) {
		student s;
		int match, key;

		key = 1234;
		printf("s = {firstName = %s\n", s.firstName = "Zidane");
		printf("      lastName = %s\n", s.lastName = "Tribal");
		printf("      id = %d}\n", s.id = 1234);
		printf("%d = %d: %s\n",key, s.id, studentIdMatches(key, (void *) &s) ? "TRUE" : "FALSE");

		key = 4278;
		printf("s = {firstName = %s\n", s.firstName = "Vivi");
		printf("      lastName = %s\n", s.lastName = "...");
		printf("      id = %d}\n", s.id = 8475);
		printf("%d = %d: %s\n",key, s.id, studentIdMatches(key, (void *) &s) ? "TRUE" : "FALSE");

	} else if (!strcmp(argv[1], "test3")){
		int result, key, found;

		int array1[] = {3, 7, 5, 1, 9, 12, 42, 70, 21};
		key = 42;
		printf("Find %d in {3, 7, 5, 1, 9, 12, 42, 70, 21}\n", key);
		found = findElement(9, sizeof(int), (void *) array1, key, (void *) &result, intMatches);
		printf("element %s\n", found ? "found" : "not found");
		if (found) {
			printf("result = %d\n", result);
		}

		int array2[] = {18, 65, 24, 37, 81, 52, 74, 81, 22, 1};
		key = 83;
		printf("Find %d in {18, 65, 24, 37, 81, 52, 74, 81, 22, 1}\n", key);
		found = findElement(10, sizeof(int), (void *) array2, key, (void *) &result, intMatches);
		printf("element %s\n", found ? "found" : "not found");
		if (found) {
			printf("result = %d\n", result);
		}
	} else if (!strcmp(argv[1], "test4")) {
		student s[5];
		student result;
		int key, found;

		printf("s[0] = {firstName = %s\n", s[0].firstName = "Zidane");
		printf("        lastName = %s\n", s[0].lastName = "Tribal");
		printf("        id = %d}\n", s[0].id = 34);

		printf("s[1] = {firstName = %s\n", s[1].firstName = "Adelbert");
		printf("        lastName = %s\n", s[1].lastName = "Steiner");
		printf("        id = %d}\n", s[1].id = 45);

		printf("s[2] = {firstName = %s\n", s[2].firstName = "Freya");
		printf("        lastName = %s\n", s[2].lastName = "Crescent");
		printf("        id = %d}\n", s[2].id = 84);

		printf("s[3] = {firstName = %s\n", s[3].firstName = "Eiko");
		printf("        lastName = %s\n", s[3].lastName = "Carol");
		printf("        id = %d}\n", s[3].id = 73);

		printf("s[4] = {firstName = %s\n", s[4].firstName = "Armarant");
		printf("        lastName = %s\n", s[4].lastName = "Coral");
		printf("        id = %d}\n", s[4].id = 0);

		key = 45;
		found = findElement(5, sizeof(student), (void *) s, key, (void *) &result, studentIdMatches);
		printf("element %s\n", found ? "found" : "not found");
		if (found) {
			printf("result = {firstName = %s, lastName = %s, id = %d}\n", result.firstName, result.lastName, result.id);
		}

		key = 99;
		found = findElement(5, sizeof(student), (void *) s, key, (void *) &result, studentIdMatches);
		printf("element %s\n", found ? "found" : "not found");
		if (found) {
			printf("result = {firstName = %s, lastName = %s, id = %d}\n", result.firstName, result.lastName, result.id);
		}

	} else {
		printf("Invalid test\n");
	}
}
