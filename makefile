CC = gcc
FLAGS := -g -pthread -Wpedantic -Wall -pedantic-errors -std=c11
OUT = main.out

SRC = $(wildcard *.c)
INC = $(wildcard *.h)

$(OUT): $(SRC) $(INC)
	$(CC) $(FLAGS) -o $(OUT) $(SRC)

clean:
	rm -fv $(OUT)

run: $(OUT)
	./$(OUT)

all:	$(OUT) run
