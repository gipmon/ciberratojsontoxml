CC = g++
CFLAGS = -c -Wall

all: paramparser

paramparser: param_table.o param_bison param_flex
	$(CC) param_table.o param_parser.tab.c param_parser/param_lexer.c -o output
	rm -rf param_parser/*.o
	rm -rf *.o
	rm -f param_parser/param_lexer.c
	rm -f *.tab.c
	rm -f *.tab.h

param_table.o:	param_parser/param_table.cpp
	$(CC) $(CFLAGS) param_parser/param_table.cpp

param_flex: param_parser/param_lexer.l
	flex -oparam_parser/param_lexer.c param_parser/param_lexer.l

param_bison: param_parser/param_parser.y
	bison param_parser/param_parser.y