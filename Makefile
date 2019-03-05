CC = gcc
CFLAGS = -c -Wall -Werror
TFLAGS = -I
OBJ_CATALOG = .build/src/
SOURCES = src/main.c src/game.c src/design.c src/terminal.c src/readkey.c
OBJECTS = $(SOURCES:.c = $(OBJ_CATALOG)%.o)
EXEC = bin/life

#Compile src
all: $(SOURCES) $(EXEC)
	
$(EXEC): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
