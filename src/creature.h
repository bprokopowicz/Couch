#include "shape.h"
struct creature {
    struct shape s;
    int age;
};

void initCreature(struct creature *c);
void stepCreature(struct creature *c);
void freeCreature(struct creature c);
struct creature cloneCreature(struct creature c);
struct creature spawnCreature(struct creature c);
