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
Stack *create_stack() {
    Stack *data = (Stack*)malloc(sizeof(Stack));
    data->head = -1;
    return data;
}

// Pushes new element into stack
void push(Stack *list, char item) {
    if (list->head == MAX_SIZE-1) {
        printf("Stack overflow. Cannot push new item.\n");
        return;
    }
    list->head++;
    list->stack[list->head] = item;
}

// Removes element from stack w.r.t. LIFO
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
    char **queue;
    int head; // First element index
    int tail; // Last element index
} Queue;

// Queue methods
Queue *create_queue() {
    Queue *data = (Queue*)malloc(sizeof(Queue));
    // Allocate memory for the queue list
    data->queue = (char **)malloc(MAX_SIZE*sizeof(char *));
    // Allocate memory for each string in the queue and assign empty string
    for (int i=0;i<MAX_SIZE;i++) {
        data->queue[i] = (char *)malloc(UNIT_SIZE*sizeof(char));
        strncpy(data->queue[i],"\0",sizeof(data->queue[i]));
    }
    data->head = -1;
    data->tail = -1;
    return data;
}

// Adds new element to queue
void enqueue(Queue *list, char *item) {
    if (strlen(item) > UNIT_SIZE) {
        printf("Item overflow, please pick a shorter string.\n");
        return;
    }
    if (list->head == MAX_SIZE-1) {
        printf("Queue overflow, cannot enqueue new element.\n");
        return;
    }
    list->head++;
    strcpy(list->queue[list->head],item);
    list->tail = 0;
}

// Removes one element from queue w.r.t. FIFO
// REMARK: Always free the item after temporary use!
char *dequeue(Queue *list) {
    if (list->head == -1) {
        printf("The queue is empty.\n");
        return "\0";
    }
    char *item = (char *)malloc(UNIT_SIZE*sizeof(char)); 
    strcpy(item,list->queue[0]);
    for (int i=0;i<=list->head;i++) {
        strcpy(list->queue[i],list->queue[i+1]);
    }
    strncpy(list->queue[list->head],"\0",sizeof(list->queue[list->head]));
    list->head--;
    if (list->head == -1) {
        list->tail = -1;
    }
    return item;
}

// Removes queue element at index
char *q_remove(Queue *list, int index) {
    if (list->head < index || index < 0) {
        printf("Queue underflow, please populate queue or use a lower index to pop");
        return "\0";
    }
    char *item = (char *)malloc(UNIT_SIZE*sizeof(char));
    strcpy(item,list->queue[index]);
    for (int i=index;i<list->head;i++) {
        strcpy(list->queue[i],list->queue[i+1]);

    }
    strncpy(list->queue[list->head],"\0",sizeof(list->queue[list->head]));
    list->head--;
    if (list->head == -1) {
        list->tail = -1;
    }
    return item;
}

// Copies new value to an existing element in queue
void q_change(Queue *list,int index,char *new_val) {
    if (index > list->head) {
        printf("Such index doesn't exist in queue.\n");
        return;
    }
    strcpy(list->queue[index],new_val);
}