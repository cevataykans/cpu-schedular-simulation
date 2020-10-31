all: thread

thread: *.c lists/*.c
	gcc -Wall -o out *.c lists/*.c -lpthread
clean:
	rm out