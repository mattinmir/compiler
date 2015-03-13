%code requires{
	#include <iostream>
	#include <stdio.h>
  
	// #include "ast.hpp"
  
  
	//extern Value *g_ast; // A way of getting the AST out
  
	//! This is to fix problems when generating C++
	int yylex();
	void yyerror(const char *);
	
}

%{
	using namespace std;
%}

%union
{
  	char char_t;
	short short_t;
  	int int_t;
	long long_t;
	double double_t;
	void* ptr_t;
  	const char* string_t;
}

%token COLON COMMA EOL
%token LSQUARE RSQUARE LBRACE RBRACE LPAREN RPAREN
%token ADD SUB MUL DIV MODULO
%token EQUAL_TO NOT_EQUAL_TO BITWISE_OR LOGICAL_OR BITWISE_AND LOGICAL_AND BITWISE_XOR TERNARY
%token ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN BITWISE_OR_ASSIGN BITWISE_AND_ASSIGN BITWISE_XOR_ASSIGN MODULO_ASSIGN
%token <int_t> INTEGER 
%token <double_t> DOUBLE 
%token <string_t> STRING TYPE ID

%start number

%{
	struct pair_t* root=0;
%}

%%

number	: DOUBLE {std::cout << "Num found: " << $1 << std::endl; }
		| INTEGER {std::cout << "Num found: " << $1 << std::endl; }

%%
int main() 
{	
	int y = 0;

	do
	{	
		y = yyparse();
		cout << y;
	}
    while(y);
}