all: pointer_to_function

pointer_to_function: problem_pointer_to_function.c mytest.c pointer_to_function.h
	gcc -std=gnu99 -g -o mytest mytest.c problem_pointer_to_function.c

release: problem_pointer_to_function.c mytest.c pointer_to_function.h
	gcc -std=gnu99 -o mytest mytest.c problem_pointer_to_function.c

clean:
	rm -f *.out *.txt *.o mytest
