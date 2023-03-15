#include <stdio.h>
#include <string.h>

#define SCALE_DIGITS 9
// must have DIGITS zeroes.
#define SCALE_FACTOR 1000000000

#define BUFLEN 100

struct vertex {
        long x_;
        long y_;
};

long scaleIt(double d);
void initVertex(struct vertex *v, double x, double y);

#define vertexIsInside(v) (((v.x_ >= SCALE_FACTOR)||( v.y_ >= SCALE_FACTOR)) ? 0 : ( ((v.x_ <= 0) && (v.y_ <= 0)) ? 0 : 1))

// NOT THREAD SAFE For now, returns a static char* buffer for the string.  
// returns a scaled long as a string floating point.
char * scaledToSharedString(long scaled);

// NOT THREAD SAFE For now, returns a static char* buffer for the string.  
char *vertexToSharedString(struct vertex v);
