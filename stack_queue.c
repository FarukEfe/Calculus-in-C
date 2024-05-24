#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    list->head++;
    list->stack[list->head] = item;
}

char pop(Stack *list) {
    if (list->head == -1) {
        printf("No items on stack. Already emptied.\n");
        return '\0';
    }
    char *copy = strtok(list->stack,"\0"); // Copy stack
    char val = copy[list->head]; // Get current head item
    list->stack[list->head] = '\000';
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
    list->head++;
    list->queue[list->head] = item;
    list->tail = 0;
}

// Removes one element from queue w.r.t. FIFO
void dequeue(Queue *list) {
    if (list->head == -1) {
        printf("The queue is empty.\n");
        return;
    }
    for (int i=0;i<=list->head;i++) {
        strcpy(list->queue[i],list->queue[i+1]);
    }
    strncpy(list->queue[list->head],"\0",sizeof(list->queue[list->head]));
    list->head--;
    if (list->head == -1) {
        list->tail = -1;
    }
}

// Removes queue element at index
void q_remove(Queue *list, int index) {
    if (list->head < index || index < 0) {
        printf("Queue underflow, please populate queue or use a lower index to pop");
        return;
    }
    for (int i=index;i<list->head;i++) {
        strcpy(list->queue[i],list->queue[i+1]);

    }
    strncpy(list->queue[list->head],"\0",sizeof(list->queue[list->head]));
    list->head--;
    if (list->head == -1) {
        list->tail = -1;
    }
}
