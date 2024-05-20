#include "stack_queue.c"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*
TO-DO's:
 - Evaluate from reverse polished notation
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

    if (strlen(expression) == 0) {
        printf("Solution failed, returning 999 by default.\n");
        return -999;
    }
    // Define holding queue
    Queue *q_hold = create_queue();
    // Define holding and solving stacks
    Stack *s_hold = create_stack();
    Stack *s_solve = create_stack();

    char *token = strtok(expression,"\0");
    while (*token != '\000') {
        // Read through each character
        if (isdigit(*token)) { // Numbers
            enqueue(q_hold,*token);
        } else if (*token == '(' || *token == ')') { // Brackets
            push(s_hold,*token);
        } else { // Operator
            // Pop items from stack until PEDMAS is accomplished
            while (get_order(s_hold->stack[s_hold->head]) > get_order(*token)) {
                char item = pop(s_hold);
                enqueue(q_hold,item);
            }
            push(s_hold,*token);
        }
        token++;
    }
    // Enqueue remaning items on stack
    char item = pop(s_hold);
    while (item != '\0') {
       enqueue(q_hold,item); 
       item = pop(s_hold);
    }
    // Print out Reverse-Polished Notation
    for (int i=0;i<=q_hold->head;i++) {
        printf("%c",q_hold->queue[i]);
    }
    printf("\n");

    // Solve the Holding Stack
    char *order = strtok(q_hold->queue,"\0");
    char len = strlen(order);
    int operated;
    do {
        operated = 0;
        for (int i=0;i<len;i++) {
            if (get_order(order[i]) != -1) {
                /*
                We've previously made sure that an operation will always have 2 numbers trailing it
                atoi will change to atof when the string expression can handle decimals and multichar numbers
                */
                char str1[1]; strncpy(str1,order+(i-2),sizeof(str1));
                char str2[1]; strncpy(str2,order+(i-1),sizeof(str2));
                int first_num = str1[0]-48, second_num = str2[0]-48;
                int result = evaluate(order[i],first_num,second_num);
                // Get replacement and operation result it's being replaced with
                char rep[3]; strncpy(rep,order+i-2,sizeof(rep));
                int size_with = floor(log(result))-1;
                char with[size_with]; sprintf(with,"%d",result); // "%d" will turn to %f after upcoming features
                // Replace order string
                order = str_replace(order,rep,with);
                len = strlen(order);
                operated = 1;
                break; // Break inner loop and start over
            }
        }
    } while (operated); 

    return atof(order);
}

int main() {
    float soln = solve("3+4*5-2",3.0,8.0);
    printf("%.1f\n",soln);
    return 1;
}