// hashtable.h
#ifndef HASHTABLE_H
#define HASHTABLE_H

void initialize_hashtable();
void insert_variable(const char *name);
void update_variable(const char *name, int value);
int get_variable_value(const char *name);
void display_variable(const char *name);

#endif  // HASHTABLE_H
