%option noyywrap

%{
#include "parser.tab.hh"
using namespace std;
#define YY_DECL extern "C" int yylex()
%}

%%
":"             	{ cout << "Colon" << endl; return COLON; }
","             	{ return COMMA; }
"["             	{ return LSQUARE; }
"]"             	{ return RSQUARE; }
"{"             	{ return LBRACE; }
"}"             	{ return RBRACE; }
"("			{ return LPAREN; }
")"			{ return RPAREN; }
[0-9]+\.[0-9]+		{ yylval.number=atoi(yytext); return DOUBLE; }
[0-9]+          	{ yylval.number=atoi(yytext); return INTEGER; }
["][^"]*["]     	{ yylval.string=strdup(yytext); return STRING; }
[a-zA-Z][a-zA-Z0-9]* 	{  }
\n			{ linenum++; }
[ \t]			;
%%



void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
  exit(1);
}
