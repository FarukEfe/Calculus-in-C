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
            return -1;
    }
}

float evaluate(char *expression,float x, float y) {
    // Define holding and solving queues
    Queue *q_hold = create_queue();
    Queue *q_solve = create_queue();
    // Define holding and solving stacks
    Stack *s_hold = create_stack();
    Stack *s_solve = create_stack();

    char *token = strtok(expression,"\0");
    while (*token != '\000') {
        // Read through each character
        if (isdigit(*token) != 0) { // Numbers
            enqueue(q_hold,*token);
        } else if (*token == '(' || *token == ')') { // Brackets
            push(s_hold,*token);
        } else { // Operator
            // Pop items from stack until PEDMAS is accomplished
            while (get_order(s_hold->stack[s_hold->head]) > get_order(*token)) {
                /*
                DEBUG: The code gets stuck here, and queue is a fast increasing list
                of '\000' repeating MANY times. Is the queue supposed to look like 
                that?
                */
                char item = pop(s_hold);
                enqueue(q_hold,item);
            }
            push(s_hold,*token);
        }
        token++;
    }
    char item = pop(s_hold);
    while (item != '\0') {
       enqueue(q_hold,item); 
       item = pop(s_hold);
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

/*

For Debug:

int main() {
    Stack *dummy = create_stack();
    push(dummy,'c');
    push(dummy,'a');
    push(dummy,'d');
    push(dummy,'c');  
    push(dummy,'c');  
    printf("%s\n",dummy->stack);
    char item = pop(dummy);
    printf("Item is %c and the new stack became %s.\n",item,dummy->stack);
}
*/