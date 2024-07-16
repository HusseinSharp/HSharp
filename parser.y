%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "hashtable.h"
#include "garbagecollection.h"
#include "lexer.h"

int array_size;
int twod_array_size_row;
int twod_array_size_col;

extern int yylineno;
extern char current_token_text[];

void yyerror(const char *s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
    fprintf(stderr, "Current token: %s\n", current_token_text);
}

void enter_scope();
void exit_scope();

%}

%union {
    int num;
    float fnum;
    char *str;
    struct {
        int type;
        union {
            int intValue;
            float floatValue;
            char *strValue;
        } value;
    } exprval;
}

%token <num> NUMBER
%token <fnum> FLOAT_NUMBER
%token <str> STRING_LITERAL
%token <str> EQUALS
%token <str> SEMICOLON
%token <str> PLUS
%token <str> MINUS
%token <str> MULTIPLY
%token <str> DIVIDE
%token LPAR
%token RPAR
%token <str> LCB
%token <str> RCB
%token <str> MAIN
%token <str> LIBDEF
%token FREEMEM
%token <str> CALL
%token VAR
%token FILENAME
%token <str> IDENT
%token <str> LSB
%token <str> RSB
%token <str> COMMA
%token IMPORT

%type <exprval> expr
%type <str> sexpr
%type <str> var_declaration assignment display 
%type <str> statement_list
%type <str> libprogstart

%left PLUS MINUS
%left MULTIPLY DIVIDE

%start program

%%

program: start_stmt
       ;

start_stmt: libprogstart mainprog
          | mainprog
          | libprogstart
          | /* empty */
          ;

mainprog: import_list_opt MAIN LCB { enter_scope(); } statement_list RCB { exit_scope(); } SEMICOLON
        ;

import_list_opt: import_list
               | /* empty */
               ;

import_list: import_list IMPORT_stmt
           | IMPORT_stmt
           ;

IMPORT_stmt: IMPORT FILENAME ;

libprogstart: LIBDEF LCB { enter_scope(); } statement_list RCB { exit_scope(); } SEMICOLON;

statement_list: /* empty */
              | statement_list statement SEMICOLON
              ;

statement: var_declaration
         | assignment
         | display
         | freememory
         | block
         ;

block: LCB { enter_scope(); } statement_list RCB { exit_scope(); }
     ;

var_declaration:  VAR IDENT EQUALS expr { 
                   if ($4.type == TYPE_INT) {
                       insert_variable($2);
                       update_variable($2, $4.value.intValue);
                   } else if ($4.type == TYPE_FLOAT) {
                       insert_float_variable($2);
                       update_float_variable($2, $4.value.floatValue);
                   } else {
                       insert_string_variable($2);
                       update_string_variable($2, $4.value.strValue);
                   }
                 }
               | VAR IDENT EQUALS sexpr { insert_string_variable($2); update_string_variable($2, $4); }
               ;

assignment: IDENT EQUALS expr { 
                if ($3.type == TYPE_INT) 
                    update_variable($1, $3.value.intValue); 
                else if ($3.type == TYPE_FLOAT) 
                    update_float_variable($1, $3.value.floatValue);
                else 
                    update_string_variable($1, $3.value.strValue); 
            }
          | IDENT EQUALS sexpr { update_string_variable($1, $3); }
          ;

display: CALL IDENT { display_variable($2); }
       ;

freememory: FREEMEM LPAR IDENT RPAR {
    void *ptr = get_memory_block_pointer($3);
    if(ptr) {
        remove_from_garbage_collection(ptr);
    } else {
        fprintf(stderr, "Error: Variable '%s' not found\n", $3);
    }
}

expr: NUMBER { $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = $1 }; }
    | FLOAT_NUMBER { $$ = (typeof($$)){ .type = TYPE_FLOAT, .value.floatValue = $1 }; }
    | IDENT { 
        int intValue = get_variable_value($1); 
        if (intValue != -1) {
            $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = intValue };
        } else {
            float floatValue = get_float_variable_value($1);
            if (floatValue != -1.0) {
                $$ = (typeof($$)){ .type = TYPE_FLOAT, .value.floatValue = floatValue };
            } else {
                char *strValue = get_string_variable_value($1);
                $$ = (typeof($$)){ .type = TYPE_STRING, .value.strValue = strValue };
            }
        }
    }
    | expr PLUS expr { 
        if ($1.type == TYPE_STRING || $3.type == TYPE_STRING) {
            char *str1 = ($1.type == TYPE_STRING) ? $1.value.strValue : ($1.type == TYPE_INT) ? int_to_string($1.value.intValue) : float_to_string($1.value.floatValue);
            char *str2 = ($3.type == TYPE_STRING) ? $3.value.strValue : ($3.type == TYPE_INT) ? int_to_string($3.value.intValue) : float_to_string($3.value.floatValue);
            $$ = (typeof($$)){ .type = TYPE_STRING, .value.strValue = concatStrings(str1, str2) };
        } else if ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) {
            $$ = (typeof($$)){ .type = TYPE_FLOAT, .value.floatValue = ($1.type == TYPE_INT ? $1.value.intValue : $1.value.floatValue) + ($3.type == TYPE_INT ? $3.value.intValue : $3.value.floatValue) };
        } else {
            $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = $1.value.intValue + $3.value.intValue };
        }
    }
    | expr MINUS expr { 
        if ($1.type == TYPE_STRING || $3.type == TYPE_STRING) {
            fprintf(stderr, "Error: Cannot subtract strings\n");
            $$ = (typeof($$)){ .type = TYPE_FLOAT, .value.floatValue = NAN };
        } else if ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) {
            $$ = (typeof($$)){ .type = TYPE_FLOAT, .value.floatValue = ($1.type == TYPE_INT ? $1.value.intValue : $1.value.floatValue) - ($3.type == TYPE_INT ? $3.value.intValue : $3.value.floatValue) };
        } else {
            $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = $1.value.intValue - $3.value.intValue };
        }
    }
    | expr MULTIPLY expr { 
        if ($1.type == TYPE_STRING || $3.type == TYPE_STRING) {
            fprintf(stderr, "Error: Cannot multiply strings\n");
            $$ = (typeof($$)){ .type = TYPE_FLOAT, .value.floatValue = NAN };
        } else if ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) {
            $$ = (typeof($$)){ .type = TYPE_FLOAT, .value.floatValue = ($1.type == TYPE_INT ? $1.value.intValue : $1.value.floatValue) * ($3.type == TYPE_INT ? $3.value.intValue : $3.value.floatValue) };
        } else {
            $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = $1.value.intValue * $3.value.intValue };
        }
    }
    | expr DIVIDE expr {
        if ($1.type == TYPE_STRING || $3.type == TYPE_STRING) {
            fprintf(stderr, "Error: Cannot divide strings\n");
            $$ = (typeof($$)){ .type = TYPE_FLOAT, .value.floatValue = NAN };
        } else if (($3.type == TYPE_FLOAT && $3.value.floatValue != 0) || ($3.type == TYPE_INT && $3.value.intValue != 0)) {
            if ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) {
                $$ = (typeof($$)){ .type = TYPE_FLOAT, .value.floatValue = ($1.type == TYPE_INT ? $1.value.intValue : $1.value.floatValue) / ($3.type == TYPE_INT ? $3.value.intValue : $3.value.floatValue) };
            } else {
                $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = $1.value.intValue / $3.value.intValue };
            }
        } else {
            fprintf(stderr, "Error: Division by zero\n");
            $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = 0 };
        }
    }
    | LPAR expr RPAR { $$ = $2; }
    ;

sexpr: STRING_LITERAL { $$ = strdup($1); }
     | IDENT { $$ = get_string_variable_value($1); }
     | sexpr PLUS sexpr {
         char *temp = concatStrings($1, $3);
         free($1);
         free($3);
         $$ = temp;
       }
     ;

%%
