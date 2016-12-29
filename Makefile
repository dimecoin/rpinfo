
CC=gcc
CFLAGS=-ansi -pedantic -std=c11 -pipe -Wall -I. -L. -fsanitize=address -fno-omit-frame-pointer 
LIBS=

DEBUGFLAGS=-g -O0 -DDEBUG_FLAG
RELEASEFLAGS=-Os
NUMJOBS=2

NAME=rpinfo
FILES=

default: all

all:clean debug

release: clean
	$(CC) $(CFLAGS) $(LIBS) $(RELEASEFLAGS) *.c -o $(NAME)
	strip -sxX ${NAME}

debug: clean
	$(CC) $(CFLAGS) $(LIBS) $(DEBUGFLAGS) ${NAME}.c ${FILES} -o $(NAME)

asm: clean
	$(CC) $(CFLAGS) $(LIBS) -S ${NAME}.c ${FILES} -o $(NAME).s
	
clean:
	rm a.out $(NAME) $(NAME).s *.o *.so 2> /dev/null || true




