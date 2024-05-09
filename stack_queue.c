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

void pop(Stack *list) {
    if (list->head == -1) {
        printf("No items on stack. Already emptied.\n");
        return;
    }
    list->head--; // With the next push, the "popped" item will be overwritten
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

void dequeue(Queue *list) {
    if (list->head = -1) {
        printf("The queue is empty.\n");
        return;
    }

    for (int i=0;i<list->tail-1;i++) {
        list->queue[i] = list->queue[i+1];
    }
    list->head--;
}