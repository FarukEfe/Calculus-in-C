#include "stack_queue.c"
#include <operator.h>
#include <ctype.h>
#include <math.h>

// Taken from https://stackoverflow.com/questions/779875/what-function-is-to-replace-a-substring-from-a-string-in-c
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

// This file handles evaluating math expression using stacks and queues
int get_order(char operator) {
    switch (operator) {
        case '-':
            return 1;
        case '+':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        case '^':
            return 3;
        case ')':
            return 0;
        case '(':
            return -1;
        default:
            return -99;
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
        case '^':
            return pow(first,second);
        default: // I'll make sure this never happens
            return 1;
    }
}

void create_memory() {
    // Memory for Reverse Polish
    xc = (char *)malloc(UNIT_SIZE*sizeof(char));
    yc = (char *)malloc(UNIT_SIZE*sizeof(char));
    str_convert = (char *)malloc(2*sizeof(char));
    num = (char *)malloc(UNIT_SIZE*sizeof(char));
    // Memory for solving Reverse Polish
    str1 = (char *)malloc(UNIT_SIZE*sizeof(char));
    str2 = (char *)malloc(UNIT_SIZE*sizeof(char));
    replacement = (char *)malloc(UNIT_SIZE*sizeof(char)); 
}

void reset_memory() {
    strcpy(xc,"\0");
    strcpy(yc,"\0");
    strcpy(str_convert,"\0");
    strcpy(num,"\0");
    strcpy(str1,"\0");
    strcpy(str2,"\0");
    strcpy(replacement,"\0");
}

void release_memory() {
    free(xc); free(yc); // Free x and y variable strings
    free(num); // Free number allocation from reverse polishing
    free(str1); free(str2); free(replacement); // Free operation variables from solving step
    // stack_release(s_hold); q_release(q_hold); // Release stack and queue
}

float solve(char *expression, float x, float y) {

    reset_memory(); // Defined in this file, resets allocated memory
    
    sprintf(xc,"%f",x);
    sprintf(yc,"%f",y);
    char *newexpr = str_replace(expression,"x",xc); newexpr = str_replace(newexpr,"y",yc);

    if (expression == "") {
        printf("Solution failed, returning 0 by default.\n");
        return 0;
    }
    // Define holding queue
    Queue *q_hold = create_queue();
    // Define holding stack
    Stack *s_hold = create_stack();

    char *token = strtok(newexpr,"\0");
    while (*token != '\000') {
        // Read through each character
        if (isdigit(*token) || *token == '.') { // Numbers
            strcat(num, (char[2]) { (char) *token, '\0' } );
        } else if (*token == '(') { // Brackets
            push(s_hold,*token);
        } else { // Operator
            enqueue(q_hold,num);
            strcpy(num,"\0");
            // Pop items from stack until PEDMAS is accomplished
            while (get_order(s_hold->stack[s_hold->head]) >= get_order(*token)) {
                char item = pop(s_hold);
                strcpy( str_convert , (char[2]) { (char) item, '\0' } );
                enqueue(q_hold,str_convert);
            }
            if (*token != ')') {
                push(s_hold,*token);
            } else {
                pop(s_hold);
            }
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
    // Print out Reverse Polish Notation (for Debug)
    /*
    for (int i=0;i<=q_hold->head;i++) {
        printf("Elem %d: %s\n",i,q_hold->queue[i]);
    }
    printf("\n");
    */
    // Solve the Holding Stack
    int operated;
    do {
        operated = 0;
        for (int i=0;i<=q_hold->head;i++) {
            // Only run operation when there's an operator character in queue
            if (get_order(*(q_hold->queue[i])) > 0 && strlen(q_hold->queue[i]) == 1) {
                // Get numbers for operation
                strcpy(str1, q_hold->queue[i-2]);
                strcpy(str2, q_hold->queue[i-1]);
                float first_num = atof(str1);
                float second_num = atof(str2);
                // Run the operation and replace with the previous indexes in queue
                float result = evaluate(*(q_hold->queue[i]),first_num,second_num);
                sprintf(replacement,"%f",result);
                q_remove(q_hold,i-2);
                q_remove(q_hold,i-1);
                q_change(q_hold,i-2,replacement);
                operated = 1;
                // Release memory allocations here
                break;
            } else if (strlen(q_hold->queue[i]) == 0) {
                // If theres an empty slot, remove it and restart iteration
                q_remove(q_hold,i);
                operated = 1;
                break;
            }
        }
    } while (operated);

    if (q_hold->head != 0) {
        printf("Syntax error, the equation invalid. Returning 0...\n");
        return 0;
    }

    float result = atof(q_hold->queue[q_hold->head]);

    // stack_release(s_hold); q_release(q_hold); // Free stack and queue at the end of task

    return result;
}