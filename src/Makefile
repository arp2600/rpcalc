RPCLIB = -DLIB_DIR=\"../rpc_lib/\"

all: lex.yy.c
	gcc -std=c99 $(RPCLIB) parser.tab.c lex.yy.c rpcalc.c output.c -c
	g++ -std=c++11 $(RPCLIB) *.o input_handler.cpp interpreter.cpp -o rpcalc
	mv rpcalc ../bin

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

clean:
	rm parser.tab.c parser.tab.h lex.yy.c *.o
