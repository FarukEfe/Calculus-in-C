#include "stack_queue.c"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
TO-DO's:
 - Account for brackets and evaporate them when consecutive '(' and ')'
*/

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

/*
The int input and return types will turn to float when the shunting yard algorithm accounts for 
multichar numbers and decimals
*/
float evaluate(char operator, float first, float second) {
    switch (operator) {
        case '-':
            return first-second;
        case '+':
            return first+second;
        case '*':
            return first*second;
        case '/':
            return first/second;
        default: // I'll make sure this never happens
            return 1;
    }
}

float solve(char *expression, float x, float y) {

    if (expression == "") {
        printf("Solution failed, returning 0 by default.\n");
        return 0;
    }
    // Define holding queue
    Queue *q_hold = create_queue();
    // Define holding and solving stacks
    Stack *s_hold = create_stack();
    Stack *s_solve = create_stack();

    char *token = strtok(expression,"\0");
    char *str_convert;
    char *num = (char *)malloc(UNIT_SIZE*sizeof(char));
    while (*token != '\000') {
        // Read through each character
        if (isdigit(*token) || *token == '.') { // Numbers
            //strcpy( str_convert , (char[2]) { (char) *token, '\0' } );
            //enqueue(q_hold,str_convert);
            strcat(num, (char[2]) { (char) *token, '\0' } );
        } else if (*token == '(' || *token == ')') { // Brackets
            push(s_hold,*token);
        } else { // Operator
            enqueue(q_hold,num);
            strcpy(num,"\0");
            // Pop items from stack until PEDMAS is accomplished
            while (get_order(s_hold->stack[s_hold->head]) > get_order(*token)) {
                char item = pop(s_hold);
                strcpy( str_convert , (char[2]) { (char) item, '\0' } );
                enqueue(q_hold,str_convert);
            }
            push(s_hold,*token);
        }
        token++;
    }
    // Enqueue the last number if there's any remaining
    if (strlen(num) != 0) {
        enqueue(q_hold,num);
    }
    // Enqueue remaning items on stack
    char item = pop(s_hold);
    while (item != '\0') {
        strcpy( str_convert , (char[2]) { (char) item, '\0' } );
        enqueue(q_hold,str_convert); 
        item = pop(s_hold);
    }
    // Print out Reverse-Polished Notation
    for (int i=0;i<=q_hold->head;i++) {
        printf("%d: %s\n",i,q_hold->queue[i]);
    }
    printf("\n");

    // Solve the Holding Stack
    int operated;
    do {
        operated = 0;
        for (int i=0;i<=q_hold->head;i++) {
            // Only run operation when there's an operator character in queue
            if (get_order(*(q_hold->queue[i])) != -1 && strlen(q_hold->queue[i]) == 1) {
                // Get numbers for operation
                char *str1 = (char *)malloc(UNIT_SIZE*sizeof(char));
                char *str2 = (char *)malloc(UNIT_SIZE*sizeof(char));
                strcpy(str1, q_hold->queue[i-2]);
                strcpy(str2, q_hold->queue[i-1]);
                float first_num = atof(str1);
                float second_num = atof(str2);
                // Run the operation and replace with the previous indexes in queue
                float result = evaluate(*(q_hold->queue[i]),first_num,second_num);
                char *replacement = (char *)malloc(UNIT_SIZE*sizeof(char)); 
                sprintf(replacement,"%f",result);
                q_remove(q_hold,i-2);
                q_remove(q_hold,i-1);
                q_change(q_hold,i-2,replacement);
                operated = 1;
                // Release memory allocations here
                break;
            }
        }
    } while (operated);

    if (q_hold->head != 0) {
        printf("Syntax error, the equation invalid. Returning 0...\n");
        return 0;
    }

    return atof(q_hold->queue[q_hold->head]);
}


int main() {
    float soln = solve("42*5/2+30-8",3.0,8.0);
    printf("%.1f\n",soln);
    return 1;
}
/*
Gathering examples for test cases:
"3+4*5-2"
"3+4*5-11/4"
"4*5/2+3-8"
"4*6/5+3-8"
4.2*5/2+3-8
42*5/2+30-8
*/