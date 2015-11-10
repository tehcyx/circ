SOURCES=src/main.c src/sqlitedb.c src/linkedlist.c src/logger.c src/server.c src/client.c src/stringutil.c src/channel.c src/commands.c
OBJECTS=$(SOURCES:.c=.o)
CFLAGS=-std=c99 -Wall -Wextra -Wno-unused-parameter -ggdb3
CFLAGS+=-D_THREAD_SAFE
CFLAGS+=-I./src/include
LIBS=-lsqlite3  -lpthread

all: bin/circ

bin/circ: $(OBJECTS) $(CXX_OBJS)
	[ -d bin ] || mkdir -p bin
	$(CC) $(OBJECTS) $(CXX_OBJS) $(LIBS) -o $@
	
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf bin $(OBJECTS) $(CXX_OBJS)