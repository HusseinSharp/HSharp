%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testparser.tab.h"
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
IDENT      [a-zA-Z]

%option stack
%x INCL

%%

"Import" {
    print_debug("@import detected");
    BEGIN(INCL); return IMPORT;
}

<INCL>[ \t]*\"[a-zA-Z0-9]+\.hslib\" {
    char filename[256];
    sscanf(yytext, " \"%[^\"]\"", filename);
    handle_include(filename);
    BEGIN(0);
    print_debug("Including file");
    yyparse();
    return FILENAME;
}

<INCL><<EOF>> {
    if (file_stack_top >= 0) {
        print_debug("End of included file");
        finish_include();
    }
    BEGIN(0);
    return 0;
}

{WS}        /* Ignore whitespace */
{DIGIT}+    { yylval.num = atoi(yytext);  return NUMBER; }
{IDENT}     { yylval.str = strdup(yytext);  return IDENT; }
"+"         { print_debug("PLUS detected"); return PLUS; }
"-"         { print_debug("MINUS detected"); return MINUS; }
"*"         { print_debug("MULTIPLY detected"); return MULTIPLY; }
"/"         { print_debug("DIVIDE detected"); return DIVIDE; }
"="         { print_debug("EQUALS detected"); return EQUALS; }
";"         { print_debug("SEMICOLON detected"); return SEMICOLON; }
"("         { print_debug("LPAR detected"); return LPAR; }
")"         { print_debug("RPAR detected"); return RPAR; }
"{"         { print_debug("LCB detected"); return LCB; }
"}"         { print_debug("RCB detected"); return RCB; }
"["         { print_debug("LSB detected"); return LSB; }
"]"         { print_debug("RSB detected"); return RSB; }
"Free"      { print_debug("FREEMEM detected"); return FREEMEM; }
"##".*      { print_debug("Comment detected"); /* ignore comments */ }
"/#"[^#]*"#/" { print_debug("Block comment detected"); /* ignore block comments */ }
"Var"       { print_debug("VAR detected"); return VAR; }
"Void Main()" { print_debug("MAIN detected"); return MAIN; }
"Call"      { print_debug("CALL detected"); return CALL; }
"Library"   { return LIBDEF; }
.           { fprintf(stderr, "Error: Unexpected character '%s'\n", yytext); }

%%

int yywrap() {
    if (file_stack_top >= 0) {
        print_debug("End of included file");
        finish_include();
        return 0;
    }
    return 1;
}
