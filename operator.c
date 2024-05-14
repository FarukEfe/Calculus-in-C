#include "stack_queue.c"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// This file handles evaluating math expression using stacks and queues
int get_order(char operator) {
    switch (operator) {
        case '-':
            return 1;
        case '+':
            return 2;
        case '*':
            return 3;
        case '/':
            return 4;
        default:
            return 999;
    }
}

float evaluate(char *expression,float x, float y) {
    char *current = expression;
    // Define holding and solving queues
    Queue *q_hold = create_queue();
    Queue *q_solve= create_queue();
    // Define holding and solving stacks
    Stack *s_hold = create_stack();
    Stack *s_solve = create_stack();

    while (current != NULL) {
        // Read through each character
        if (isdigit(*current)) { // Numbers
            enqueue(q_hold,*current);
        } else if (*current == '(' || *current == ')') { // Brackets
            push(s_hold,*current);
        } else { // Operator
            // Pop items from stack until PEDMAS is accomplished
            while (get_order(s_hold->stack[s_hold->head]) > get_order(*current)) {
                char item = pop(s_hold);
                enqueue(q_hold,item);
            }
            push(s_hold,*current);
        }
        current++;
    }
    char item;
    while ((item = pop(s_hold)) != '\0') {
       enqueue(q_hold,item); 
    }
    // Testing
    for (int i=0;i<=q_hold->head;i++) {
        printf("%c",q_hold->queue[i]);
    }
    printf("\n");
    return 0.0;
}

int main() {
    evaluate("3+4*5-2",3.0,8.0);
    return 1;
}