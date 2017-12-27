SRCDIR=src
OBJDIR=obj
SOURCES=src/main.c src/sqlitedb.c src/linkedlist.c src/logger.c src/server.c src/client.c src/stringutil.c src/channel.c src/commands.c src/utils.c
OBJECTS=$(addprefix $(OBJDIR)/, main.o sqlitedb.o linkedlist.o logger.o server.o client.o stringutil.o channel.o commands.o utils.o)
CFLAGS=-std=gnu99 -Wall -Wextra -Wno-unused-parameter -ggdb3
CFLAGS+=-D_THREAD_SAFE
CFLAGS+=-I./src/include
LIBS=-lsqlite3 -lpthread

all: bin/circ

bin/circ: $(OBJECTS) $(CXX_OBJS)
	[ -d bin ] || mkdir -p bin
	$(CC) $(OBJECTS) $(CXX_OBJS) $(LIBS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# .c.o:
# 	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean:
	rm -rf $(OBJECTS) $(CXX_OBJS)
