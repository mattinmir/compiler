all: parser.tab.cc lex.yy.cc
	g++ -std=c++0x parser.tab.cc lex.yy.cc -o compiler

scanner: lex.yy.cc
	g++ lex.yy.cc -o scanner

lex.yy.cc: parser.tab.hh lexer.lex
	flex -o lex.yy.cc lexer.lex

parser.tab.hh parser.tab.cc: parser.y
	bison -dr all  parser.y -o parser.tab.cc

clean:
	rm parser.tab.cc lex.yy.cc parser.tab.hh scanner
