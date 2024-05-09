#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

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

/*
Declare dictionary to match user input strings with appropriate Point instances
The PointDictionary structure and its methods are influenced by the following resource:
https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c
*/
typedef struct PointDictionary {
    struct PointDictionary *next;
    const char* key;
    Point value;
} PointDictionary;

// Create a table of hash values
static PointDictionary *table[HASHSIZE];

// Form hash value for key string
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

Point *find(char *key) {
    PointDictionary *np;
    for (np = table[hash(key)]; np != NULL; np = np->next) {
        if (strcmp(key, np->key) == 0)
          return &np->value;
    }
    return NULL;
}

