%code requires{
  #include <iostream>
  #include <stdio.h>
  
 // #include "ast.hpp"
  
  
  //extern Value *g_ast; // A way of getting the AST out
  
  //! This is to fix problems when generating C++
  int yylex(void);
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
  	std::string string_t;
}
%token ASSIGN ADD MULT SUB DIV 
%token COLON COMMA SEMICOLON EOL
%token LSQUARE RSQUARE LBRACE RBRACE LPAREN RPAREN
%token INTEGER DOUBLE STRING TYPE ID

%type <number> 

%start NUM

%{
struct pair_t* root=0;

%}

%%

NUM	: NUMBER {std::cout << "Num found: " << $1 << std::endl; }

%%
