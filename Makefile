CC = gcc
CFLAGS = -g -Ilibrary
SRC = $(wildcard *.c menu/*.c)
OBJ = $(SRC:.c=.o)
EXE = main.exe

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /q $(OBJ) $(EXE)