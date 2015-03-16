%code requires{
	

	#include <iostream>
	#include <stdio.h>
	#include <cstring>
	
	// #include "ast.hpp"
  	//#define YYDEBUG 0
  
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
  	char* string_t;
}

%token AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF INT 
%token LONG REGISTER RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH TYPEDEF UNION UNSIGNED 
%token VOID VOLATILE WHILE

%token COLON COMMA EOL

%token LSQUARE RSQUARE LBRACE RBRACE LPAREN RPAREN

%token ADD SUB MUL DIV MODULO

%token EQUAL_TO NOT_EQUAL_TO LOGICAL_NOT BITWISE_NOT BITWISE_OR LOGICAL_OR BITWISE_AND LOGICAL_AND BITWISE_XOR TERNARY

%token ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN BITWISE_OR_ASSIGN BITWISE_AND_ASSIGN 
%token BITWISE_XOR_ASSIGN MODULO_ASSIGN

%token <int_t> INT_VAL 
%token <double_t> DOUBLE_VAL 
%token <string_t> STRING_VAL ID


%type <string_t> type type_qualifier INT FLOAT DOUBLE CHAR LONG SHORT UNSIGNED

%start function

%{
	struct pair_t* root=0;
%}

%%

expr	: expr op expr
	


function	: type ID LPAREN RPAREN LBRACE RBRACE {cout << $2 << endl;}
		;

type		: INT
		| FLOAT
		| DOUBLE
		| CHAR
		| type_qualifier type {char str[80]; strcpy(str, $1); strcpy(str, " "); strcpy(str, $2);  $$ = str;}
		;

type_qualifier	: LONG 
		| SHORT
		| UNSIGNED
		;
%%
int main() 
{	
	//yydebug = 1;
	int y = 0;

	do
	{	
		y = yyparse();
		cout << y;
	}
    while(y);
}
