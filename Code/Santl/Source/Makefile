PROJECT = neighbour_joining
SOURCES = main.c init.c util.c print_solution.c free_memory.c find_best_pair.c delete_and_set.c
HEADERS = structure.h init.h util.h print_solution.h free_memory.h find_best_pair.h delete_and_set.h

CC = gcc
CFLAGS = -Wall -g -O2
LDFLAGS =
OBJECTS = ${SOURCES:.c=.o}
BIN = ../Bin/

$(PROJECT): $(OBJECTS)
	$(CC) $(OBJECTS) -o ${BIN}$(PROJECT)

$(OBJECTS): $(HEADERS)

clean:
	-rm -f ${BIN}$(PROJECT) $(OBJECTS) *.core *.o
