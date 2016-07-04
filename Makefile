ALL=led-blink-galileo1

all : ${ALL}

CC=gcc
CFLAGS=-W -Wall -pedantic -O3
LDFLAGS=
.SUFFIXES:

% : %.c
	${CC} -o $@ $< ${CFLAGS} ${LDFLAGS}
	@echo

clean :
	rm -f ${ALL} *.o a.
