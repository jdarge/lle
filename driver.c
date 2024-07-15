#include "def.h"
#include "print.h"
#include "sbrk.h"
#include "string.h"

//Structs
typedef struct node {
    int value;
    float number;
    struct node *next;
} node_t;

// Tests
void node_int_test(void);
void node_float_test(void);
void dynamic_int_array(void);
void dynamic_float_array(void);
void string(void);

_Noreturn void exit(int code)
{
    /* Infinite for-loop since this function can't return */
    for (;;) {
        asm("mov %0, %%rax\n\t"
            "mov %1, %%rdi\n\t"
            "syscall\n\t"
            :
            : "r" ((uint64) SYS_exit),
              "r" ((uint64) code)
            : "%rax", "%rdi");
    }
}

int main(void) {

    node_int_test();
    dynamic_int_array();
    string();

    // node_float_test();
    // dynamic_float_array();

    return 0;
}

// https://www.reddit.com/r/C_Programming/comments/se3kgi/hello_world_without_libc/
__asm (
    ".global _start\n"
    "_start:\n"
    "   movl  (%rsp), %edi\n"
    "   lea   8(%rsp), %rsi\n"
    "   call  main\n"
    "   movl  %eax, %edi\n"
    "   movl  $60, %eax\n"
    "   syscall\n"
);

void node_int_test(void) {
    // Create an empty linked list
    node_t *head = NULL;

    // Allocate the first node
    node_t *new_node = (node_t *) sbrk(sizeof(node_t));

    if (new_node == NULL) {
        printf("Error: out of memory\n");
        return;
    }

    new_node->value = 50;
    new_node->next = NULL;
    head = new_node;

    // Allocate a second node
    new_node = sbrk(sizeof(node_t));
    if (new_node == NULL) {
        printf("Error: out of memory\n");
        return;
    }

    new_node->value = 99;
    new_node->next = NULL;
    head->next = new_node;

    // Print the contents of the linked list
    node_t *current_node = head;
    while (current_node != NULL) {
        printf("%d ", current_node->value);
        current_node = current_node->next;
    }

    printf("\n");
}

void node_float_test(void) {
    // Create an empty linked list
    node_t *head = NULL;

    // Allocate the first node
    node_t *new_node = (node_t *) sbrk(sizeof(node_t));

    if (new_node == NULL) {
        printf("Error: out of memory\n");
        return;
    }

    new_node->number = 1.23;
    new_node->next = NULL;
    head = new_node;

    // Allocate a second node
    new_node = sbrk(sizeof(node_t));
    if (new_node == NULL) {
        printf("Error: out of memory\n");
        return;
    }

    new_node->number = 5.67;
    new_node->next = NULL;
    head->next = new_node;

    // Print the contents of the linked list
    node_t *current_node = head;
    while (current_node != NULL) {
        printf("%2f ", current_node->number);
        current_node = current_node->next;
    }

    printf("\n");
}

void dynamic_int_array(void) {
    // Allocate an array of 10 integers
    int *array = sbrk(10 * sizeof(int));
    if (array == NULL) {
        printf("Error: out of memory\n");
        return;
    }

    // Initialize the array
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }

    // Print the contents of the array
    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Resize the array to hold 20 integers
    int *new_array = sbrk(20 * sizeof(int));
    if (new_array == NULL) {
        printf("Error: out of memory\n");
        return;
    }

    // Copy the contents of the old array to the new array
    for (int i = 0; i < 10; i++) {
        new_array[i] = array[i];
    }

    // Initialize the remaining elements of the new array
    for (int i = 10; i < 20; i++) {
        new_array[i] = i;
    }

    // Print the contents of the new array
    for (int i = 0; i < 20; i++) {
        printf("%d ", new_array[i]);
    }
    printf("\n");
}

void dynamic_float_array(void) {
    // Allocate an array of 10 integers
    float *array = sbrk(10 * sizeof(float));
    if (array == NULL) {
        printf("Error: out of memory\n");
        return;
    }

    // Initialize the array
    for (int i = 0; i < 10; i++) {
        array[i] = (float) i + ((float) i / 10);
    }

    // Print the contents of the array
    for (int i = 0; i < 10; i++) {
        printf("%3f ", array[i]);
    }
    printf("\n");

    // Resize the array to hold 20 integers
    float *new_array = sbrk(20 * sizeof(float));
    if (new_array == NULL) {
        printf("Error: out of memory\n");
        return;
    }

    // Copy the contents of the old array to the new array
    for (int i = 0; i < 10; i++) {
        new_array[i] = array[i];
    }

    // Initialize the remaining elements of the new array
    for (int i = 10; i < 20; i++) {
        new_array[i] = (float) (i + 0.1);
    }

    // Print the contents of the new array
    for (int i = 0; i < 20; i++) {
        printf("%3f ", new_array[i]);
    }
    printf("\n");
}

void string(void) {
    // Allocate memory for two strings
    char *str1 = (char *) sbrk(1024);
    char *str2 = (char *) sbrk(1024);

    // Copy some text into the first string
    strncpy(str1, "Hello, world!", 1024);

    // Copy the first string into the second string
    strncpy(str2, str1, 1024);

    // Print the two strings
    printf("str1:\t%s\n", str1);
    printf("str2:\t%s\n", str2);

    printf("char:\t%c\n", 'a');
    printf("int:\t%d\n", 543);
    printf("float:\t%f\n", 1.99);

    // TODO !%...
    printf("int!%2:\t%3d\n", 543000);
    printf("float!%2:%2f\n", 1.99);

    // Free the memory allocated for the strings
    brk(str2);
    brk(str1);
}
