#include "vertex.h"
struct edge {
    struct vertex a_;
    struct vertex b_;
};

void initEdge(struct edge *e, struct vertex v1, struct vertex v2);
int edgeCutsCorner (struct edge *e);
