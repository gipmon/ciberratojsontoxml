CC = g++
CFLAGS = -c -Wall

CLASSES =  Challenge Maze Grid  Beacons TargetAreas Walls

all: compile cleanall

compile: param_table.o param_bison param_flex maze_parser.y maze_parser.l classes
	$(CC) param_table.o param_parser.tab.c param_parser/param_lexer.c maze_parser.tab.c maze_parser/maze_lexer.c classes/Challenge.o classes/Maze.o classes/Grid.o classes/Beacons.o classes/TargetAreas.o classes/Walls.o main.cpp -o main.output

param_table.o:	param_parser/param_table.cpp
	$(CC) $(CFLAGS) param_parser/param_table.cpp

param_flex: param_parser/param_lexer.l
	flex -oparam_parser/param_lexer.c param_parser/param_lexer.l

param_bison: param_parser/param_parser.y
	bison param_parser/param_parser.y

maze_parser.y:
	bison maze_parser/maze_parser.y

maze_parser.l:
	flex -omaze_parser/maze_lexer.c maze_parser/maze_lexer.l

classes: $(CLASSES)

$(CLASSES): %: classes/%.cpp
			$(CC) $(CFLAGS) classes/$@.cpp -o classes/$@.o

cleanall:
	rm -rf param_parser/*.o
	rm -f param_parser/param_lexer.c
	rm -rf maze_parser/*.o
	rm -f maze_parser/maze_lexer.c
	rm -rf *.o
	rm -f *.tab.c
	rm -f *.tab.h
	rm -f classes/*.o
