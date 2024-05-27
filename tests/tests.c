#include "operator.c"
#include "dictionary.c"

// This file provides test cases for the shunting yard algorithm developed in order to evaluate math expressions.

typedef struct Test {
    char *expression;
    float x;
    float y;
} Test;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("To run: ./test <testdata.txt>\n");
        return 0;
    }

    FILE *fptr; fptr = fopen(argv[1],"r");
    if (fptr == NULL) {
        printf("Couldn't access file, terminating program.\n");
        return 0;
    }

    char *current = NULL;
    size_t buffer = 0;

    int tests = 0;
    int successes = 0;

    while(getline(&current,&buffer,fptr) != -1) {
        char *expression = strtok(current," ");
        char *x_str = strtok(NULL," ");
        char *y_str = strtok(NULL," ");
        char *answer = strtok(NULL," ");

        float x = atof(x_str);
        float y = atof(y_str);
        float ans = atof(answer);

        float test_result = solve(expression, x, y);
        
        tests++;

        float error = abs(test_result-ans)*100/ans;
        if (error < 0.1) {
            successes++;
        }

        printf("Expected: %.5f / Answer: %.5f (error: %.5f%%) (Passed %d out of %d)\n",ans,test_result,error,successes,tests);
    }

    printf("\nPassed %d out of %d test cases.\n\n",successes,tests);

    release_memory(); // Defined in operator.c, releases allocated memory after all jobs are over

    return 1;
}