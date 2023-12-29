#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE* yyin;
extern int yylex();

int main(int argc, char** argv) {
    if (argc == 2 && strcmp(argv[1], "-c") == 0) {
        // Read input from the console
        yyin = stdin;
    } else if (argc == 2) {
        // Read input from a file
        const char* fileExtension = strrchr(argv[1], '.');
        if (fileExtension && strcmp(fileExtension, ".hussein") == 0) {
            yyin = fopen(argv[1], "r");
            if (!yyin) {
                perror("Error opening file");
                return 1;
            }
        } else {
            fprintf(stderr, "Error: Unsupported file extension. Please provide a .hussein file.\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s [-c | input_file]\n", argv[0]);
        return 1;
    }

    yyparse();

    if (argc == 2 && yyin != stdin) {
        fclose(yyin);
    }

    return 0;
}

int yyerror(const char* s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}