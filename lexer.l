%{
#include <stdio.h>
int yywrap() {
    return 1; // Indicate that there are no more files to scan
}

%}


DIGIT       [0-9]
WS          [ \t\n]

%%

{WS}        /* Ignore whitespace */
{DIGIT}+    { printf("NUMBER: %s\n", yytext); }
"+"         { printf("PLUS\n"); }
"-"         { printf("MINUS\n"); }
"*"         { printf("MULTIPLY\n"); }
"/"         { printf("DIVIDE\n"); }
"("         { printf("LEFT_PAREN\n"); }
")"         { printf("RIGHT_PAREN\n"); }
"{"         { printf("LEFT_CURLY_BRACKET)}
"}"         { printf("RIGHT_CURLY_BRACKET)}
.           { fprintf(stderr, "Error: Unexpected character '%s'\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

