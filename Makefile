all: lex.yy.c
	gcc -std=c99 parser.tab.c lex.yy.c rpcalc.c -c
	g++ -std=c++11 *.o input_handler.cpp interpreter.cpp -o rpcalc


parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

clean:
	rm parser.tab.c parser.tab.h lex.yy.c *.o
