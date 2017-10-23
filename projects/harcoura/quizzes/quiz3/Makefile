CFLAGS = -Wall -fpic -coverage -lm

testme: 
	gcc -o testme testme.c -g  $(CFLAGS)

all: testme

clean:
	rm testme *.gcov *.gcda *.gcno
