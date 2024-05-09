#include <stdio.h>
#include <stdlib.h>

// This project could be a good recap of your learnings in c from 1XC3
// Make sure you use gdb for debugging and valgrind to check for memory leaks

// To get point of integration for each area, divide the enum values by 2 before finding x*i
enum H {
    WEST = -2,
    CENTER = -1,
    EAST = 0
};

enum V {
    SOUTH = -2,
    MIDDLE = -1,
    NORTH = 0
};

typedef struct Point {
    enum H h_point;
    enum V v_point;
} Point;

int main(int argc, char *argv[]) {

    if (argc < 8 || argc > 9) {
        printf("Arguments include: ./output <m> <n> <f> <a> <b> <c> <d> <point>(optional)\n");
        return 0;
    }
    // y-splits
    int m = atoi(argv[1]);
    // x-splits
    int n = atoi(argv[2]);
    // x-bounds
    int a = atof(argv[4]);
    int b = atof(argv[5]);
    // y-bounds
    int c = atof(argv[6]);
    int d = atof(argv[7]);
    // (optional) point. for now assign default values, we'll handle user input as enum later
    Point integral_pt;
    integral_pt.h_point = EAST;
    integral_pt.v_point = NORTH;

    // We'll get to this later
    char *f_str = argv[3];

    // area differentials
    float differential_x = (b-a)/m;
    float differential_y = (d-c)/n;

    // Debug
    printf("%f\n",differential_x);
    printf("%f\n",differential_y);


}

float differentialY(int n,float c,float d) {
    return (d-c)/n;
}

float differentialX(int m,float a,float b) {
    return (b-a)/m;
}