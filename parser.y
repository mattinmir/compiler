%{
	

	#include <iostream>
	#include <cstdio>
	#include <cstring>
	
	// #include "ast.hpp"
  	//#define YYDEBUG 0
  	using namespace std;
	//extern Value *g_ast; // A way of getting the AST out
  
	//! This is to fix problems when generating C++
	int yylex();
	void yyerror(const char *);
	
%}


%union{

  	char char_t;
	short short_t;
  	int int_t;
	long long_t;
	double double_t;
	void* ptr_t;
  	char* string_t;
}

%token AUTO BREAK BOOL CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF INT 
%token LONG REGISTER RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH TYPEDEF UNION UNSIGNED 
%token VOID VOLATILE WHILE

%token COLON COMMA EOL

%token LSQUARE RSQUARE LBRACE RBRACE LPAREN RPAREN

%token ADD SUB MUL DIV MODULO

%token EQUAL_TO NOT_EQUAL_TO LOGICAL_NOT BITWISE_NOT BITWISE_OR LOGICAL_OR BITWISE_AND LOGICAL_AND 
%token BITWISE_XOR TERNARY LT_EQUAL_TO GT_EQUAL_TO

%token TRUE FALSE

%token ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN BITWISE_OR_ASSIGN BITWISE_AND_ASSIGN 
%token BITWISE_XOR_ASSIGN MODULO_ASSIGN

%token INCREMENT DECREMENT

%token <int_t> INT_VAL 
%token <double_t> DOUBLE_VAL 
%token <string_t> STRING_VAL ID
%token <char_t>	CHAR_VAL

%type <string_t>   INT FLOAT DOUBLE CHAR LONG SHORT UNSIGNED
%left '<' '>' '=' GT_EQUAL_TO LT_EQUAL_TO NOT_EQUAL_TO
%left '+' '-' ADD_ASSIGN SUB_ASSIGN INCREMENT DECREMENT
%left '*' '/' 

%right "then" "else"

%%

program			: declaration_list
			;

declaration_list	: declaration_list declaration
			| declaration
			;

declaration		: var_declaration
			| fun_declaration
			;

var_declaration		: type_specifier var_decl_list ';'
			;

scoped_var_declaration	: scoped_type_specifier var_decl_list ';'
			;

var_decl_list		: var_decl_list ',' var_decl_initialise
			| var_decl_initialise
			;

var_decl_initialise	: var_decl_id
			| var_decl_id ':' simple_expression
			;

var_decl_id		: ID
			| ID '[' INT_VAL ']'
			;

scoped_type_specifier	: type_specifier
			;

type_specifier		: INT
			| FLOAT
			| DOUBLE
			| CHAR
			| BOOL
			;

fun_declaration		: type_specifier ID '(' params ')' 
			| ID '(' params ')' statement
			;

params			: /*Empty*/
			| param_list
			;

param_list		: param_list ';' param_type_list
			| param_type_list
			;

param_type_list		: type_specifier param_id_list
			;

param_id_list		: param_id_list ',' param_id
			| param_id
			;

param_id		: ID
			| ID '[' ']'
			;

statement		: expression_stmt
			| compound_stmt
			| selection_stmt
			| iteration_stmt
			| return_stmt
			| break_stmt
			;

compound_stmt		: '{' local_declarations statement_list '}' // int x; float y; ... statements
			;

local_declarations	: /*Empty*/
			| local_declarations scoped_var_declaration
			;

statement_list		: /*Empty*/
			| statement_list statement
			;

expression_stmt		: expression ';'
			| ';'
			;

selection_stmt		: IF '(' simple_expression ')' statement
			| IF '(' simple_expression ')' statement ELSE statement
			;

iteration_stmt		: WHILE '(' simple_expression ')' statement // TODO: for
			;

return_stmt		: RETURN ';'
			| RETURN expression ';'
			;

break_stmt		: BREAK ';'
			;

expression		: mutable '=' expression
			| mutable ADD_ASSIGN expression
			| mutable SUB_ASSIGN expression
			| mutable '*' expression
			| mutable DIV_ASSIGN expression
			| mutable BITWISE_AND_ASSIGN expression
			| mutable BITWISE_OR_ASSIGN expression
			| mutable INCREMENT
			| mutable DECREMENT
			| simple_expression
			;

simple_expression	: simple_expression LOGICAL_OR and_expression
			| and_expression
			;

and_expression		: and_expression LOGICAL_AND unary_rel_expression
			| and_expression
			;

unary_rel_expression	: '!' unary_rel_expression
			| rel_expression
			;

rel_expression		: sum_expression relop sum_expression
			| sum_expression
			;

relop			: LT_EQUAL_TO
			| '<'
			| '>'
			| GT_EQUAL_TO
			| EQUAL_TO
			| NOT_EQUAL_TO
			;

sum_expression		: sum_expression sumop term
			| term
			;

sumop			: '+' 
			| '-'
			;

term			: term mulop unary_expression
			| unary_expression
			;

mulop			: '*'
			| '/'
			| '%'
			;

unary_expression	: unaryop unary_expression
			| factor
			;

unaryop			: '-' 
			| '*'
			;

factor			: immutable
			| mutable
			;

mutable			: ID 
			| ID '[' expression ']'
			;

immutable		: '(' expression ')' 
			| call 
			| constant
			;

call			: ID '(' args ')'
			;

args			: /*Empty*/
			| arg_list
			;

arg_list		: arg_list ',' expression
			| expression
			;

constant		: number
			| boolean
			| CHAR_VAL
			| STRING_VAL
			;

number			: INT_VAL
			| DOUBLE_VAL
			;

boolean			: TRUE
			| FALSE
			;

%%
int main() 
{	
	//yydebug = 1;
	while(yyparse());
}
