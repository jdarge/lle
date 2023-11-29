#include "sbrk.h"
#include "system.h"

// https://filippo.io/linux-syscall-table/
void *brk(void *end_data_segment) {
    return (void *) syscall(12, end_data_segment);
}

void *sbrk(intptr_t increment) {

    static void *heap_start = NULL;
    static void *heap_end = NULL;

    // If heap_start is NULL, then this is the first call to sbrk
    if (heap_start == NULL) {
        // Use brk with a size of 0 to get the current program break
        heap_start = brk(0);

        // Calculate a suitable starting address for the heap
        heap_start = (void *) (((uintptr_t) heap_start + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1));

        // Set the end of the heap to the starting address
        heap_end = heap_start;
    }

    // If increment is 0, return the current program break
    if (increment == 0) {
        return heap_end;
    }

    // Calculate the new program break
    char *new_heap_end = (char *) heap_end + increment;

    // If the new program break is below the start of the heap, return an error
    if (new_heap_end < (char *) heap_start) {
        return (void *) -1;
    }

    // Use brk to set the new program break
    void *prev_heap_end = heap_end;
    void *result = brk(new_heap_end);
    if (result == (void *) -1) {
        return (void *) -1;
    }

    // Update heap_end to reflect the new program break
    heap_end = new_heap_end;

    // Return the previous program break
    return prev_heap_end;
}
