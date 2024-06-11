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
%}

%union {
   int num;
   char *str;
   struct ast *ast_node;
   struct symlist *arg_list;
}

%token <str> EQUALS
%token <str> SEMICOLON
%token <str> PLUS
%token <str> MINUS
%token <str> MULTIPLY
%token <str> DIVIDE
%token  LPAR
%token  RPAR
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
%type <str> start_stmt
%type <str> import_list
%type <str> program
%type <str> mainprog
%type <str> libprogstart

%left PLUS MINUS
%left MULTIPLY DIVIDE

%start program

%%

program: start_stmt 
       ;

start_stmt: /* empty */ 
          | libprogstart mainprog 
          | mainprog
          ;

libprogstart: LIBDEF LCB statement_list RCB SEMICOLON;

mainprog: import_list MAIN LCB statement_list RCB SEMICOLON;
        | MAIN LCB statement_list RCB SEMICOLON;
        
statement_list: /* empty */
              | statement_list statement SEMICOLON
              ;

import_list: /* empty */
           | import_list IMPORT_stmt 
           ;

statement: var_declaration 
         | assignment 
         | display 
         | freememory
         ;

IMPORT_stmt: IMPORT FILENAME SEMICOLON;

var_declaration:  IDENT LSB expr RSB { printf("DEBUG: Declaring array %s of size %d\n", $1, $3); insert_array($1,$3); array_size = $3;}
               | VAR IDENT { printf("DEBUG: Declaring variable %s\n", $2); insert_variable($2); }
               | IDENT LSB expr RSB LSB expr RSB { printf("DEBUG: Declaring 2D array %s of size %d x %d\n", $1, $3, $6); insert_2d_array($1, $3, $6); twod_array_size_col = $6; twod_array_size_row = $3;};

assignment: IDENT EQUALS expr { printf("DEBUG: Assigning to %s\n", $1); update_variable($1, $3); }
          | IDENT LSB expr RSB EQUALS expr { printf("DEBUG: Assigning to array %s[%d]\n", $1, $3); update_array_element($1, $3, $6, array_size); }
          | IDENT LSB expr RSB LSB expr RSB EQUALS expr { printf("DEBUG: Assigning to 2D array %s[%d][%d]\n", $1, $3, $6); update_2d_array_element($1, $3, $6, $9, twod_array_size_row, twod_array_size_col); };

display: CALL IDENT { printf("DEBUG: Calling display for %s\n", $2); display_variable($2); }
       | CALL IDENT LSB expr RSB { printf("DEBUG: Calling display for array element %s[%d]\n", $2, $4); display_array_element($2, $4, array_size); }
       | CALL IDENT LSB expr RSB LSB expr RSB { printf("DEBUG: Calling display for 2D array element %s[%d][%d]\n", $2, $4, $7); display_2d_array_element($2, $4, $7, twod_array_size_row, twod_array_size_col); };

freememory: FREEMEM LPAR IDENT RPAR {
    printf("DEBUG: Freeing memory for %s\n", $3);
    // Remove the memory block from garbage collection
    // Get pointer to the memory block based on IDENT
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
           $$ = 0; // You can handle division by zero differently if needed
       }
   }
   | LPAR expr RPAR { $$ = $2; }
   ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
