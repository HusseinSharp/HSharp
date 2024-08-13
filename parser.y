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

    int evaluate_condition(int condition) {
        return condition;
    }

    int condvalue;
    int temp;
    int condition_met;

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
%token <str> LPAR
%token <str> RPAR
%token <str> LCB
%token <str> RCB
%token <str> MAIN
%token <str> LIBDEF
%token <str> CALL
%token <str> VAR
%token <str> FILENAME
%token <str> IDENT
%token <str> LSB
%token <str> RSB
%token <str> COMMA
%token <str> IMPORT
%token <str> IF
%token <str> ELSE
%token <str> EQ
%token <str> NEQ
%token <str> LT
%token <str> GT
%token <str> LEQ
%token <str> GEQ
%token <str> OR
%token <str> AND
%token <str> ELSEIF

%type <exprval> expr
%type <str> sexpr
%type <str> var_declaration assignment display
%type <str> statement statement_list
%type <str> conditional_statement conditional_statement_list
%type <str> libprogstart if_statement elseif_statements else_statement conditional_if_statement
%type <str> conditional_display conditional_var_declaration conditional_assignment

%left PLUS MINUS
%left MULTIPLY DIVIDE
%left EQ NEQ LT GT LEQ GEQ OR AND


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

statement_list: /* empty */ { $$ = ""; }
              | statement_list statement SEMICOLON { $$ = $1; }
              ;

conditional_statement_list: /* empty */ { $$ = ""; }
                          | conditional_statement_list conditional_statement SEMICOLON { $$ = $1; }
                          ;

statement: var_declaration { $$ = $1; }
         | assignment { $$ = $1; }
         | display { $$ = $1; }
         | if_statement { $$ = ""; }
         ;

conditional_statement: conditional_var_declaration { $$ = $1; }
                     | conditional_assignment { $$ = $1; }
                     | conditional_display { $$ = $1; }
                     | conditional_if_statement { $$ = ""; }
                     ;

var_declaration: VAR IDENT EQUALS expr { 
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
                   $$ = $2;
                 }
               | VAR IDENT EQUALS sexpr { insert_string_variable($2); update_string_variable($2, $4); $$ = $2; }
               ;

conditional_var_declaration: VAR IDENT EQUALS expr { 
                               if (evaluate_condition(condvalue)) {
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
                               $$ = $2;
                             }
                           | VAR IDENT EQUALS sexpr { 
                               if (evaluate_condition(condvalue)) {  // Assuming string literals are always true
                                   insert_string_variable($2);
                                   update_string_variable($2, $4);
                               }
                               $$ = $2;
                             }
                           ;

assignment: IDENT EQUALS expr { 
                int old_type = get_variable_type($1);
                if (old_type == -1) {
                    if ($3.type == TYPE_INT) {
                        insert_variable($1);
                        update_variable($1, $3.value.intValue);
                    } else if ($3.type == TYPE_FLOAT) {
                        insert_float_variable($1);
                        update_float_variable($1, $3.value.floatValue);
                    } else {
                        insert_string_variable($1);
                        update_string_variable($1, $3.value.strValue);
                    }
                } else {
                    if ($3.type == TYPE_INT && old_type != TYPE_INT) {
                        delete_variable($1);
                        insert_variable($1);
                        update_variable($1, $3.value.intValue);
                    } else if ($3.type == TYPE_FLOAT && old_type != TYPE_FLOAT) {
                        delete_variable($1);
                        insert_float_variable($1);
                        update_float_variable($1, $3.value.floatValue);
                    } else if ($3.type == TYPE_STRING && old_type != TYPE_STRING) {
                        delete_variable($1);
                        insert_string_variable($1);
                        update_string_variable($1, $3.value.strValue);
                    } else {
                        if ($3.type == TYPE_INT) 
                            update_variable($1, $3.value.intValue); 
                        else if ($3.type == TYPE_FLOAT) 
                            update_float_variable($1, $3.value.floatValue);
                        else 
                            update_string_variable($1, $3.value.strValue);
                    }
                }
                $$ = $1;
            }
          | IDENT EQUALS sexpr { 
                int old_type = get_variable_type($1);
                if (old_type == -1) {
                    insert_string_variable($1);
                } else if (old_type != TYPE_STRING) {
                    delete_variable($1);
                    insert_string_variable($1);
                }
                update_string_variable($1, $3); 
                $$ = $1;
            }
          ;

conditional_assignment: IDENT EQUALS expr { 
                            if (evaluate_condition(condvalue)) {
                                int old_type = get_variable_type($1);
                                if (old_type == -1) {
                                    if ($3.type == TYPE_INT) {
                                        insert_variable($1);
                                        update_variable($1, $3.value.intValue);
                                    } else if ($3.type == TYPE_FLOAT) {
                                        insert_float_variable($1);
                                        update_float_variable($1, $3.value.floatValue);
                                    } else {
                                        insert_string_variable($1);
                                        update_string_variable($1, $3.value.strValue);
                                    }
                                } else {
                                    if ($3.type == TYPE_INT && old_type != TYPE_INT) {
                                        delete_variable($1);
                                        insert_variable($1);
                                        update_variable($1, $3.value.intValue);
                                    } else if ($3.type == TYPE_FLOAT && old_type != TYPE_FLOAT) {
                                        delete_variable($1);
                                        insert_float_variable($1);
                                        update_float_variable($1, $3.value.floatValue);
                                    } else if ($3.type == TYPE_STRING && old_type != TYPE_STRING) {
                                        delete_variable($1);
                                        insert_string_variable($1);
                                        update_string_variable($1, $3.value.strValue);
                                    } else {
                                        if ($3.type == TYPE_INT) 
                                            update_variable($1, $3.value.intValue); 
                                        else if ($3.type == TYPE_FLOAT) 
                                            update_float_variable($1, $3.value.floatValue);
                                        else 
                                            update_string_variable($1, $3.value.strValue);
                                    }
                                }
                            }
                            $$ = $1;
                        }
                      | IDENT EQUALS sexpr { 
                            if (evaluate_condition(condvalue)) {  // Assuming string literals are always true
                                int old_type = get_variable_type($1);
                                if (old_type == -1) {
                                    insert_string_variable($1);
                                } else if (old_type != TYPE_STRING) {
                                    delete_variable($1);
                                    insert_string_variable($1);
                                }
                                update_string_variable($1, $3); 
                            }
                            $$ = $1;
                        }
                      ;

display: CALL IDENT { display_variable($2); $$ = $2; }
       ;

conditional_display: CALL IDENT { if (evaluate_condition(condvalue)) { display_variable($2); } $$ = $2; }
                    ;

if_statement: IF LPAR expr RPAR { condvalue = $3.value.intValue; condition_met = condvalue; } LCB conditional_statement_list RCB elseif_statements else_statement
            ;

elseif_statements: /* empty */
                 | elseif_statements ELSEIF LPAR expr RPAR { 
                     if (!condition_met) {
                         condvalue = $4.value.intValue;
                         condition_met = condvalue;
                     } else {
                         condvalue = 0;
                     }
                   } LCB conditional_statement_list RCB
                 ;

else_statement: /* empty */
              | ELSE { 
                  if (!condition_met) { // Only evaluate if no previous condition was met
                      condvalue = 1; 
                      condition_met = 1; 
                  } else {
                      condvalue = 0; // Prevent the else block from executing
                  }
                } LCB conditional_statement_list RCB
              ;

conditional_if_statement: IF LPAR expr RPAR { condvalue = $3.value.intValue; } LCB conditional_statement_list RCB elseif_statements else_statement
                        ;

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
    | expr EQ expr { $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = ($1.type == $3.type) && 
                                                (($1.type == TYPE_INT && $1.value.intValue == $3.value.intValue) || 
                                                 ($1.type == TYPE_FLOAT && $1.value.floatValue == $3.value.floatValue) || 
                                                 ($1.type == TYPE_STRING && strcmp($1.value.strValue, $3.value.strValue) == 0)) }; }
    | expr NEQ expr { $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = !($1.type == $3.type) || 
                                                 (($1.type == TYPE_INT && $1.value.intValue != $3.value.intValue) || 
                                                  ($1.type == TYPE_FLOAT && $1.value.floatValue != $3.value.floatValue) || 
                                                  ($1.type == TYPE_STRING && strcmp($1.value.strValue, $3.value.strValue) != 0)) }; }
    | expr LT expr { $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = ($1.type == $3.type) && 
                                               (($1.type == TYPE_INT && $1.value.intValue < $3.value.intValue) || 
                                                ($1.type == TYPE_FLOAT && $1.value.floatValue < $3.value.floatValue)) }; }
    | expr GT expr { $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = ($1.type == $3.type) && 
                                               (($1.type == TYPE_INT && $1.value.intValue > $3.value.intValue) || 
                                                ($1.type == TYPE_FLOAT && $1.value.floatValue > $3.value.floatValue)) }; }
    | expr LEQ expr { $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = ($1.type == $3.type) && 
                                                (($1.type == TYPE_INT && $1.value.intValue <= $3.value.intValue) || 
                                                 ($1.type == TYPE_FLOAT && $1.value.floatValue <= $3.value.floatValue)) }; }
    | expr GEQ expr { $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = ($1.type == $3.type) && 
                                                (($1.type == TYPE_INT && $1.value.intValue >= $3.value.intValue) || 
                                                 ($1.type == TYPE_FLOAT && $1.value.floatValue >= $3.value.floatValue)) }; }
    | expr OR expr {
        if ($1.type == TYPE_STRING || $3.type == TYPE_STRING) {
            fprintf(stderr, "Error: Cannot apply '||' on strings\n");
            $$ = (typeof($$)){ .type = TYPE_FLOAT, .value.floatValue = NAN };
        } else if ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) {
            $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = (($1.type == TYPE_INT ? $1.value.intValue : $1.value.floatValue) != 0) ||
                                                         (($3.type == TYPE_INT ? $3.value.intValue : $3.value.floatValue) != 0) };
        } else {
            $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = $1.value.intValue || $3.value.intValue };
        }
    }
    | expr AND expr {
        if ($1.type == TYPE_STRING || $3.type == TYPE_STRING) {
            fprintf(stderr, "Error: Cannot apply '&&' on strings\n");
            $$ = (typeof($$)){ .type = TYPE_FLOAT, .value.floatValue = NAN };
        } else if ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) {
            $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = (($1.type == TYPE_INT ? $1.value.intValue : $1.value.floatValue) != 0) &&
                                                         (($3.type == TYPE_INT ? $3.value.intValue : $3.value.floatValue) != 0) };
        } else {
            $$ = (typeof($$)){ .type = TYPE_INT, .value.intValue = $1.value.intValue && $3.value.intValue };
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

int is_number(const char* str) {
    char* endptr;
    strtol(str, &endptr, 10);
    return *endptr == '\0';
}

int is_float(const char* str) {
    char* endptr;
    strtof(str, &endptr);
    return *endptr == '\0';
}
