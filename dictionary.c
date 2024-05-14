#include "dictionary.h"

/*
Declare dictionary to match user input strings with appropriate Point instances
The PointDictionary structure and its methods are influenced by the following resource:
https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c
*/

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
    Point *val;
    if (np == NULL) {
        val->h_point = EAST;
        val->v_point = NORTH;
    } else {
        val = np->value;
    }
    return *val;
}

PointDictionary *install(char *key, Point *value) {
    PointDictionary *np;
    unsigned hashvalue;
    if ((np = find(key)) == NULL) { // Set np as the instance at key
        np = (PointDictionary *)malloc(sizeof(*np));
        np->value = value;
        if (np == NULL || (np->key = strdup(key)) == NULL) return NULL;
        hashvalue = hash(key); // Get next hash in table
        np->next = table[hashvalue]; // Set next link to the new hash according to the table
        table[hashvalue] = np;
    } else {
        free((Point *) np->value); // Free up previous value assignment
        np->value = value;
        return np;
    }
}

PointDictionary *generate_directions() {
    PointDictionary *dict = (PointDictionary *)malloc(sizeof(PointDictionary)*8);

    Point *nw = (Point *)malloc(sizeof(Point));
    nw->h_point = 2;
    nw->v_point = 0;
    Point *n = (Point *)malloc(sizeof(Point));
    n->h_point = 1;
    n->v_point = 0;
    Point *ne = (Point *)malloc(sizeof(Point));
    ne->h_point = 0;
    ne->v_point = 0;
    Point *e = (Point *)malloc(sizeof(Point));
    e->h_point = 0;
    e->v_point = 1;
    Point *se = (Point *)malloc(sizeof(Point));
    se->h_point = 0;
    se->v_point = 2;
    Point *s = (Point *)malloc(sizeof(Point));
    s->h_point = 1;
    s->v_point = 2;
    Point *sw = (Point *)malloc(sizeof(Point));
    sw->h_point = 2;
    sw->v_point = 2;
    Point *w = (Point *)malloc(sizeof(Point));
    w->h_point = 2;
    w->v_point = 1;

    char* keys[8] = {"NW","N","NE","E","SE","S","SW","W"};
    Point* points[8] = {nw,n,ne,e,se,s,sw,w};

    for (int i=0;i<8;i++) {
        dict = install(keys[i],points[i]);
    }
}
