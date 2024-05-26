#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

/*
The dictionary defined on this file is to assign string abbreviations with a custom type
object defined as 'Point', which holds the point of integration offset as 2 seperate enums
(1 horizontal and 1 vertical).
This way, we can assign the user command line input string with a point on the differential
area dA.
*/

// To get point of integration for each area, divide the enum values by 2 before finding x*i
enum H {
    WEST = 2,
    CENTER = 1,
    EAST = 0
};

enum V {
    SOUTH = 2,
    MIDDLE = 1,
    NORTH = 0
};

// Get the integration point within a unit area of the Riemann Sum
typedef struct Point {
    enum H h_point;
    enum V v_point;
} Point;

typedef struct PointDictionary {
    struct PointDictionary *next;
    const char *key;
    Point *value;
} PointDictionary;

// Create a table of hash values
static PointDictionary *table[HASHSIZE];

unsigned hash(char *s);
PointDictionary *find(char *key);
Point find_value(char *key);
PointDictionary *install(char *key, Point *value);
PointDictionary *generate_directions();

#endif