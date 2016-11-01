CC = gcc
CFLAGS = -Wall -std=c99

all: categorizer
categorizer:
	$(CC) $(CFLAGS) questions.c qtree.c categorizer.c -o categorizer

questions:
	$(CC) $(CFLAGS) questions.c qtree.c test2.c -o test2

leak-check:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./categorizer test.txt

questions1:
	$(CC) $(CFLAGS) questions.c qtree.c test1.c -o test1
    
clean:  
	rm test2 