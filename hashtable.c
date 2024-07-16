#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define HASH_SIZE 101
#define MAX_SCOPE_DEPTH 100

struct Node *symbol_table_stack[MAX_SCOPE_DEPTH][HASH_SIZE];
int current_scope_depth = 0;

unsigned int hash(const char *str) {
    unsigned int hash_val = 0;
    while (*str) {
        hash_val = (hash_val << 5) + *str++;
    }
    return hash_val % HASH_SIZE;
}

void initialize_hashtable() {
    for (int i = 0; i < MAX_SCOPE_DEPTH; ++i) {
        for (int j = 0; j < HASH_SIZE; ++j) {
            symbol_table_stack[i][j] = NULL;
        }
    }
}

void enter_scope() {
    if (current_scope_depth >= MAX_SCOPE_DEPTH - 1) {
        fprintf(stderr, "Error: Maximum scope depth exceeded\n");
        exit(EXIT_FAILURE);
    }
    current_scope_depth++;
}

void exit_scope() {
    if (current_scope_depth <= 0) {
        fprintf(stderr, "Error: No scope to exit\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < HASH_SIZE; ++i) {
        struct Node *current = symbol_table_stack[current_scope_depth][i];
        while (current) {
            struct Node *temp = current;
            current = current->next;
            free(temp->name);
            free(temp->value);
            free(temp);
        }
        symbol_table_stack[current_scope_depth][i] = NULL;
    }
    current_scope_depth--;
}

void insert_variable(const char *name) {
    unsigned int index = hash(name);

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (!new_node) {
        fprintf(stderr, "Error: Failed to allocate memory for variable node\n");
        return;
    }
    new_node->name = strdup(name);
    if (!new_node->name) {
        fprintf(stderr, "Error: Failed to allocate memory for variable name\n");
        free(new_node);
        return;
    }
    new_node->type = TYPE_INT;
    new_node->value = malloc(sizeof(int));  // Allocate space for single int
    if (!new_node->value) {
        fprintf(stderr, "Error: Failed to allocate memory for variable value\n");
        free(new_node->name);
        free(new_node);
        return;
    }
    *((int *)new_node->value) = 0;  // Default value
    new_node->next = symbol_table_stack[current_scope_depth][index];
    symbol_table_stack[current_scope_depth][index] = new_node;
}

void insert_float_variable(const char *name) {
    unsigned int index = hash(name);

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (!new_node) {
        fprintf(stderr, "Error: Failed to allocate memory for float variable node\n");
        return;
    }
    new_node->name = strdup(name);
    if (!new_node->name) {
        fprintf(stderr, "Error: Failed to allocate memory for float variable name\n");
        free(new_node);
        return;
    }
    new_node->type = TYPE_FLOAT;
    new_node->value = malloc(sizeof(float));
    if (!new_node->value) {
        fprintf(stderr, "Error: Failed to allocate memory for float variable value\n");
        free(new_node->name);
        free(new_node);
        return;
    }
    *((float *)new_node->value) = 0.0;  // Default value
    new_node->next = symbol_table_stack[current_scope_depth][index];
    symbol_table_stack[current_scope_depth][index] = new_node;
}

void insert_string_variable(const char *name) {
    unsigned int index = hash(name);

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (!new_node) {
        fprintf(stderr, "Error: Failed to allocate memory for string variable node\n");
        return;
    }
    new_node->name = strdup(name);
    if (!new_node->name) {
        fprintf(stderr, "Error: Failed to allocate memory for string variable name\n");
        free(new_node);
        return;
    }
    new_node->type = TYPE_STRING;
    new_node->value = strdup("");
    if (!new_node->value) {
        fprintf(stderr, "Error: Failed to allocate memory for string variable value\n");
        free(new_node->name);
        free(new_node);
        return;
    }
    new_node->next = symbol_table_stack[current_scope_depth][index];
    symbol_table_stack[current_scope_depth][index] = new_node;
}

void insert_array(const char *name, int array_size) {
    unsigned int index = hash(name);

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (!new_node) {
        fprintf(stderr, "Error: Failed to allocate memory for array node\n");
        return;
    }
    new_node->name = strdup(name);
    if (!new_node->name) {
        fprintf(stderr, "Error: Failed to allocate memory for array name\n");
        free(new_node);
        return;
    }
    new_node->is_array = 1;
    new_node->size = array_size;
    new_node->value = malloc(array_size * sizeof(int));  // Allocate space for the array
    if (!new_node->value) {
        fprintf(stderr, "Error: Failed to allocate memory for array value\n");
        free(new_node->name);
        free(new_node);
        return;
    }
    for (int i = 0; i < array_size; ++i) {
        ((int *)new_node->value)[i] = 0;  // Default values for the array
    }
    new_node->next = symbol_table_stack[current_scope_depth][index];
    symbol_table_stack[current_scope_depth][index] = new_node;
}

void insert_2d_array(const char *name, int rows, int cols) {
    unsigned int index = hash(name);

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (!new_node) {
        fprintf(stderr, "Error: Failed to allocate memory for 2D array node\n");
        return;
    }
    new_node->name = strdup(name);
    if (!new_node->name) {
        fprintf(stderr, "Error: Failed to allocate memory for 2D array name\n");
        free(new_node);
        return;
    }
    new_node->is_array = 1;
    new_node->rows = rows;
    new_node->cols = cols;
    new_node->size = rows * cols;
    new_node->value = malloc(rows * sizeof(int *)); // Allocate space for rows
    if (!new_node->value) {
        fprintf(stderr, "Error: Failed to allocate memory for 2D array value\n");
        free(new_node->name);
        free(new_node);
        return;
    }
    for (int i = 0; i < rows; ++i) {
        ((int **)new_node->value)[i] = malloc(cols * sizeof(int)); // Allocate space for columns
        if (!((int **)new_node->value)[i]) {
            fprintf(stderr, "Error: Failed to allocate memory for 2D array column\n");
            // Free previously allocated memory
            for (int j = 0; j < i; ++j) {
                free(((int **)new_node->value)[j]);
            }
            free(new_node->name);
            free(new_node->value);
            free(new_node);
            return;
        }
        for (int j = 0; j < cols; ++j) {
            ((int **)new_node->value)[i][j] = 0;  // Default values for the 2D array
        }
    }
    new_node->next = symbol_table_stack[current_scope_depth][index];
    symbol_table_stack[current_scope_depth][index] = new_node;
}

void update_variable(const char *name, int value) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int index = hash(name);
        struct Node *current = symbol_table_stack[depth][index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0 && current->type == TYPE_INT) {
                *((int *)current->value) = value;
                return;
            }
            current = current->next;
        }
    }

    fprintf(stderr, "Error: Variable '%s' not declared\n", name);
}

void update_float_variable(const char *name, float value) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int index = hash(name);
        struct Node *current = symbol_table_stack[depth][index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0 && current->type == TYPE_FLOAT) {
                *((float *)current->value) = value;
                return;
            }
            current = current->next;
        }
    }

    fprintf(stderr, "Error: Float variable '%s' not declared\n", name);
}

void update_string_variable(const char *name, const char *value) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int index = hash(name);
        struct Node *current = symbol_table_stack[depth][index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0 && current->type == TYPE_STRING) {
                free(current->value);
                current->value = strdup(value);
                return;
            }
            current = current->next;
        }
    }

    fprintf(stderr, "Error: String variable '%s' not declared\n", name);
}

void delete_variable(const char *name) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int index = hash(name);
        struct Node *current = symbol_table_stack[depth][index];
        struct Node *prev = NULL;
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                if (prev == NULL) {
                    symbol_table_stack[depth][index] = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current->name);
                free(current->value);
                free(current);
                return;
            }
            prev = current;
            current = current->next;
        }
    }
}

void update_array_element(const char *name, int index, int value, int array_size) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int array_index = hash(name);
        struct Node *current = symbol_table_stack[depth][array_index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0 && current->is_array) {
                if (index >= 0 && index < current->size) {
                    ((int *)current->value)[index] = value;
                    // Track allocated memory in garbage collection
                    add_to_garbage_collection(&((int *)current->value)[index]);
                } else {
                    fprintf(stderr, "Error: Array index out of bounds\n");
                }
                return;
            }
            current = current->next;
        }
    }

    fprintf(stderr, "Error: Variable '%s' not declared or is not an array\n", name);
}

void update_2d_array_element(const char *name, int row, int col, int value, int rows, int cols) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int array_index = hash(name);
        struct Node *current = symbol_table_stack[depth][array_index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0 && current->is_array) {
                if (row >= 0 && row < current->rows && col >= 0 && col < current->cols) {
                    ((int **)current->value)[row][col] = value;
                    // Track allocated memory in garbage collection
                    add_to_garbage_collection(&((int **)current->value)[row][col]);
                } else {
                    fprintf(stderr, "Error: 2D Array index out of bounds\n");
                }
                return;
            }
            current = current->next;
        }
    }

    fprintf(stderr, "Error: Variable '%s' not declared or is not a 2D array\n", name);
}

int get_variable_value(const char *name) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int index = hash(name);
        struct Node *current = symbol_table_stack[depth][index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0 && current->type == TYPE_INT) {
                return *((int *)current->value);
            }
            current = current->next;
        }
    }
    return -1;  // Return a distinct invalid value for int
}

float get_float_variable_value(const char *name) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int index = hash(name);
        struct Node *current = symbol_table_stack[depth][index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0 && current->type == TYPE_FLOAT) {
                return *((float *)current->value);
            }
            current = current->next;
        }
    }
    return -1.0;  // Return a distinct invalid value for float
}

char* get_string_variable_value(const char *name) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int index = hash(name);
        struct Node *current = symbol_table_stack[depth][index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0 && current->type == TYPE_STRING) {
                return (char *)current->value;
            }
            current = current->next;
        }
    }
    fprintf(stderr, "Error: String variable '%s' not declared\n", name);
    return "";  // Return a default value
}

int get_variable_type(const char *name) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int index = hash(name);
        struct Node *current = symbol_table_stack[depth][index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                return current->type;
            }
            current = current->next;
        }
    }
    return -1;  // Return -1 if variable not found
}

int get_array_element_value(const char *name, int index, int array_size) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int array_index = hash(name);
        struct Node *current = symbol_table_stack[depth][array_index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0 && current->is_array) {
                if (index >= 0 && index < current->size) {
                    return ((int *)current->value)[index];
                } else {
                    fprintf(stderr, "Error: Array index out of bounds\n");
                    return 0;  // Return a default value
                }
            }
            current = current->next;
        }
    }

    fprintf(stderr, "Error: Variable '%s' not declared or is not an array\n", name);
    return 0;  // Return a default value
}

int get_2d_array_element_value(const char *name, int row, int col, int rows, int cols) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int array_index = hash(name);
        struct Node *current = symbol_table_stack[depth][array_index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0 && current->is_array) {
                if (row >= 0 && row < current->rows && col >= 0 && col < current->cols) {
                    return ((int **)current->value)[row][col];
                } else {
                    fprintf(stderr, "Error: 2D Array index out of bounds\n");
                    return 0;  // Return a default value
                }
            }
            current = current->next;
        }
    }

    fprintf(stderr, "Error: Variable '%s' not declared or is not a 2D array\n", name);
    return 0;  // Return a default value
}

void display_variable(const char *name) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int index = hash(name);
        struct Node *current = symbol_table_stack[depth][index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                switch (current->type) {
                    case TYPE_INT:
                        printf("%s = %d\n", name, *((int *)current->value));
                        break;
                    case TYPE_FLOAT:
                        if (is_nan(*((float *)current->value))) {
                            printf("%s = nan\n", name);
                        } else {
                            printf("%s = %f\n", name, *((float *)current->value));
                        }
                        break;
                    case TYPE_STRING:
                        printf("%s = \"%s\"\n", name, (char *)current->value);
                        break;
                }
                return;
            }
            current = current->next;
        }
    }

    fprintf(stderr, "Error: Variable '%s' not declared\n", name);
}

void display_array_element(const char *name, int index, int array_size) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int array_index = hash(name);
        struct Node *current = symbol_table_stack[depth][array_index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0 && current->is_array) {
                if (index >= 0 && index < current->size) {
                    printf("%s[%d] = %d\n", name, index, ((int *)current->value)[index]);
                } else {
                    fprintf(stderr, "Error: Array index out of bounds\n");
                }
                return;
            }
            current = current->next;
        }
    }

    fprintf(stderr, "Error: Variable '%s' not declared or is not an array\n", name);
}

void display_2d_array_element(const char *name, int row, int col, int rows, int cols) {
    for (int depth = current_scope_depth; depth >= 0; --depth) {
        unsigned int array_index = hash(name);
        struct Node *current = symbol_table_stack[depth][array_index];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0 && current->is_array) {
                if (row >= 0 && row < current->rows && col >= 0 && col < current->cols) {
                    printf("%s[%d][%d] = %d\n", name, row, col, ((int **)current->value)[row][col]);
                } else {
                    fprintf(stderr, "Error: 2D Array index out of bounds\n");
                }
                return;
            }
            current = current->next;
        }
    }

    fprintf(stderr, "Error: Variable '%s' not declared or is not a 2D array\n", name);
}

char* concatStrings(const char* str1, const char* str2) {
    // Allocate memory for the result
    char* result = (char*)malloc(strlen(str1) + strlen(str2) + 1);
    
    // Check if memory allocation was successful
    if (result == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    // Copy the first string to the result
    strcpy(result, str1);
    
    // Concatenate the second string to the result
    strcat(result, str2);
    
    // Return the concatenated result
    return result;
}

char* int_to_string(int value) {
    // Allocate memory for the string representation of the integer
    char *buffer = malloc(12); // Enough to hold -2^31 to 2^31-1 and a null terminator
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    sprintf(buffer, "%d", value);
    return buffer;
}

char* float_to_string(float value) {
    // Allocate memory for the string representation of the float
    char *buffer = malloc(32); // Enough to hold the float representation and a null terminator
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    sprintf(buffer, "%f", value);
    return buffer;
}

int is_nan(float value) {
    return value != value;
}
