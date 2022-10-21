CC = gcc
SHELL = /bin/bash
CFLAGS = -Wall -Wpedantic -O3
INCLUDE = 
LIBS = -lssl -lcrypto
NAME = httpsTest
SOURCES = $(wildcard src/*.c)
OBJS = ${subst src/, obj/, ${subst .c,.o,${SOURCES}}}

default: $(NAME)

$(NAME): obj-dir build-dir $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -g -pg -o build/$(NAME) $(OBJS)

clean:
	-rm -rf obj
	-rm ./build/$(NAME)*

build-dir:
	-mkdir -p build/

obj-dir:
	-mkdir -p obj/

$(OBJS): obj/%.o : src/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -pg $(LIBS) -c "src/$*.c" -o obj/$*.o
