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

PointDictionary *find(char *key) {
    PointDictionary *np;
    for (np = table[hash(key)]; np != NULL; np = np->next) {
        if (strcmp(key, np->key) == 0)
          return np;
    }
    return NULL;
}

Point find_value(char *key) {
    PointDictionary *np = find(key);
    return np->value;
}

PointDictionary *install(char *key, Point value) {
    PointDictionary *np;
    unsigned hashvalue;
    if ((np = find(key)) == NULL) { // Set np as the instance at key
        np = (PointDictionary *)malloc(sizeof(*np));
        if (np == NULL || (np->key = strdup(key)) == NULL) return NULL;
        hashvalue = hash(key); // Get next hash in table
        np->next = table[hashvalue]; // Set next link to the new hash according to the table
        table[hashvalue] = np;
    } else {
        free((void *) np->value); // Free up previous value assignment
        np->value = value;
        return np;
    }
}

int main() {
    PointDictionary *dummydict;
    Point nw;
    nw.h_point = 0;
    nw.v_point = -1;
    dummydict = install("NW",nw);
    Point test = find_value("NW");
    printf("%d %d\n",test.h_point,test.v_point);
}