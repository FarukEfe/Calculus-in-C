#include "operator.c"
#include "dictionary.c"

// This project could be a good recap of your learnings in c from 1XC3
// Make sure you use gdb for debugging and valgrind to check for memory leaks

int main(int argc, char *argv[]) {

    if (argc < 8 || argc > 9) {
        printf("Arguments include: ./output <m> <n> <f> <a> <b> <c> <d> <point>(optional)\n");
        return 0;
    }
    // y-splits
    int m = atoi(argv[1]);
    // x-splits
    int n = atoi(argv[2]);
    if (m <= 1 || n <= 1) {
        printf("For approximation, at lease a partition of one unit is needed, please reconsider m and n.\n");
    }
    // x-bounds
    float a = atof(argv[4]);
    float b = atof(argv[5]);
    // y-bounds
    float c = atof(argv[6]);
    float d = atof(argv[7]);
    // (optional) point. for now assign default values, we'll handle user input as enum later
    Point integral_pt;
    integral_pt.h_point = EAST;
    integral_pt.v_point = NORTH;

    // We'll get to this later
    char *f_str = argv[3];

    // area differentials and slice area
    float differential_x = (b-a)/m;
    float differential_y = (d-c)/n;
    float unit_area = differential_x*differential_y;

    printf("%f %f %f\n",differential_x,differential_y,unit_area);

    float total = 0.0;
    for (int x_index = 1;x_index<=m;x_index++) {
        // x integrating point: x* = a + (i-h)*dx
        float point_x = a + (x_index-(integral_pt.h_point/2))*differential_x;
        for (int y_index = 1;y_index<=n;y_index++) {
            // y integrating point: y* = c + (i-v)*dy
            float point_y = c + (y_index-(integral_pt.v_point/2))*differential_y;
            // dummy function for testing
            float res = point_x + point_y;
            // multiply function result by unit area (dA)
            float unit_approx = res*unit_area;
            total += unit_approx;
        }
    }

    printf("The total result is %.2f\n",total);
}