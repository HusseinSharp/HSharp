%{
#include <stdio.h>
#include <stdlib.h>


%}

%token VAR
%token <str> VAR_NAME


%token EQUALS
%token SEMICOLON
%token PLUS
%token MINUS
%token MULTIPLY
%token DIVIDE
%token LPAR
%token RPAR
%token LCB
%token RCB
%token MAIN
%token IF
%token ELIF
%token ELSE
%token FOR
%token WHILE
%token DBQT

%union {
   int num;
   char *str;
}


%token <num> NUMBER
%token <str> STRING
%type <num> expr
%type <str> MAIN

%%

mainprog: MAIN LCB statement RCB SEMICOLON ;

statement: expr
        | variable
        | ifstmt
        ;
ifstmt : IF LPAR statement RPAR LCB statement RCB SEMICOLON
       | IF LPAR statement RPAR LCB statement RCB ELIF LPAR statement RPAR LCB statement RCB ELSE LCB statement RCB SEMICOLON
expr: NUMBER PLUS NUMBER {$$ = $1 + $3;}
    | NUMBER MINUS NUMBER {$$ = $1 - $3;}
    | NUMBER MULTIPLY NUMBER {$$ = $1 * $3;}
    | NUMBER DIVIDE NUMBER {$$ = $1 / $3;}
    ;
variable : VAR STRING EQUALS expr SEMICOLON {printf("variable name: %s has value %d \n", $2, $4);}
          | VAR STRING EQUALS NUMBER SEMICOLON{printf("variable name: %s has value %d \n", $2, $4);}
          | VAR STRING EQUALS DBQT STRING DBQT SEMICOLON {printf("variable name: %s has value %s \n", $2, $5);}
          ;

%%
