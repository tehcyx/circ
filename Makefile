SOURCES=src/main.c
OBJECTS=$(SOURCES:.c=.o)
FLAGS=-c -Wall
CC=cc
#LIBS=-lmxml -lpthread -L./mxml/lib
#INCLUDES=-I./mxml/include/ -I./include/
LIBS=-lpthread -lm
INCLUDES=
FRAMEWORKS=
#FRAMEWORKS=-framework OpenGL -framework GLUT

all: circ
	
circ: $(OBJECTS)   
	$(CC) $(OBJECTS) $(LIBS) $(FRAMEWORKS) -o $@
	make clean	
	
.c.o:
	$(CC) $(FLAGS) $(INCLUDES) $< -o $@

clean:
	rm src/main.o
