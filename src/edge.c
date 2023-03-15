#include "edge.h"

void initEdge (struct edge *e, struct vertex v1, struct vertex v2){
    e->a_ = v1;
    e->b_ = v2;
}

// assumes a and b are inside the walls
int edgeCutsCorner (struct edge *e) {
    // a and b must be in opposite halls
    struct vertex a = e->a_;
    struct vertex b = e->b_;
    if (
            // a in upper left hall, b in lower right hall
            ( (a.x_ < 0) &&  (a.y_ > 0) && (b.x_ > 0) && (b.y_ < 0) )
            ||
            // b in upper left hall, a in lower right hall
            ( (b.x_ < 0) &&  (b.y_ > 0) && (a.x_ > 0) && (a.y_ < 0) )
       ) {
        // slope
        const double m = 1.0 * (b.y_ - a.y_) / (b.x_ - a.x_);
        // we cut the corner if the intercepts (x=0 or y=0) occur in a negative quadrant, 
        // i.e. cutting both inside walls.  Testing either suffices, since the edge must
        // cross both or neither.  
        const double y_intercept = a.y_ - m * a.x_;
        if (y_intercept <= 0) return 1;
    } 
    return 0;
}
