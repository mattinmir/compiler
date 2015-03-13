%option noyywrap

%{
#include "parser.tab.hh"
using namespace std;
int linenum = 0;
%}

%%
":"             		{ return COLON; }
","             		{ return COMMA; }
";"             		{ return EOL; }

"["             		{ return LSQUARE; }
"]"             		{ return RSQUARE; }
"{"             		{ return LBRACE; }
"}"             		{ return RBRACE; }
"("						{ return LPAREN; }
")"						{ return RPAREN; }

"+"						{ return ADD; }
"-"						{ return SUB; }
"*"						{ return MUL; }
"/"						{ return DIV; }
"%"						{ return(MODULO); }

"=="					{ return EQUAL_TO; }
"!="					{ return NOT_EQUAL_TO; }
"|"						{ return BITWISE_OR; }
"||"					{ return LOGICAL_OR; }
"&"						{ return BITWISE_AND; }
"&&"					{ return LOGICAL_AND; }
"^"						{ return BITWISE_XOR; }
"?"						{ return TERNARY;}


"="						{ return ASSIGN; }
"+="					{ return ADD_ASSIGN; }
"-="					{ return SUB_ASSIGN; }
"*="					{ return MUL_ASSIGN; }
"/="					{ return DIV_ASSIGN; }
"%="					{ return(MODULO_ASSIGN); }
"&="					{ return(BITWISE_AND_ASSIGN); }
"^="					{ return(BITWISE_XOR_ASSIGN); }
"|="					{ return(BITWISE_OR_ASSIGN); }

[0-9]+\.[0-9]+			{ yylval.double_t=atoi(yytext); return DOUBLE; }
[0-9]+          		{ yylval.int_t=atoi(yytext); return INTEGER; }
["][^"]*["]     		{ yylval.string_t=strdup(yytext); return STRING; }
[a-zA-Z][a-zA-Z0-9]* 	{ return ID; }
\n						{linenum++;}
[ \t]					;
%%



void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
  exit(1);
}
