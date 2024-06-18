// hashtable.h
// Copyright (c) 2023 HusseinSharp(H#)
#ifndef HASHTABLE_H
#define HASHTABLE_H

#define HASH_SIZE 101

struct Node {
    char *name;
    int is_array;  // Indicates whether the variable is an array
    void *value;   // Value can be int or int array
    int size;      // Size of the array
    int rows;
    int cols;
    struct Node *next;
};

extern struct Node *hash_table[HASH_SIZE];  // Declare hash_table as external

unsigned int hash(const char *str); // Ensure the hash function is declared



void initialize_hashtable();
void insert_variable(const char *name);
void insert_array(const char *name, int array_size);
void insert_2d_array(const char *name, int rows, int cols);
void update_variable(const char *name, int value);
void update_array_element(const char *name, int index, int value, int array_size);
void update_2d_array_element(const char *name, int row, int col, int value,int rows ,int cols);
int get_variable_value(const char *name);
int get_array_element_value(const char *name, int index, int array_size);
int get_2d_array_element_value(const char *name, int row, int col,int rows,int cols);
void display_variable(const char *name);
void display_array_element(const char *name, int index, int array_size);
void display_2d_array_element(const char *name, int row, int col,int rows,int cols);

#endif  // HASHTABLE_H
