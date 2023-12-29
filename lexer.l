%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
char* yytext;
%}

DIGIT      [0-9]
WS         [ \t\n]
STRING     [a-zA-Z]

%%

{WS}       /* Ignore whitespace */
{DIGIT}+   { yylval.num = atoi(yytext); return NUMBER; }
{STRING}+  { yylval.str = strdup(yytext); return STRING; }
"+"        { printf("PLUS\n"); return PLUS; }
"-"        { printf("MINUS\n"); return MINUS; }
"*"        { printf("MULTIPLY\n"); return MULTIPLY;}
"/"        { printf("DIVIDE\n"); return DIVIDE;}
"="        { printf("EQUALS\n"); return EQUALS;}
";"        { printf("SEMICOLON\n"); return SEMICOLON;}
"("        { printf("LEFT_PAREN\n"); return LPAR; }
")"        { printf("RIGHT_PAREN\n"); return RPAR; }
"{"        { printf("LEFT_CURLY_BRACKET\n"); return LCB; }
"}"        { printf("RIGHT_CURLY_BRACKET\n"); return RCB; }
\"         {printf("double quote\n");return DBQT;}
"##".*     { printf("single line comment\n"); }
"/#"[^#]*"#/" { printf("multiple line comment\n"); }
"@var"     {printf("variable declaration\n"); return VAR;}
"Void Main()"  {printf("main method\n"); return MAIN;}
"for" {printf("for loop");    return FOR;}
"while" {printf("while loop"); return WHILE;}
"if"  {printf("if statement"); return IF;}
"elif" {printf("else if statement"); return ELIF;}
"else" {printf("else statement"); return ELSE;}
.          { fprintf(stderr, "Error: Unexpected character '%s'\n", yytext); }

%%

int yywrap() {
   return 1;
}