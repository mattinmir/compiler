%option noyywrap

%{
#include "parser.tab.hh"
using namespace std;
int linenum = 0;
%}

%%

"auto"			{ return AUTO; }
"break"			{ return BREAK; }
"case"			{ return CASE; }
"char"			{ return CHAR; }
"const"			{ return CONST; }
"continue"		{ return CONTINUE; }
"default"		{ return DEFAULT; }
"do"			{ return DO; }
"double"		{ return DOUBLE; }
"else"			{ return ELSE; }
"enum"			{ return ENUM; }
"extern"		{ return EXTERN; }
"float"			{ return FLOAT; }
"for"			{ return FOR; }
"goto"			{ return GOTO; }
"if"			{ return IF; }
"int"			{ return INT; }
"long"			{ return LONG; }
"register"		{ return REGISTER; }
"return"		{ return RETURN; }
"short"			{ return SHORT; }
"signed"		{ return SIGNED; }
"sizeof"		{ return SIZEOF; }
"static"		{ return STATIC; }
"struct"		{ return STRUCT; }
"switch"		{ return SWITCH; }
"typedef"		{ return TYPEDEF; }
"union"			{ return UNION; }
"unsigned"		{ return UNSIGNED; }
"void"			{ return VOID; }
"volatile"		{ return VOLATILE; }
"while"			{ return WHILE; }

"..."			{ return ELLIPSIS; }
":"             	{ return COLON; }
","             	{ return COMMA; }
";"             	{ return EOL; }

"["            		{ return LSQUARE; }
"]"            		{ return RSQUARE; }
"{"            		{ return LBRACE; }
"}"            		{ return RBRACE; }
"("			{ return LPAREN; }
")"			{ return RPAREN; }

"+"			{ return ADD; }
"-"			{ return SUB; }
"*"			{ return MUL; }
"/"			{ return DIV; }
"%"			{ return MODULO; }


"<"			{ return LESS_THAN; }
">"			{ return GREATER_THAN; }
"<="			{ return LT_EQUAL_TO; }
">="			{ return GT_EQUAL_TO; }
"=="			{ return EQUAL_TO; }
"!="			{ return NOT_EQUAL_TO; }
"!"			{ return LOGICAL_NOT; }
"~"			{ return BITWISE_NOT; }
"|"			{ return BITWISE_OR; }
"||"			{ return LOGICAL_OR; }
"&"			{ return BITWISE_AND; }
"&&"			{ return LOGICAL_AND; }
"^"			{ return BITWISE_XOR; }
"?"			{ return TERNARY;}


"="			{ return ASSIGN; }
"+="			{ return ADD_ASSIGN; }
"-="			{ return SUB_ASSIGN; }
"*="			{ return MUL_ASSIGN; }
"/="			{ return DIV_ASSIGN; }
"%="			{ return MODULO_ASSIGN; }
"&="			{ return BITWISE_AND_ASSIGN; }
"^="			{ return BITWISE_XOR_ASSIGN; }
"|="			{ return BITWISE_OR_ASSIGN; }

[0-9]+\.[0-9]+		{ yylval.double_t=atoi(yytext); return DOUBLE_VAL; } 
[0-9]+          	{ yylval.int_t=atoi(yytext); return INT_VAL; }
["][^"]*["]     	{ return STRING_VAL; }
['][^']?[']		{ return CHAR_VAL; }
[_a-zA-Z][_a-zA-Z0-9]* 	{ return ID; }
\n			{linenum++;}
[ \t]			;
%%



void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
  exit(1);
}
