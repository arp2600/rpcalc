all: lex.yy.c
	g++ -c interpreter.cpp
	gcc parser.tab.c lex.yy.c rpcalc.c -o rpcalc

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

clean:
	rm parser.tab.c parser.tab.h lex.yy.c *.o
