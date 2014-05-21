CC = g++
CFLAGS = -Wall


target = calc

$(target):	$(target).o $(target)-lexer.o $(target)-parser.tab.o
	$(CC) -o $@ $^

$(target)-parser.tab.c $(target)-parser.tab.h:	$(target)-parser.y
	bison $<

$(target)-lexer.c:	$(target)-lexer.l $(target)-parser.tab.h
	flex -o$@ $<

clean:
	rm -f $(target)-lexer.[co] $(target)-parser.tab.[och] $(target).o

cleanall:	clean
	rm -f $(target)
