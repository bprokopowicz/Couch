#include "shape.h"
struct creature {
    struct shape shape_;
    int age_;
};

struct creature randomCreature(int nVertices, double maxWidth, double maxHeight);
void initCreature();
void stepCreature(struct creature *c);
void freeCreature(struct creature c);
struct creature cloneCreature(struct creature c);
struct creature spawnChildCreature(struct creature c);
