SOURCES=src/main.c src/sqlitedb.c src/linkedlist.c src/logger.c src/server.c src/client.c src/stringutil.c src/channel.c src/commands.c
OBJECTS=$(SOURCES:.c=.o)
FLAGS=-c -Wall
CC=cc
#LIBS=-lmxml -lpthread -L./mxml/lib
#INCLUDES=-I./mxml/include/ -I./include/
LIBS=-lsqlite3 -lpthread
INCLUDES=-I./src/include/ -I./src/
FRAMEWORKS=
#FRAMEWORKS=-framework OpenGL -framework GLUT

all: circ

circ: $(OBJECTS)   
	$(CC) $(OBJECTS) $(LIBS) $(FRAMEWORKS) -o $@
	make clean

.c.o:
	$(CC) $(FLAGS) $(INCLUDES) $< -o $@

clean:
	rm src/main.o src/sqlitedb.o src/linkedlist.o src/logger.o src/server.o src/client.o src/stringutil.o src/channel.o src/commands.o