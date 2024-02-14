%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
char* yytext;
%}

DIGIT      [0-9]
WS         [ \t\n]
IDENT     [a-zA-Z]

%%

{WS}       /* Ignore whitespace */
{DIGIT}+   { yylval.num = atoi(yytext); return NUMBER; }
{IDENT}+  { yylval.str = strdup(yytext); return IDENT; }
"+"        {  return PLUS; }
"-"        {  return MINUS; }
"*"        {  return MULTIPLY;}
"/"        {  return DIVIDE;}
"="        {  return EQUALS;}
";"        { return SEMICOLON;}
"("        {  return LPAR; }
")"        { return RPAR; }
"{"        {  return LCB; }
"}"        {  return RCB; }
"["        { return LSB;}
"]"        {return RSB ;}

"##".*      {  }
"/#"[^#]*"#/" {  }
"@var"     {return VAR;}
"Void Main()"  { return MAIN;}  
"@call"        {return CALL;}
.          { fprintf(stderr, "Error: Unexpected character '%s'\n", yytext); }

%%

int yywrap() {
   return 1;
}
