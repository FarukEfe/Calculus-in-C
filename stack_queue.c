#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define UNIT_SIZE 10

// Stack data structure
typedef struct Stack {
    char **stack;
    int head; // Last element index
} Stack;

// Stack methods
Stack *create_stack() {
    Stack *data = (Stack*)malloc(sizeof(Stack));
    // Memory allocate for the string list
    data->stack = (char **)malloc(MAX_SIZE*sizeof(char *));
    // Memory allocate for each slot in string list
    int i=0;
    while (data->stack[i] != NULL) {
        data->stack[i] = (char *)malloc(UNIT_SIZE*sizeof(char));
        i++;
    }
    data->head = -1;
    return data;
}

void push(Stack *list, char item[UNIT_SIZE]) {
    if (list->head == MAX_SIZE-1) {
        printf("Stack overflow. Cannot push new item.\n");
        return;
    }
    list->head++;
    list->stack[list->head] = item;
}

char *pop(Stack *list) {
    if (list->head == -1) {
        printf("No items on stack. Already emptied.\n");
        return '\0';
    }
    char *val = strtok(list->stack[list->head],"\0"); // Copy stack
    // Release element on stack
    free(list->stack[list->head]);
    list->head--; // With the next push, the "popped" item will be overwritten
    return val; // We want to return the popped item since we're using it for enqueue in this program
}

// Queue data structure
typedef struct Queue {
    char **queue;
    int head; // First element index
    int tail; // Last element index
} Queue;

// Queue methods
Queue *create_queue() {
    Queue *data = (Queue*)malloc(sizeof(Queue));
    // Memory allocate for the queue list
    data->queue = (char **)malloc(MAX_SIZE*sizeof(char *));
    int i=0;
    // Memory allocate for all strings in queue
    while (data->queue[i] != NULL) {
        data->queue[i] = (char *)malloc(UNIT_SIZE*sizeof(char));
    }
    data->head = -1;
    data->tail = -1;
    return data;
}

void enqueue(Queue *list, char item[UNIT_SIZE]) {
    if (list->head == MAX_SIZE-1) {
        printf("Queue overflow, cannot enqueue new element.\n");
        return;
    }
    list->head++;
    list->queue[list->head] = item;
    list->tail = 0;
}

char *dequeue(Queue *list) {
    if (list->head = -1) {
        printf("The queue is empty.\n");
        return '\0';
    }
    char *item = list->queue[0];
    for (int i=0;i<list->tail-1;i++) {
        list->queue[i] = list->queue[i+1];
    }
    // Free up dequeued memory space
    free(list->queue[list->head]);
    list->head--;
    if (list->head == -1) {
        list->tail = -1;
    }
    return item;
}