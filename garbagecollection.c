#include "garbagecollection.h"
#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition for the garbage collection linked list
static struct MemoryBlock *garbage_collection = NULL;

// Function to initialize garbage collection
void initialize_garbage_collection() {
    garbage_collection = NULL;
}

// Function to add a memory block to the garbage collection list
void add_to_garbage_collection(void *ptr) {
    // Check if the block is already in the garbage collection list
    struct MemoryBlock *current = garbage_collection;
    while (current != NULL) {
        if (current->ptr == ptr) {
            printf("Memory block %p is already in the garbage collection\n", ptr); // Debug print
            return; // Already in the list, do not add again
        }
        current = current->next;
    }

    // If not found, add to the list
    struct MemoryBlock *block = (struct MemoryBlock *)malloc(sizeof(struct MemoryBlock));
    if (!block) {
        fprintf(stderr, "Error: Failed to allocate memory for garbage collection\n");
        return;
    }
    block->ptr = ptr;
    block->next = garbage_collection;
    garbage_collection = block;
   // printf("Added to garbage collection: %p\n", ptr); // Debug print
}

// Function to free all memory blocks tracked by garbage collection
void garbage_collect() {
    struct MemoryBlock *current = garbage_collection;
    while (current != NULL) {
        struct MemoryBlock *temp = current;
        current = current->next;
       // printf("Freeing: %p\n", temp->ptr); // Debug print
        free(temp->ptr);
        free(temp);
    }
    garbage_collection = NULL;
}

// Function to remove a memory block from the garbage collection list
void remove_from_garbage_collection(void *ptr) {
    struct MemoryBlock *current = garbage_collection;
    struct MemoryBlock *prev = NULL;

    // Traverse the garbage collection list
    while (current != NULL) {
        if (current->ptr == ptr) {
            // Found the memory block to remove
            if (prev != NULL) {
                // Update the previous block's next pointer
                prev->next = current->next;
            } else {
                // If the found block is the head of the list
                garbage_collection = current->next;
            }
           // printf("Removing from garbage collection: %p\n", ptr); // Debug print
            free(current);
            return;
        }
        // Move to the next block
        prev = current;
        current = current->next;
    }

    // If the specified memory block is not found
    fprintf(stderr, "Error: Memory block not found in garbage collection: %p\n", ptr); // Debug print
}

// Function to get a memory block pointer from the hashtable
void* get_memory_block_pointer(const char *name) {
    unsigned int index = hash(name); // Ensure hash function is accessible

    struct Node *current = hash_table[index]; // Access the hashtable
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current->value;
        }
        current = current->next;
    }

    fprintf(stderr, "Error: Memory block for '%s' not found\n", name);
    return NULL; // Return NULL if not found
}
