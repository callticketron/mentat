CFLAGS = -Wall -g
EXE = msh
SOURCE = mentat.c
CC = gcc
DEPS = 

all: clean mentat

mentat: $(DEPS)
	cd src && $(CC) $(CFLAGS) $(SOURCE) -o $(EXE) $(DEPS)

clean:
	rm -rf a.out msh *.o
