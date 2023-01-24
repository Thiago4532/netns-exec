all: netns-exec

CC = gcc
CFLAGS = -D_GNU_SOURCE
PREFIX = /usr/local

SRC = netns-exec.c namespace.c
OBJ = ${SRC:.c=.o}

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

netns-exec: ${OBJ}
	$(CC) -o netns-exec netns-exec.o namespace.o $(CFLAGS)

clean:
	@echo cleaning
	rm -f netns-exec ${OBJ}

install:
	@echo installing netns-exec to ${DESTDIR}${PREFIX}/bin...
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f netns-exec ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/netns-exec
	@chmod u+s ${DESTDIR}${PREFIX}/bin/netns-exec

uninstall:
	@echo removing netns-exec from ${DESTDIR}{PREFIX}/bin
	rm -f ${DESTDIR}${PREFIX}/bin/netns-exec

.PHONY: all clean install uninstall
