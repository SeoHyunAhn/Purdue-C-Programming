
goal: git testmemdump mem myfiledump test_mystring test_array

testmemdump: mymemdump.c testmemdump.c obj/orgmemdump.o
	gcc -std=gnu99 -g -o testmemdump testmemdump.c mymemdump.c obj/orgmemdump.o

myfiledump: myfiledump.c 
	gcc -std=gnu99 -g -o myfiledump myfiledump.c 

mem: mymemdump.c mem.c
	gcc -std=gnu99 -g -o mem mymemdump.c mem.c

test_array: test_array.c array.c
	gcc -std=gnu99 -g -o test_array test_array.c array.c

test_mystring: test_mystring.c mystring.c
	gcc -std=gnu99 -g -o test_mystring test_mystring.c mystring.c

git:
	@#Do not remove or comment these lines. They are used for monitoring progress.
	@git add *.h *.c total.out >> local.git.out 2>&1 || echo
	@git total.out >> local.git.out 2>&1 || echo
	@git local.git.out >> local.git.out 2>&1 || echo
	git commit -a -m "Lab5 " >> local.git.out 2>&1 || echo

clean:
	rm -f testmemdump myfiledump mem convert test_bits total.out

