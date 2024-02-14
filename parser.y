%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
int array_size;

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
%token  MAIN
%token <str> CALL
%token VAR

%token <num> NUMBER
%token <str> IDENT
%token <str> LSB
%token <str> RSB
%token <str> COMMA

%type <num> expr
%type <str> var_declaration assignment display
%type <str> statement_list


%left PLUS MINUS
%left MULTIPLY DIVIDE

%%

mainprog: MAIN LCB statement_list RCB SEMICOLON;

statement_list: /* empty */
              | statement_list statement SEMICOLON
              ;

statement: var_declaration | assignment | display;

var_declaration:  IDENT LSB expr RSB { insert_array($1,$3); array_size = $3;}
               | VAR IDENT { insert_variable($2); };

assignment: IDENT EQUALS expr { update_variable($1, $3); }
          | IDENT LSB expr RSB EQUALS expr { update_array_element($1, $3, $6,array_size); };

display: CALL IDENT { display_variable($2); }
       | CALL IDENT LSB expr RSB { display_array_element($2, $4,array_size); };





expr: NUMBER { $$ = $1; }
   | IDENT { $$ = get_variable_value($1); }
   | IDENT LSB expr RSB { $$ = get_array_element_value($1, $3,array_size); }
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
   | '(' expr ')' { $$ = $2; }
   ;
   %%
   void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
