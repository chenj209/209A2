CC = gcc
CFLAGS = -Wall -std=c99

all: questions 

questions:
	$(CC) $(CFLAGS) questions.c qtree.c test2.c -o test2

leak-check:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test2 test.txt Tony 0 0 0 0 0

questions1:
	$(CC) $(CFLAGS) questions.c qtree.c test1.c -o test1
    
clean:  
	rm test2 