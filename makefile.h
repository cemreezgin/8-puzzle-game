//
//  makefile.h
//  iai_3
//
//  Created by Anıl on 10.05.2025.
//

CC = gcc
CFLAGS = -O3 -march=native -flto -DNDEBUG
LDFLAGS = -lm
SRC = GRAPH_SEARCH.c Standart_Search.c SpecificToProblem.c HashTable.c
OBJ = $(SRC:.c=.o)
EXEC = puzzle_solver

all: $(EXEC)

$(EXEC): $(OBJ)
    $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ) $(EXEC)

gcc -O3 -march=native -flto -DNDEBUG -o puzzle_solver *.c -lm

CFLAGS = -O3 -march=native -flto -fomit-frame-pointer -DNDEBUG

#ifdef DEBUG
void Print_Frontier(Queue *const frontier) {
    // ... mevcut kod ...
}
#endif
