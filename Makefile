HDIR =../headers
CC = gcc
CFLAGS = -Wall -g -std=c99

ODIR =obj

_DEPS = questions.h qtree.h
DEPS = $(patsubst %,$(HDIR)/%,$(_DEPS))

_OBJ = questions.o qtree.o categorizer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: categorizer

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

categorizer: $(OBJ)
	$(CC) $^ $(CFLAGS)  -o $@

.PHONY: clean
    
clean:  
	rm -f $(ODIR)/*.o categorizer