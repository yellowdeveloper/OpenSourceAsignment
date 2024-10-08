all: hello

test: hello.c
	gcc -Wall -ansi -pedantic -o hello hello.c

clean:
	rm -f hello
