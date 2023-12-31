// hashtable.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 101

struct Node {
    char *name;
    int value;
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
    new_node->value = 0;  // Default value
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
}

void update_variable(const char *name, int value) {
    unsigned int index = hash(name);
    
    struct Node *current = hash_table[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    
    fprintf(stderr, "Error: Variable '%s' not declared\n", name);
}

int get_variable_value(const char *name) {
    unsigned int index = hash(name);
    
    struct Node *current = hash_table[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current->value;
        }
        current = current->next;
    }
    
    fprintf(stderr, "Error: Variable '%s' not declared\n", name);
    return 0;  // Return a default value
}

void display_variable(const char *name) {
    unsigned int index = hash(name);
    
    struct Node *current = hash_table[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("%s = %d\n", name, current->value);
            return;
        }
        current = current->next;
    }
    
    fprintf(stderr, "Error: Variable '%s' not declared\n", name);
}
