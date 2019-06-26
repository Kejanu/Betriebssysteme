CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=c11 -g -pedantic

BINARIES = a5 a5extended

all: a5

main.o: main.c a5.h

a5.o: a5.c a5.h

a5extended.o: a5extended.c a5.h

a5: main.o a5.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

a5extended: main.o a5extended.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

clean:
	rm -f $(BINARIES) *.o

.PHONY: all clean

