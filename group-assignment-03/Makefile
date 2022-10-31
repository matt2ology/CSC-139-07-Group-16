CC = gcc
CFLAGS = -pthread
SRC = stack-ptr.c
EXE = stack-ptr

all: $(SRC)
	$(CC) $(CFLAGS) $< -o $(EXE)

.PHONY: clean
clean: $(EXE)
	rm -f $(EXE)
