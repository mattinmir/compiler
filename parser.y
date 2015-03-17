%{	
	#include <cstdio>
	#include <iostream>
	
	// #include "ast.hpp"
  	//#define YYDEBUG 1
  	using namespace std;
	//extern Value *g_ast; // A way of getting the AST out
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

%token ADD ADD_ASSIGN ASSIGN AUTO BITWISE_AND BITWISE_AND_ASSIGN BITWISE_NOT BITWISE_OR BITWISE_OR_ASSIGN BITWISE_XOR BITWISE_XOR_ASSIGN BOOL BREAK CASE CHAR COLON COMMA CONST CONTINUE DECREMENT DEFAULT DIV DIV_ASSIGN DO DOUBLE ELSE ENUM EOL EQUAL_TO EXTERN FALSE FLOAT FOR GOTO GT_EQUAL_TO IF INCREMENT INT LBRACE LOGICAL_AND LOGICAL_NOT LOGICAL_OR LONG LPAREN LSQUARE LT_EQUAL_TO MODULO MODULO_ASSIGN MUL MUL_ASSIGN NOT_EQUAL_TO RBRACE REGISTER RETURN RPAREN RSQUARE SHORT SIGNED SIZEOF STATIC STRUCT SUB SUB_ASSIGN SWITCH TERNARY TRUE TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE

%token <int_t> INT_VAL 
%token <double_t> DOUBLE_VAL 
%token <string_t> STRING_VAL ID
%token <char_t>	CHAR_VAL

%type <string_t>   INT FLOAT DOUBLE CHAR LONG SHORT UNSIGNED

%left LESS_THAN GREATER_THAN ASSIGN GT_EQUAL_TO LT_EQUAL_TO NOT_EQUAL_TO
%left ADD SUB ADD_ASSIGN SUB_ASSIGN INCREMENT DECREMENT
%left DIV MULT 

%right "else" ELSE




%%

program			: declaration_list
			;

declaration_list	: declaration_list declaration
			| declaration
			;

declaration		: var_declaration
			| fun_declaration
			;

var_declaration		: type_specifier var_decl_list EOL 
			;

scoped_var_declaration	: scoped_type_specifier var_decl_list EOL
			;

var_decl_list		: var_decl_list COMMA var_decl_initialise
			| var_decl_initialise
			;

var_decl_initialise	:  var_decl_id
					;

var_decl_id		: ID
			| ID LSQUARE INT_VAL RSQUARE
			;

scoped_type_specifier	: type_specifier
			;

type_specifier		: INT
			| FLOAT
			| DOUBLE
			| CHAR
			| BOOL
			;

fun_declaration		: type_specifier ID LPAREN params RPAREN statement
			| ID LPAREN params RPAREN statement
			;

params			: /*Empty*/
			| param_list
			;

param_list		: param_list EOL param_type_list
			| param_type_list
			;

param_type_list		: type_specifier param_id_list
			;

param_id_list		: param_id_list COMMA param_id
			| param_id
			;

param_id		: ID
			| ID LSQUARE RSQUARE
			;

statement		: expression_stmt
			| compound_stmt
			| selection_stmt
			| iteration_stmt
			| return_stmt
			| break_stmt
			;

compound_stmt		: LBRACE local_declarations statement_list RBRACE // int x; float y; ... statements
			;

local_declarations	: /*Empty*/
			| local_declarations scoped_var_declaration
			;

statement_list		: /*Empty*/
			| statement_list statement
			;

expression_stmt		: expression EOL
			| EOL
			;

selection_stmt		: IF LPAREN simple_expression RPAREN statement %prec "else"
			| IF LPAREN simple_expression RPAREN statement ELSE statement
			;

iteration_stmt		: WHILE LPAREN simple_expression RPAREN statement // TODO: for
			;

return_stmt		: RETURN EOL
			| RETURN expression EOL
			;

break_stmt		: BREAK EOL
			;

expression		: mutable ASSIGN expression
			| mutable ADD_ASSIGN expression
			| mutable SUB_ASSIGN expression
			//| mutable MULT expression 
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
			| unary_rel_expression
			;

unary_rel_expression	: LOGICAL_NOT unary_rel_expression
			| rel_expression
			; 

rel_expression		: sum_expression relop sum_expression
			| sum_expression
			;

relop			: LT_EQUAL_TO
			| LESS_THAN
			| GREATER_THAN
			| GT_EQUAL_TO
			| EQUAL_TO
			| NOT_EQUAL_TO
			;

sum_expression		: sum_expression sumop term
			| term
			;

sumop			: ADD 
			| SUB
			;

term			: term mulop unary_expression
			| unary_expression
			;

mulop			: MULT
			| DIV
			| MODULO
			;

unary_expression	: unaryop unary_expression
			| factor
			;

unaryop			: SUB 
			| MULT
			;

factor			: immutable
			| mutable
			;

mutable			: ID 
			| ID LSQUARE expression RSQUARE
			;

immutable		: LPAREN expression RPAREN 
			| call 
			| constant
			;

call			: ID LPAREN args RPAREN
			;

args			: /*Empty*/
			| arg_list
			;

arg_list		: arg_list COMMA expression
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
