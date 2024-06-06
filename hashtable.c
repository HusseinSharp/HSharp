#include "hashtable.h"
#include "garbagecollection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 101

struct Node *hash_table[HASH_SIZE];  // Define hash_table

unsigned int hash(const char *str) {
    unsigned int hash_val = 0;
    while (*str) {
        hash_val = (hash_val << 5) + *str++;
    }
    return hash_val % HASH_SIZE;
}

void initialize_hashtable() {
    for (int i = 0; i < HASH_SIZE; ++i) {
        hash_table[i] = NULL;
    }
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
    new_node->is_array = 0;
    new_node->value = malloc(sizeof(int));  // Allocate space for single int
    if (!new_node->value) {
        fprintf(stderr, "Error: Failed to allocate memory for variable value\n");
        free(new_node->name);
        free(new_node);
        return;
    }
    *((int *)new_node->value) = 0;  // Default value
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
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
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
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
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
}

void update_variable(const char *name, int value) {
    unsigned int index = hash(name);

    struct Node *current = hash_table[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && !current->is_array) {
            *((int *)current->value) = value;
            // Track allocated memory in garbage collection
            add_to_garbage_collection(current->value);
           // printf("Updated variable %s to %d, added to garbage collection\n", name, value); // Debug print
            return;
        }
        current = current->next;
    }

    fprintf(stderr, "Error: Variable '%s' not declared\n", name);
}

void update_array_element(const char *name, int index, int value, int array_size) {
    unsigned int array_index = hash(name);

    struct Node *current = hash_table[array_index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && current->is_array) {
            if (index >= 0 && index < current->size) {
                ((int *)current->value)[index] = value;
                // Track allocated memory in garbage collection
                add_to_garbage_collection(&((int *)current->value)[index]);
               // printf("Updated array %s[%d] to %d, added to garbage collection\n", name, index, value); // Debug print
            } else {
                fprintf(stderr, "Error: Array index out of bounds\n");
            }
            return;
        }
        current = current->next;
    }

    fprintf(stderr, "Error: Variable '%s' not declared or is not an array\n", name);
}

void update_2d_array_element(const char *name, int row, int col, int value, int rows, int cols) {
    unsigned int array_index = hash(name);

    struct Node *current = hash_table[array_index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && current->is_array) {
            if (row >= 0 && row < current->rows && col >= 0 && col < current->cols) {
                ((int **)current->value)[row][col] = value;
                // Track allocated memory in garbage collection
                add_to_garbage_collection(&((int **)current->value)[row][col]);
              //  printf("Updated 2D array %s[%d][%d] to %d, added to garbage collection\n", name, row, col, value); // Debug print
            } else {
                fprintf(stderr, "Error: 2D Array index out of bounds\n");
            }
            return;
        }
        current = current->next;
    }

    fprintf(stderr, "Error: Variable '%s' not declared or is not a 2D array\n", name);
}

int get_variable_value(const char *name) {
    unsigned int index = hash(name);

    struct Node *current = hash_table[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && !current->is_array) {
            return *((int *)current->value);
        }
        current = current->next;
    }

    fprintf(stderr, "Error: Variable '%s' not declared\n", name);
    return 0;  // Return a default value
}

int get_array_element_value(const char *name, int index, int array_size) {
    unsigned int array_index = hash(name);

    struct Node *current = hash_table[array_index];
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

    fprintf(stderr, "Error: Variable '%s' not declared or is not an array\n", name);
    return 0;  // Return a default value
}

int get_2d_array_element_value(const char *name, int row, int col, int rows, int cols) {
    unsigned int array_index = hash(name);

    struct Node *current = hash_table[array_index];
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

    fprintf(stderr, "Error: Variable '%s' not declared or is not a 2D array\n", name);
    return 0;  // Return a default value
}

void display_variable(const char *name) {
    unsigned int index = hash(name);

    struct Node *current = hash_table[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && !current->is_array) {
            printf("%s = %d\n", name, *((int *)current->value));
            return;
        }
        current = current->next;
    }

    fprintf(stderr, "Error: Variable '%s' not declared\n", name);
}

void display_array_element(const char *name, int index, int array_size) {
    unsigned int array_index = hash(name);

    struct Node *current = hash_table[array_index];
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

    fprintf(stderr, "Error: Variable '%s' not declared or is not an array\n", name);
}

void display_2d_array_element(const char *name, int row, int col, int rows, int cols) {
    unsigned int array_index = hash(name);

    struct Node *current = hash_table[array_index];
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


