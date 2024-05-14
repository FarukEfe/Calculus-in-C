#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Stack data structure
typedef struct Stack {
    char stack[MAX_SIZE];
    int head; // Last element index
} Stack;

// Stack methods
Stack *create_stack() {
    Stack *data = (Stack*)malloc(sizeof(Stack));
    data->head = -1;
    return data;
}

void push(Stack *list, char item) {
    if (list->head == MAX_SIZE-1) {
        printf("Stack overflow. Cannot push new item.\n");
        return;
    }
    list->stack[list->head++] = item;
}

char pop(Stack *list) {
    if (list->head == -1) {
        printf("No items on stack. Already emptied.\n");
        return '\0';
    }
    //free(list->stack[list->head]);
    char val = list->stack[list->head]; // Get current head item
    list->head--; // With the next push, the "popped" item will be overwritten
    return val; // We want to return the popped item since we're using it for enqueue in this program
}

// Queue data structure
typedef struct Queue {
    char queue[MAX_SIZE];
    int head; // First element index
    int tail; // Last element index
} Queue;

// Queue methods
Queue *create_queue() {
    Queue *data = (Queue*)malloc(sizeof(Queue));
    data->head = -1;
    data->tail = -1;
    return data;
}

void enqueue(Queue *list, char item) {
    if (list->head == MAX_SIZE-1) {
        printf("Queue overflow, cannot enqueue new element.\n");
        return;
    }
    list->queue[list->head++] = item;
    list->tail = 0;
}

char dequeue(Queue *list) {
    if (list->head = -1) {
        printf("The queue is empty.\n");
        return '\0';
    }
    char item = list->queue[0];
    for (int i=0;i<list->tail-1;i++) {
        list->queue[i] = list->queue[i+1];
    }
    list->head--;
    if (list->head == -1) {
        list->tail = -1;
    }
    return item;
}