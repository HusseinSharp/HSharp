#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE *yyin;

#ifdef _WIN32
#include <windows.h>
HINSTANCE hInstance;
#endif

int main(int argc, char *argv[]) {
   
#ifdef _WIN32
    hInstance = GetModuleHandle(NULL);
#endif
  
    initialize_hashtable();
     initialize_garbage_collection();

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename.hussein>\n", argv[0]);
        return 1;
    }
    extern char** included_files;
    extern int included_files_count;

    // Ensure that the file has a .hussein extension
    const char *filename = argv[1];
    const char *extension = strrchr(filename, '.');
    if (!extension || strcmp(extension, ".hussein") != 0) {
        fprintf(stderr, "Error: Only .hussein files are accepted as input\n");
        return 1;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    yyin = file;

    yyparse();

    fclose(file);

     for (int i = 0; i < included_files_count; ++i) {
        free(included_files[i]);
    }
    free(included_files);
    //garbage_collect();
    
    return 0;
}
