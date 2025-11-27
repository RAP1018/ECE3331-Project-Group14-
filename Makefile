CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = main.c src/regex.c
OBJ = $(SRC:.c=.o)
EXE = regex-lite

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

clean:
	rm -f $(OBJ) $(EXE)

run:
	./regex-lite test/test_cases.txt "pattern"
