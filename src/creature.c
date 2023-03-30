#include "creature.h"
#include <stdlib.h>

#define RAND ((double)rand()/(double)(RAND_MAX))

void initCreature(struct creature *c) {
    c->steps_=0;
    initShape(&(c->shape_));
}

void freeCreature(struct creature c) {
    freeShape(c.shape_);
}


void stepCreature(struct creature *c) {
    // move right if you can
    c->steps_++;
    moveShape(&c->shape_, TRANSLATE_DELTA, 0.0);
    if (!shapeIsInside(c->shape_)) {
        // undo
        moveShape(&c->shape_, -TRANSLATE_DELTA, 0.0);
    }
    // move down if you can
    moveShape(&c->shape_, 0.0, -TRANSLATE_DELTA);
    if (!shapeIsInside(c->shape_)) {
        // undo
        moveShape(&c->shape_, 0.0, TRANSLATE_DELTA);
    }
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
