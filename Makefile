cc = gcc
CFLAGS = -Wall -std=c99
all: questions
questions:
	$(cc) $(CFLAGS) questions.c test1.c -o test1
clean:
	rm test1
