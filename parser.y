%code requires{	
	#include <cstdio>
	#include <iostream>
	
	#include "ast_headers.hpp"
  	//#define YYDEBUG 1
  	using namespace std;
	//extern Value *g_ast; // A way of getting the AST out
	int yylex();
	void yyerror(const char *);
	
}

%union{
	// Need pointer types for types of which we are going to dynamically allocate new objects(eg new DeclarationList())
  	char primitive_char_t;
	short primitive_short_t;
  	int primitive_int_t;
	long primitive_long_t;
	double primitive_double_t;
	char* primitive_string_t
	void* ptr_t;
	bool bool_t;

	DeclarationList* declaration_list_t;
	Declaration* declaration_t;
	TypeSpecifier type_specifier_t;
	VarDeclInitList* var_decl_init_list_t;
	VarDeclInit* var_decl_or_init_t;
	VarDeclId* var_decl_id_t;
	SimpleExpression* simple_expression_t;
	AndExpression* and_expression_t;
	UnaryRelExpression* unary_rel_expression_t;
	Relop relop_t;
	ParamList* param_list_t;
	ParamIdDecl* param_id_decl_t;
	ParamId* param_id_t;
	ExpressionStmt* expression_stmt_t;
	Expression* expression_t;
	Mutable* mutable_t;
	AssignOp* assign_op_t;
	Statement* statement_t;
	CompoundStmt* compound_stmt_t;
	IfStmt* if_stmt_t;
	WhileStmt* while_stmt_t;
	ReturnStmt* return_stmt_t;
	BreakStmt* break_stmt_t;
	Sumop sumop_t;
	Mulop mulop_t;
	Boolean* boolean_t;
	Number* number_t;
	Constant* constant_t;
	ArgList* arg_list_t;
	Call* call_t;
	RelExpression* rel_expression_t;
	SumExpression* sum_expression_t;
	Term* term_t;
	Factor* factor_t;
	Immutable* immutable_t;
}

%token ADD ADD_ASSIGN ASSIGN AUTO BITWISE_AND BITWISE_AND_ASSIGN BITWISE_NOT BITWISE_OR BITWISE_OR_ASSIGN BITWISE_XOR BITWISE_XOR_ASSIGN BOOL BREAK CASE CHAR COLON COMMA CONST CONTINUE DECREMENT DEFAULT DIV DIV_ASSIGN DO DOUBLE ELLIPSIS ELSE ENUM EOL EQUAL_TO EXTERN FALSE FLOAT FOR GOTO GT_EQUAL_TO IF INCREMENT INT LBRACE LOGICAL_AND LOGICAL_NOT LOGICAL_OR LONG LPAREN LSQUARE LT_EQUAL_TO MODULO MODULO_ASSIGN MUL MUL_ASSIGN NOT_EQUAL_TO RBRACE REGISTER RETURN RPAREN RSQUARE SHORT SIGNED SIZEOF STATIC STRUCT SUB SUB_ASSIGN SWITCH TERNARY TRUE TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE

%token <primitive_int_t> INT_VAL 
%token <primitive_double_t> DOUBLE_VAL 
%token <primitive_string_t> STRING_VAL ID
%token <primitive_char_t> CHAR_VAL


%type <declaration_list_t> declaration_list
%type <declaration_t> declaration var_declarations fun_declaration
%type <type_specifier_t> type_specifier
%type <var_decl_init_list_t> var_decl_init_list
%type <var_decl_or_init_t> var_decl_or_init
%type <var_decl_id_t> var_decl_id
%type <simple_expression_t> simple_expression
%type <and_expression_t> and_expression
%type <unary_rel_expression_t> unary_rel_expression
%type <relop_t> relop
%type <param_id_t> param_id
%type <param_list_t> param_list params
%type <param_id_decl_t> param_id_decl
%type <expression_stmt_t> expression_stmt
%type <expression_t> expression
%type <mutable_t> mutable
%type <assign_op_t> ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN BITWISE_AND_ASSIGN BITWISE_OR_ASSIGN INCREMENT DECREMENT
%type <compound_stmt_t> compound_stmt statement_list
%type <statement_t> statement
%type <if_stmt_t> if_stmt
%type <while_stmt_t> while_stmt
%type <return_stmt_t> return_stmt
%type <sumop_t> sumop
%type <mulop_t> mulop
%type <break_stmt_t> break_stmt
%type <boolean_t> boolean
%type <number_t> number
%type <constant_t> constant
%type <arg_list_t> arg_list args
%type <call_t> call
%type <rel_expression_t> rel_expression
%type <sum_expression_t> sum_expression
%type <term_t> term
%type <factor_t> factor
%type <immutable_t> immutable

%type <primitive_bool_t> TRUE FALSE
//%type <string_t>   INT FLOAT DOUBLE CHAR LONG SHORT UNSIGNED BOOL
//%type <value_t> constant number boolean

%left LESS_THAN GREATER_THAN ASSIGN GT_EQUAL_TO LT_EQUAL_TO NOT_EQUAL_TO
%left ADD SUB ADD_ASSIGN SUB_ASSIGN INCREMENT DECREMENT
%left DIV MUL

%right "else" ELSE




%%


declaration_list	: declaration_list declaration {$1->add($2); $$ = $1 }
			| declaration {$$ = new DeclarationList(); $$->add($1); }
			;

declaration		: var_declarations {$$ = $1}
			| fun_declaration {$$ = $1}
			;

var_declarations	: type_specifier var_decl_init_list EOL {$$ = new VarDeclarations($1);} // int x, y, z=1; 
			;
/*
scoped_var_declaration	: scoped_type_specifier var_decl_init_list EOL
			;
*/

var_decl_init_list	: var_decl_init_list COMMA var_decl_or_init {$1->add($3); $$ = $1;}
			| var_decl_or_init {$$ = new VarDeclInitList(); $$->add($1);}
			;

var_decl_or_init	: var_decl_id ASSIGN simple_expression {$$ = new VarDeclInit($1, $3);}
			| var_decl_id {$$ = new VarDeclInit($1);}
			;

var_decl_id		: ID { $$ = new VarDeclId($1);}
			| ID LSQUARE INT_VAL RSQUARE { $$ = new VarDeclId($1, $3);}
			;
/*
			// modifier_list can be empty, so this means they are optional on either side of the type_specifier

			// This grammar allows any number of modifiers in a list, but the standard only allows one of
			// each var_modifier and any number of type_qualifiers, so check for this in AST
scoped_type_specifier	:type_specifier
			 // | modifier_list type_specifier modifier_list 
			;
*/

type_specifier		: INT {$$ = TypeSpecifier::int_t}
			| FLOAT {$$ = TypeSpecifier::float_t}
			| DOUBLE {$$ = TypeSpecifier::double_t}
			| CHAR {$$ = TypeSpecifier::char_t}
			| BOOL {$$ = TypeSpecifier::bool_t}
			;
/*
modifier_list		:---empty---
			| modifier_list type_qualifier
			| modifier_list var_modifier
			;
 
type_qualifier		: CONST
			| VOLATILE
			;

var_modifier		: sign_var_modifier
			| length_var_modifier
			| scope_var_modifier
			;

sign_var_modifier	: UNSIGNED
			| SIGNED
			;

length_var_modifier	: LONG
			| SHORT
			;

scope_var_modifier	: AUTO
			| STATIC
			| REGISTER
			| EXTERN
			;

*/

fun_declaration		: type_specifier ID LPAREN params RPAREN statement {$$ = new FunDeclaration($1, $2, $4, $6);}
			//| ID LPAREN params RPAREN statement
			;

params			: /*Empty*/ {$$ = new ParamList();} // Empty paramlist
			| param_list {$$ = $1}
			;

param_list		: param_list COMMA param_id_decl {$1->add($3); $$ = $1;}
			| param_id_decl {$$ = new ParamList(); $$->add($1);}
			;

param_id_decl		: type_specifier param_id {$$ = new ParamIdDecl($1, $2); }
			;
/*
param_type_list		: type_specifier param_id_list
			;

param_id_list		: param_id_list COMMA param_id
			| param_id
			;
*/
param_id		: ID {$$ = new ParamId($1, false);}
			| ID LSQUARE RSQUARE {$$ = new ParamId($1, true);} // bool sets `is_array`
			;

statement		: expression_stmt {$$ = $1;}
			| compound_stmt {$$ = $1;}
			| if_stmt {$$ = $1;}
			| while_stmt {$$ = $1;}
			| return_stmt {$$ = $1;}
			| break_stmt {$$ = $1;}
			//| local_declarations
			| var_declarations {$$ = $1;}//***********************************
			;

expression_stmt		: expression EOL {$$ = new ExpressionStmt($1);}
			| EOL {$$ = new ExpressionStmt();}
			;

compound_stmt		: LBRACE statement_list RBRACE {$$ = $2}// int x; float y; ... statements
			;
/*
local_declarations	: var_declarations
			// | scoped_var_declaration
			;
*/
//****************************************************************************************************************
// sort out instantiatition of new compund stmt
statement_list		: /*Empty*/ {$$ = new CompoundStmt();}
			| statement_list statement {$1->add($2); $$ = $1;}
			;

if_stmt			: IF LPAREN simple_expression RPAREN statement %prec "else" {$$ = new IfStmt($3, $5);}
			| IF LPAREN simple_expression RPAREN statement ELSE statement {$$ = new IfStmt($3, $5, $7);}
			;

while_stmt		: WHILE LPAREN simple_expression RPAREN statement {$$ = new WhileStmt($3, $5);}
			//| FOR LPAREN var_declaration EOL expression EOL expression RPAREN statement
			;

return_stmt		: RETURN EOL {$$ = new ReturnStmt();}
			| RETURN expression EOL {$$ = new ReturnStmt($2);}
			;

break_stmt		: BREAK EOL {$$ = new BreakStmt()}
			;

expression		: mutable ASSIGN expression {$$ = new MutableExpression($1, AssignOp::assign, $3);}
			| mutable ADD_ASSIGN expression {$$ = new MutableExpression($1, AssignOp::add_assign, $3);}
			| mutable SUB_ASSIGN expression {$$ = new MutableExpression($1, AssignOp::sub_assign, $3);}
			| mutable MUL_ASSIGN expression  {$$ = new MutableExpression($1, AssignOp::mul_assign, $3);}
			| mutable DIV_ASSIGN expression {$$ = new MutableExpression($1, AssignOp::div_assign, $3);}
			| mutable BITWISE_AND_ASSIGN expression {$$ = new MutableExpression($1, AssignOp::bitwise_and_assign, $3);}
			| mutable BITWISE_OR_ASSIGN expression {$$ = new MutableExpression($1, AssignOp::bitwise_or_assign, $3);}
			| mutable INCREMENT {$$ = new MutableExpression($1, AssignOp::increment);}
			| mutable DECREMENT {$$ = new MutableExpression($1, AssignOp::decrement);}
			| simple_expression {$$ = $1;} // Because SimpleExpression inherits from expression, therefore SimpleExpression IS AN Expression
			;

simple_expression	: simple_expression LOGICAL_OR and_expression {$1->add($3); $$ = $1 ;}
			| and_expression {$$ = new SimpleExpression(); $$->add($1)}
			;

and_expression		: and_expression LOGICAL_AND unary_rel_expression {$1->add($3); $$ = $1; }
			| unary_rel_expression  {$$ = new AndExpression(); $$->add($1);}
			;

unary_rel_expression	: LOGICAL_NOT unary_rel_expression {$2->logical_not(); $$ = $2;}
			| rel_expression {$$ = new UnaryRelExpression($1);}
			; 

rel_expression		: sum_expression relop sum_expression
			| sum_expression
			;

relop			: LT_EQUAL_TO {$$ = Relop::lt_equal_to}
			| LESS_THAN {$$ = Relop::less_than}
			| GREATER_THAN {$$ = Relop::greater_than}
			| GT_EQUAL_TO {$$ = Relop::gt_equal_to}
			| EQUAL_TO {$$ = Relop::equal_to}
			| NOT_EQUAL_TO {$$ = Relop::not_equal_to}
			;

sum_expression		: sum_expression sumop term {$1->add_op($2); $1->add_term($3); $$ = $1;}
			| term {$$ = new SumExpression(); $$->add_term($1);}
			;

sumop			: ADD {$$ = Sumop::add;}
			| SUB {$$ = Sumop::sub;}
			;

term			: term mulop factor {$1->add_op($2); $1->add_factor($3); $$ = $1;}
			| factor {$$ = new Term(); $$->add_factor($1);}
			;

mulop			: MUL {$$ = Mulop::mul;}
			| DIV {$$ = Mulop::div;}
			| MODULO {$$ = Mulop::modulo;}
			;

factor			: SUB factor {$2->negate();} // Unary minus
			| immutable {$$ = $1}
			| mutable {$$ = $1}
			;

mutable			: ID {$$= new Mutable($1);}
			| ID LSQUARE expression RSQUARE {$$= new Mutable($1, $3);}
			;

immutable		: LPAREN expression RPAREN {$$ = $2;}
			| call {$$ = $1;}
			| constant {$$ = $1;}
			;

call			: ID LPAREN args RPAREN {$$ = new Call()}
			;

args			: /*Empty*/ {$$ = new ArgList();}
			| arg_list {$$ = $1;}
			;

arg_list		: arg_list COMMA expression {$1->add($3); $$ = $1;}
			| expression {$$ = new ArgList(); $$->add($1);}
			;

constant		: number {$$ = $1}
			| boolean {$$ = $1}
			| CHAR_VAL {$$ = new Char($1);   }
			| STRING_VAL {$$ = new String($1);   }
			;

number			: INT_VAL {$$ = new Int($1);   }
			| DOUBLE_VAL {$$ = new Double($1);   }
			;

boolean			: TRUE {$$ = new Boolean(true);   }
			| FALSE {$$ = new Boolean(false);   }
			;

%%
int main() 
{	
	//yydebug = 1;
	while(yyparse());
}
