#include "stack_queue.c"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*
TO-DO's:
 - Account for brackets and evaporate them when consecutive '(' and ')'
 - Account for multicharacer numbers (including float numbers), might need to switch stack & queue 
   list types to char *stack[size] and char *queue[size].
 - Making a copy of the input expression using 'strtok' is probably a redundant step. Verify and remove if necessary.
 - When you account for decimals in the algorithm, make sure to switch the return type of evaluate to float
*/

// Taken from: https://stackoverflow.com/questions/779875/what-function-is-to-replace-a-substring-from-a-string-in-c
// Will be moved over to a separate file
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
int evaluate(char operator, int first, int second) {
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
            return 0;
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
        if (isdigit(*token)) { // Numbers
            enqueue(q_hold,*token);
        } else if (*token == '(' || *token == ')') { // Brackets
            push(s_hold,*token);
        } else { // Operator
            enqueue(q_hold,num);
            strcpy(num,"\0");
            // Pop items from stack until PEDMAS is accomplished
            while (get_order(s_hold->stack[s_hold->head]) > get_order(*token)) {
                char item = pop(s_hold);
                enqueue(q_hold,item);
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
    // Enqueue the last number if there's any remaining
    if (strlen(num) != 0) {
        enqueue(q_hold,num);
    }
    free(num); // Release memory
    // Enqueue remaning items on stack - RECONSIDR THIS LOOP SINCE IT MIGHT BE REDUNDANT
    char item = pop(s_hold);
    while (item != '\0') {
       enqueue(q_hold,item); 
       item = pop(s_hold);
    }
    // Print out Reverse-Polished Notation 
    /*
    for (int i=0;i<=q_hold->head;i++) {
        printf("%c",q_hold->queue[i]);
    }
    printf("\n");
    */
    // Solve the Holding Stack
    char *order = strtok(q_hold->queue,"\0");
    char len = strlen(order);
    int operated;
    char *str1 = (char *)malloc(UNIT_SIZE*sizeof(char));
    char *str2 = (char *)malloc(UNIT_SIZE*sizeof(char));
    char *replacement = (char *)malloc(UNIT_SIZE*sizeof(char)); 
    do {
        operated = 0;
        for (int i=0;i<=q_hold->head;i++) {
            // Only run operation when there's an operator character in queue
            if (get_order(*(q_hold->queue[i])) != -1 && strlen(q_hold->queue[i]) == 1) {
                // Get numbers for operation
                char *str1 = (char *)malloc(UNIT_SIZE*sizeof(char));
                char *str2 = (char *)malloc(UNIT_SIZE*sizeof(char));
            // Only run operation when there's an operator character in queue
            if (get_order(*(q_hold->queue[i])) != -1 && strlen(q_hold->queue[i]) == 1) {
                // Get numbers for operation
                strcpy(str1, q_hold->queue[i-2]);
                strcpy(str2, q_hold->queue[i-1]);
                float first_num = atof(str1);
                float second_num = atof(str2);
                // Run the operation and replace with the previous indexes in queue
                // Run the operation and replace with the previous indexes in queue
                float result = evaluate(*(q_hold->queue[i]),first_num,second_num);
                sprintf(replacement,"%f",result);
                q_remove(q_hold,i-2);
                q_remove(q_hold,i-1);
                q_change(q_hold,i-2,replacement);
                operated = 1;
                
                break;
            }
        }
    } while (operated);
    free(str1); free(str2); free(replacement); // Release memory allocations

    if (q_hold->head != 0) {
        printf("Syntax error, the equation invalid. Returning 0...\n");
        return 0;
    }

    return atof(q_hold->queue[q_hold->head]);
}

int main() {
    float soln = solve("4*6/6+3-8",3.0,8.0);
    float soln = solve("3+4*5-2",3.0,8.0);
    printf("%.1f\n",soln);
    return 1;
}
/*
Gathering examples for test cases:
"3+4*5-2"
"3+4*5-11/4"
"4*5/2+3-8"
"4*6/5+3-8" -> Returns segfault
4.2*5/2+3-8
42*5/2+30-8
*/
/*
Gathering examples for test cases:
"3+4*5-2"
"3+4*5-11/4"
"4*5/2+3-8"
"4*6/5+3-8"
4.2*5/2+3-8
42*5/2+30-8
*/