#include "creature.h"
#include <stdlib.h>

#define RAND ((double)rand()/(double)(RAND_MAX))

void initCreature(struct creature *c) {
    c->age_=0;
    initShape(&(c->shape_));
}

struct creature randomCreature(int nvertices, double maxWidth, double maxHeight) {
    struct creature c;
    initCreature(&c);
    for (int i=0; i < nvertices; i++) {
        struct vertex v;
        initVertex(&v, RAND*maxWidth, RAND*maxHeight);
        addVertex(&c.shape_, v);
    }
    return c;
}
