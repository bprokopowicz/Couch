#include "shape.h"

// Shapes are a set of vertices.  All vertices fit inside a 2.0w x 1.0h box.  Rotation of the box is around 
// its middle. The co-ordinates of vertices are 0,0 in the lower left corner up to 2.0, 1.0 in the upper right.
// NOTE, vertices can be on the border of the box

struct shape * addVertex(struct shape *s, const struct vertex v) {
    if ((v.x_ < 0) || (v.x_ > SCALE_FACTOR * 2) || (v.y_ < 0) || (v.y_ > SCALE_FACTOR)) {
        printf("Bad vertex: %s\n", vertexToSharedString(v));
        return s;
    }
    if (s->nVertices_ >= s->capacity_) {
        struct vertex *buf;
        int oldSize = s->capacity_;
        s->capacity_ *= 2;
        buf = malloc(s->capacity_ * sizeof(struct vertex));
        memcpy(buf, s->vertices_, oldSize * sizeof(struct vertex));
        free(s->vertices_);
        s->vertices_ = buf;
    }
    s->vertices_[s->nVertices_++] = v;
    return s;
}

void moveShape(struct shape *s, const double x, const double y) {
    moveShapeScaled(s, scaleIt(x), scaleIt(y));
}

void moveShapeScaled(struct shape *s, const long x, const long y) {
        s->x_off_ += x;
        s->y_off_ += y;
    }

// returns new memory - must delete it.
char *shapeToNewString(struct shape s) {
    char *buf;
    int n = s.nVertices_;
    int bufsize = n * 2*(SCALE_DIGITS+3)+5;
    buf = malloc(bufsize);
    buf[0] = '\0';
    for (int i = 0; i < n-1; i++) {
        char *xStr = scaledToSharedString(s.vertices_[i].x_);
        strcat(buf, xStr);
        strcat(buf, ",");
    }
    if (n>0) {
        char *xStr = scaledToSharedString(s.vertices_[n-1].x_);
        strcat(buf, xStr);
    }
    strcat(buf, ":");
    for (int i = 0; i < n-1; i++) {
        char *yStr = scaledToSharedString(s.vertices_[i].y_);
        strcat(buf, yStr);
        strcat(buf, ",");
    }
    if (n>0) {
        char *yStr = scaledToSharedString(s.vertices_[n-1].y_);
        strcat(buf, yStr);
    }
    return buf;
}

void initShape(struct shape *s){
    s->nVertices_= 0;
    s->capacity_ = 2;
    s->vertices_ = malloc(s->capacity_ * sizeof(struct vertex));
    // all shapes start at -2,0 which is in the upper hall to the left.
    s->x_off_ = scaleIt(-2.0);
    s->y_off_ = scaleIt(0.0);
}

// constructs a deep copy of s and applies offsets.  Returns copy
// copy needs to be freed with freeShape() after use.
struct shape applyOffsets(struct shape s) {
    struct shape moved;
    int n = s.nVertices_;
    moved.nVertices_ = n;
    moved.x_off_ = 0;
    moved.y_off_ = 0;
    moved.vertices_ = malloc(n * sizeof(struct vertex));
    for (int i = 0; i < n; i++) {
        const struct vertex v = s.vertices_[i];
        moved.vertices_[i].x_ = v.x_ + s.x_off_;
        moved.vertices_[i].y_ = v.y_ + s.y_off_;
    }
    return moved;
}

void freeShape(struct shape s) {
    free(s.vertices_);
}

int shapeIsInside(struct shape s) {
    const int n = s.nVertices_;

    // for speed, we copy the vertices onto the stack instead of using malloc 
    struct vertex offsetVertices[n];
    for (int i = 0; i < n; i++) {
        const struct vertex v = s.vertices_[i];
        offsetVertices[i].x_ = v.x_ + s.x_off_;
        offsetVertices[i].y_ = v.y_ + s.y_off_;
    }

    // all offset vertices must be inside
    for (int i=0; i < n; i++) {
        if (! vertexIsInside(offsetVertices[i])) {
            return 0;
        }
    }
    // does any edge cross the inside corner even though both vertices are inside?
    for (int i1 = 0; i1 < n; i1++) {
        int i2 = (i1+1) % n;
        struct edge e;
        initEdge(&e, offsetVertices[i1], offsetVertices[i2]);
        if (edgeCutsCorner(&e)) {
            return 0;
        }
    }
    return 1;
}

void printShape(struct shape s) {
    char *str = shapeToNewString(s);
    printf("%s\n", str);
    free(str);
}
