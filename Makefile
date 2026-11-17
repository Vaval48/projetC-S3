CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

EXEC = projetC

SRC = main.c affichages/affichages.c menus/menus.c donnees/donnees.c

OBJ = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean