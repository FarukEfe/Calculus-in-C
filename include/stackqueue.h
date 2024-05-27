#ifndef STACKQUEUE_H
#define STACKQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define UNIT_SIZE 25

// Stack data structure
typedef struct Stack {
    char stack[MAX_SIZE];
    int head; // Last element index
} Stack;

// Stack methods
Stack *create_stack();
void push(Stack *list, char item);
char pop(Stack *list);
void stack_release(Stack *list);

// Queue data structure
typedef struct Queue {
    char **queue;
    int head; // First element index
    int tail; // Last element index
} Queue;

// Queue methods
Queue *create_queue();
void enqueue(Queue *list, char *item);
char *dequeue(Queue *list);
char *q_remove(Queue *list, int index);
void q_change(Queue *list,int index,char *new_val);
void q_release(Queue *list);

#endif