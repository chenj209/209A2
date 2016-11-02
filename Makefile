CC = gcc
CFLAGS = -Wall -g -std=c99

ODIR =./obj

DEPS = questions.h qtree.h

_OBJ = questions.o qtree.o categorizer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: directories categorizer 

directories: obj

obj:
	mkdir obj

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

categorizer: $(OBJ)
	$(CC) $^ $(CFLAGS)  -o $@

.PHONY: clean
    
clean:  
	rm -f $(ODIR)/*.o categorizer