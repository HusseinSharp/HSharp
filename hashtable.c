// hashtable.c
//Copyright (c) 2023 HusseinSharp(H#)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#define HASH_SIZE 101

struct Node {
    char *name;
    int is_array;  // Indicates whether the variable is an array
    void *value;   // Value can be int or int array
    struct Node *next;
};

static struct Node *hash_table[HASH_SIZE];

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
    new_node->name = strdup(name);
    new_node->is_array = 0;
    new_node->value = malloc(sizeof(int));  // Allocate space for single int
    *((int *)new_node->value) = 0;  // Default value
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
}

void insert_array(const char *name, int array_size) {
    unsigned int index = hash(name);
    
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->name = strdup(name);
    new_node->is_array = 1;
    new_node->value = malloc(array_size);  // Example: assuming array size is 100 integers
    for (int i = 0; i < array_size; ++i) {
        ((int *)new_node->value)[i] = 0;  // Default values for the array
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
            if (index >= 0 && index < array_size) {
                ((int *)current->value)[index] = value;
            } else {
                fprintf(stderr, "Error: Array index out of bounds\n");
            }
            return;
        }
        current = current->next;
    }
    
    fprintf(stderr, "Error: Variable '%s' not declared or is not an array\n", name);
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
            if (index >= 0 && index < array_size) {
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
            if (index >= 0 && index < array_size) {
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

