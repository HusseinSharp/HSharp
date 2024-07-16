%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
char* yytext;

#define MAX_INCLUDE_DEPTH 100

static FILE* file_stack[MAX_INCLUDE_DEPTH];
static int file_stack_top = -1;
char current_token_text[256];  // Add this global variable to store the current token 

char** included_files = NULL;
int included_files_count = 0;

void handle_include(const char* filename) {
    const char *ext = strrchr(filename, '.');
    if (!ext || strcmp(ext, ".hslib") != 0) {
        fprintf(stderr, "Error: Invalid file extension for %s. Only .hslib files are allowed.\n", filename);
        exit(EXIT_FAILURE);
    }

    // Check if the file has already been included
    for (int i = 0; i < included_files_count; ++i) {
        if (strcmp(included_files[i], filename) == 0) {
            fprintf(stderr, "Error: File %s has already been included.\n", filename);
            exit(EXIT_FAILURE);
        }
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

    // Add the filename to the list of included files
    included_files = realloc(included_files, sizeof(char*) * (included_files_count + 1));
    if (!included_files) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    included_files[included_files_count] = strdup(filename);
    if (!included_files[included_files_count]) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    included_files_count++;

    // Enter library scope
    enter_scope();

    file_stack[++file_stack_top] = file;
    yypush_buffer_state(yy_create_buffer(file, YY_BUF_SIZE));
    yy_switch_to_buffer(yy_create_buffer(file, YY_BUF_SIZE));
    yylineno = 1;

    printf("opening file %s\n", filename);
}

void finish_include() {
    if (file_stack_top >= 0) {
        fclose(file_stack[file_stack_top]);
        file_stack[file_stack_top] = NULL;
        file_stack_top--;
        yypop_buffer_state();
        if (file_stack_top < 0) {
            // Exit library scope
            exit_scope();
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
FLOAT      {DIGIT}+"."{DIGIT}+
STRING     \"[^\"]*\"

%option stack
%x INCL FUNC_BODY

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

{WS}        { /* Ignore whitespace, but count newlines */
    char *p = yytext;
    while (*p) {
        if (*p == '\n') {
            yylineno++;
        }
        p++;
    }
}
{DIGIT}+    { strncpy(current_token_text, yytext, sizeof(current_token_text)); yylval.num = atoi(yytext); return NUMBER; }
"-"{DIGIT}+ { strncpy(current_token_text, yytext, sizeof(current_token_text)); yylval.num = atoi(yytext); return NUMBER; }
{FLOAT}+    { strncpy(current_token_text, yytext, sizeof(current_token_text)); yylval.fnum = atof(yytext); return FLOAT_NUMBER; }
"-"{FLOAT}+ { strncpy(current_token_text, yytext, sizeof(current_token_text)); yylval.fnum = atof(yytext); return FLOAT_NUMBER; }
{STRING}    { strncpy(current_token_text, yytext, sizeof(current_token_text)); yylval.str = strdup(yytext); return STRING_LITERAL; }
"Var"       { strncpy(current_token_text, yytext, sizeof(current_token_text)); return VAR; }
"Void Main()" { strncpy(current_token_text, yytext, sizeof(current_token_text)); return MAIN; }
"Call"      { strncpy(current_token_text, yytext, sizeof(current_token_text)); return CALL; }
"Library"   { strncpy(current_token_text, yytext, sizeof(current_token_text)); return LIBDEF; }
"if"        { strncpy(current_token_text, yytext, sizeof(current_token_text)); return IF; }
"else"      { strncpy(current_token_text, yytext, sizeof(current_token_text)); return ELSE; }
"else if"   {strncpy(current_token_text, yytext, sizeof(current_token_text)); return ELSEIF;}
"=="        { strncpy(current_token_text, yytext, sizeof(current_token_text)); return EQ; }
"!="        { strncpy(current_token_text, yytext, sizeof(current_token_text)); return NEQ; }
"<="        { strncpy(current_token_text, yytext, sizeof(current_token_text)); return LEQ; }
">="        { strncpy(current_token_text, yytext, sizeof(current_token_text)); return GEQ; }
"<"         { strncpy(current_token_text, yytext, sizeof(current_token_text)); return LT; }
">"         { strncpy(current_token_text, yytext, sizeof(current_token_text)); return GT; }
{IDENT}     { strncpy(current_token_text, yytext, sizeof(current_token_text)); yylval.str = strdup(yytext); return IDENT; }
"+"         { strncpy(current_token_text, yytext, sizeof(current_token_text)); return PLUS; }
"-"         { strncpy(current_token_text, yytext, sizeof(current_token_text)); return MINUS; }
"*"         { strncpy(current_token_text, yytext, sizeof(current_token_text)); return MULTIPLY; }
"/"         { strncpy(current_token_text, yytext, sizeof(current_token_text)); return DIVIDE; }
"="         { strncpy(current_token_text, yytext, sizeof(current_token_text)); return EQUALS; }
";"         { strncpy(current_token_text, yytext, sizeof(current_token_text)); return SEMICOLON; }
"("         { strncpy(current_token_text, yytext, sizeof(current_token_text)); return LPAR; }
")"         { strncpy(current_token_text, yytext, sizeof(current_token_text)); return RPAR; }
"{"         { strncpy(current_token_text, yytext, sizeof(current_token_text)); return LCB; }
"}"         { strncpy(current_token_text, yytext, sizeof(current_token_text)); return RCB; }
"["         { strncpy(current_token_text, yytext, sizeof(current_token_text)); return LSB; }
"]"         { strncpy(current_token_text, yytext, sizeof(current_token_text)); return RSB; }

"##".*      { /* ignore comments */ }
"/#"[^#]*"#/" { }
.           { fprintf(stderr, "Error: Unexpected character '%s' at line %d\n", yytext, yylineno); strncpy(current_token_text, yytext, sizeof(current_token_text)); }

%%

int yywrap() {
    if (file_stack_top >= 0) {
        finish_include();
        return 1;
    }
    return 1;
}
