all: lex.yy.c
	gcc -g parser.tab.c lex.yy.c rpcalc.c -c
	g++ -g *.o interpreter.cpp -o rpcalc # Linking must be performed with g++ as it apppears gcc can not link c++ code


parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

clean:
	rm parser.tab.c parser.tab.h lex.yy.c *.o
