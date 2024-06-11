%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
char* yytext;

#define MAX_INCLUDE_DEPTH 100

static FILE* file_stack[MAX_INCLUDE_DEPTH];
static int file_stack_top = -1;

void handle_include(const char* filename) {
    const char *ext = strrchr(filename, '.');
    if (!ext || strcmp(ext, ".hslib") != 0) {
        fprintf(stderr, "Error: Invalid file extension for %s. Only .hslib files are allowed.\n", filename);
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening library file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    if (file_stack_top >= MAX_INCLUDE_DEPTH - 1) {
        fprintf(stderr, "Error: Maximum include depth exceeded\n");
        exit(EXIT_FAILURE);
    }
    
    file_stack[++file_stack_top] = file;
    yypush_buffer_state(yy_create_buffer(file, YY_BUF_SIZE));
    printf("opening file %s\n", filename);
}

void finish_include() {
    if (file_stack_top >= 0) {
        fclose(file_stack[file_stack_top]);
        file_stack[file_stack_top] = NULL;
        file_stack_top--;
        yypop_buffer_state();
        if (file_stack_top < 0) {
            printf("closing library file\n");
        }
    }
}

void print_debug(const char *msg) {
    printf("DEBUG: %s\n", msg);
}
%}

DIGIT      [0-9]
WS         [ \t\n]
IDENT      [a-zA-Z_][a-zA-Z0-9_]*


%option stack
%x INCL

%%

"Import" {
  
    BEGIN(INCL); return IMPORT;
}

<INCL>[ \t]*\"[a-zA-Z0-9]+\.hslib\" {
    char filename[256];
    sscanf(yytext, " \"%[^\"]\"", filename);
    handle_include(filename);
    BEGIN(0);
    yyparse();
    return FILENAME;
}

<INCL><<EOF>> {
    if (file_stack_top >= 0) {
        
        finish_include();
    }
    BEGIN(0);
    return 0;
}


{WS}        /* Ignore whitespace */
{DIGIT}+    { yylval.num = atoi(yytext);  return NUMBER; }
"Var"       { return VAR; }
"Void Main()" {  return MAIN; }
"Call"      {  return CALL; }
"Library"   { return LIBDEF; }
"Free"      {  return FREEMEM; }
{IDENT}     { yylval.str = strdup(yytext);  return IDENT; }
"+"         {  return PLUS; }
"-"         { return MINUS; }
"*"         {  return MULTIPLY; }
"/"         {  return DIVIDE; }
"="         {  return EQUALS; }
";"         {  return SEMICOLON; }
"("         {  return LPAR; }
")"         {  return RPAR; }
"{"         {  return LCB; }
"}"         {  return RCB; }
"["         { return LSB; }
"]"         {  return RSB; }
"##".*      { /* ignore comments */ }
"/#"[^#]*"#/" { print_debug("Block comment detected"); /* ignore block comments */ }
.           { fprintf(stderr, "Error: Unexpected character '%s'\n", yytext); }


%%

int yywrap() {
    if (file_stack_top >= 0) {
       
        finish_include();
        return 0;
    }
    return 1;
}
