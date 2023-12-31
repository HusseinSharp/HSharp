#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE *yyin;

int main(int argc, char *argv[]) {
    initialize_hashtable();

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename.hussein>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    yyin = file;

    yyparse();

    fclose(file);
    return 0;
}