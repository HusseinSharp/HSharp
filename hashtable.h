// hashtable.h
#ifndef HASHTABLE_H
#define HASHTABLE_H

void initialize_hashtable();
void insert_variable(const char *name);
void insert_array(const char *name);
void update_variable(const char *name, int value);
void update_array_element(const char *name, int index, int value);
int get_variable_value(const char *name);
int get_array_element_value(const char *name, int index);
void display_variable(const char *name);
void display_array_element(const char *name, int index);

#endif  // HASHTABLE_H
