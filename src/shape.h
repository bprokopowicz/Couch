#include "edge.h"
#include <stdlib.h>
// Shapes are a set of vertices.  All vertices fit inside a 2.0w x 1.0h box.  Rotation of the box is around 
// its middle. The co-ordinates of vertices are 0,0 in the lower left corner up to 2.0, 1.0 in the upper right.

struct shape {
    struct vertex * vertices_;
    int nVertices_;
    int capacity_;
    long x_off_, y_off_;
};

void initShape(struct shape *s);

struct shape* addVertex(struct shape *s, struct vertex v);

void moveShape(struct shape *s, const double x, const double y);

void moveShapeScaled(struct shape *s, const long x, const long y);

char *shapeToNewString(struct shape s);

int shapeIsInside(struct shape s); 

struct shape applyOffsets(struct shape s);

void printShape(struct shape s);

void freeShape(struct shape s);
