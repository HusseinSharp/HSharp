%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "garbagecollection.h"

int array_size;
int twod_array_size_row;
int twod_array_size_col;

#define YYDEBUG 1
extern int yydebug;
extern int yylineno;  // Use the yylineno from the lexer
extern char current_token_text[];

void yyerror(const char *s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
    fprintf(stderr, "Current token: %s\n", current_token_text);
}

%}

%union {
   int num;
   char *str;
}

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

%token <num> NUMBER
%token <str> IDENT
%token <str> LSB
%token <str> RSB
%token <str> COMMA
%token IMPORT

%type <num> expr
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



mainprog: import_list_opt MAIN LCB statement_list RCB SEMICOLON
        ;

import_list_opt: import_list
               | /* empty */
               ;
               
import_list: IMPORT_stmt_list
           ;

IMPORT_stmt_list: IMPORT_stmt
                | IMPORT_stmt_list IMPORT_stmt
                ;
IMPORT_stmt: IMPORT FILENAME ;

libprogstart: LIBDEF LCB statement_list RCB SEMICOLON;

statement_list: /* empty */
              | statement_list statement SEMICOLON
              ;

statement: var_declaration
         | assignment
         | display
         | freememory
         ;

var_declaration: IDENT LSB expr RSB { insert_array($1,$3); array_size = $3; }
               | VAR IDENT { insert_variable($2); }
               | IDENT LSB expr RSB LSB expr RSB { insert_2d_array($1, $3, $6); twod_array_size_col = $6; twod_array_size_row = $3; }
               ;

assignment: IDENT EQUALS expr %prec EQUALS { update_variable($1, $3); }
          | IDENT LSB expr RSB EQUALS expr %prec EQUALS { update_array_element($1, $3, $6, array_size); }
          | IDENT LSB expr RSB LSB expr RSB EQUALS expr %prec EQUALS { update_2d_array_element($1, $3, $6, $9, twod_array_size_row, twod_array_size_col); }
          ;

display: CALL IDENT %prec CALL { display_variable($2); }
       | CALL IDENT LSB expr RSB %prec CALL { display_array_element($2, $4, array_size); }
       | CALL IDENT LSB expr RSB LSB expr RSB %prec CALL { display_2d_array_element($2, $4, $7, twod_array_size_row, twod_array_size_col); }
       ;

freememory: FREEMEM LPAR IDENT RPAR {
    void *ptr = get_memory_block_pointer($3);
    if(ptr){
        remove_from_garbage_collection(ptr);
    }
    else {
        fprintf(stderr, "Error: Variable '%s' not found\n", $3);
    }
}             

expr: NUMBER { $$ = $1; }
   | IDENT { $$ = get_variable_value($1); }
   | IDENT LSB expr RSB { $$ = get_array_element_value($1, $3, array_size); }
   | IDENT LSB expr RSB LSB expr RSB { $$ = get_2d_array_element_value($1, $3, $6, twod_array_size_row, twod_array_size_col); }
   | expr PLUS expr { $$ = $1 + $3; }
   | expr MINUS expr { $$ = $1 - $3; }
   | expr MULTIPLY expr { $$ = $1 * $3; }
   | expr DIVIDE expr {
       if ($3 != 0) {
           $$ = $1 / $3;
       } else {
           fprintf(stderr, "Error: Division by zero\n");
           $$ = 0;
       }
   }
   | LPAR expr RPAR { $$ = $2; }
   ;

%%

