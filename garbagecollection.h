#ifndef GARBAGE_COLLECTION_H
#define GARBAGE_COLLECTION_H

// Define a structure for tracking allocated memory blocks
struct MemoryBlock {
    void *ptr;
    struct MemoryBlock *next;
};

// Function to initialize garbage collection
void initialize_garbage_collection();

// Function to add a memory block to the garbage collection list
void add_to_garbage_collection(void *ptr);

void remove_from_garbage_collection(void *ptr);

void* get_memory_block_pointer(const char *name);

// Function to free all memory blocks tracked by garbage collection
void garbage_collect();

#endif  // GARBAGE_COLLECTION_H
