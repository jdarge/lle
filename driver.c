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

int main(void) {

    node_int_test();
    // node_float_test();
    dynamic_int_array();
    // dynamic_float_array();
    string();

    return 0;
}

void node_int_test(void) {
    // Create an empty linked list
    node_t *head = NULL;

    // Allocate the first node
    node_t *new_node = (node_t *) my_sbrk(sizeof(node_t));

    if (new_node == NULL) {
        my_printf("Error: out of memory\n");
        return;
    }

    new_node->value = 50;
    new_node->next = NULL;
    head = new_node;

    // Allocate a second node
    new_node = my_sbrk(sizeof(node_t));
    if (new_node == NULL) {
        my_printf("Error: out of memory\n");
        return;
    }

    new_node->value = 99;
    new_node->next = NULL;
    head->next = new_node;

    // Print the contents of the linked list
    node_t *current_node = head;
    while (current_node != NULL) {
        my_printf("%d ", current_node->value);
        current_node = current_node->next;
    }

    my_printf("\n");
}

void node_float_test(void) {
    // Create an empty linked list
    node_t *head = NULL;

    // Allocate the first node
    node_t *new_node = (node_t *) my_sbrk(sizeof(node_t));

    if (new_node == NULL) {
        my_printf("Error: out of memory\n");
        return;
    }

    new_node->number = 1.23;
    new_node->next = NULL;
    head = new_node;

    // Allocate a second node
    new_node = my_sbrk(sizeof(node_t));
    if (new_node == NULL) {
        my_printf("Error: out of memory\n");
        return;
    }

    new_node->number = 5.67;
    new_node->next = NULL;
    head->next = new_node;

    // Print the contents of the linked list
    node_t *current_node = head;
    while (current_node != NULL) {
        my_printf("%2f ", current_node->number);
        current_node = current_node->next;
    }

    my_printf("\n");
}

void dynamic_int_array(void) {
    // Allocate an array of 10 integers
    int *array = my_sbrk(10 * sizeof(int));
    if (array == NULL) {
        my_printf("Error: out of memory\n");
        return;
    }

    // Initialize the array
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }

    // Print the contents of the array
    for (int i = 0; i < 10; i++) {
        my_printf("%d ", array[i]);
    }
    my_printf("\n");

    // Resize the array to hold 20 integers
    int *new_array = my_sbrk(20 * sizeof(int));
    if (new_array == NULL) {
        my_printf("Error: out of memory\n");
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
        my_printf("%d ", new_array[i]);
    }
    my_printf("\n");
}

void dynamic_float_array(void) {
    // Allocate an array of 10 integers
    float *array = my_sbrk(10 * sizeof(float));
    if (array == NULL) {
        my_printf("Error: out of memory\n");
        return;
    }

    // Initialize the array
    for (int i = 0; i < 10; i++) {
        array[i] = (float) i + ((float) i / 10);
    }

    // Print the contents of the array
    for (int i = 0; i < 10; i++) {
        my_printf("%3f ", array[i]);
    }
    my_printf("\n");

    // Resize the array to hold 20 integers
    float *new_array = my_sbrk(20 * sizeof(float));
    if (new_array == NULL) {
        my_printf("Error: out of memory\n");
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
        my_printf("%3f ", new_array[i]);
    }
    my_printf("\n");
}

void string(void) {
    // Allocate memory for two strings
    char *str1 = (char *) my_sbrk(1024);
    char *str2 = (char *) my_sbrk(1024);

    // Copy some text into the first string
    my_strncpy(str1, "Hello, world!", 1024);

    // Copy the first string into the second string
    my_strncpy(str2, str1, 1024);

    // Print the two strings
    my_printf("str1:\t%s\n", str1);
    my_printf("str2:\t%s\n", str2);

    my_printf("char:\t%c\n", 'a');
    my_printf("int:\t%d\n", 543);
    my_printf("float:\t%f\n", 1.99);

    // TODO !%...
    my_printf("int!%2:\t%3d\n", 543000);
    my_printf("float!%2:%2f\n", 1.99);

    // Free the memory allocated for the strings
    my_brk(str2);
    my_brk(str1);
}
