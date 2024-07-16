#ifndef HASHTABLE_H
#define HASHTABLE_H

#define HASH_SIZE 101
#define MAX_SCOPE_DEPTH 100

#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_STRING 2

struct Node {
    char *name;
    int is_array;  // Indicates whether the variable is an array
    int type;   // 0: int, 1: float, 2: string
    void *value;   // Value can be int or int array
    int size;      // Size of the array
    int rows;
    int cols;
    struct Node *next;
};

extern struct Node *symbol_table_stack[MAX_SCOPE_DEPTH][HASH_SIZE];
extern int current_scope_depth;

unsigned int hash(const char *str);
void initialize_hashtable();
void enter_scope();
void exit_scope();

void insert_array(const char *name, int array_size);
void insert_2d_array(const char *name, int rows, int cols);

void update_array_element(const char *name, int index, int value, int array_size);
void update_2d_array_element(const char *name, int row, int col, int value, int rows, int cols);

int get_array_element_value(const char *name, int index, int array_size);
int get_2d_array_element_value(const char *name, int row, int col, int rows, int cols);

void display_array_element(const char *name, int index, int array_size);
void display_2d_array_element(const char *name, int row, int col, int rows, int cols);

void insert_variable(const char *name);
void insert_float_variable(const char *name);
void insert_string_variable(const char *name);
void update_variable(const char *name, int value);
void update_float_variable(const char *name, float value);
void update_string_variable(const char *name, const char *value);
int get_variable_value(const char *name);
float get_float_variable_value(const char *name);
char* get_string_variable_value(const char *name);
void display_variable(const char *name);
int is_nan(float value);

char* concatStrings(const char* str1, const char* str2);
char* int_to_string(int value);
char* float_to_string(float value);
void delete_variable(const char *name);
int get_variable_value(const char *name);

#endif  // HASHTABLE_H
