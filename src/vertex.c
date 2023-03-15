#include "vertex.h"

long scaleIt(double d) {
    long sign = (d < 0.0) ? -1L : 1L;
    // truncate the scaled absolute value, then apply the sign back
    return sign * (long) (d * (sign*SCALE_FACTOR)); 
}

void initVertex(struct vertex *v, double x, double y) {
    v->x_ = scaleIt(x);
    v->y_ = scaleIt(y);
}

// NOT THREAD SAFE For now, returns a static char* buffer for the string.  
char * scaledToSharedString(long scaled) {
    long sign = (scaled >= 0) ? 1 : -1;
    static char buf[BUFLEN];
    // digit 9 here should be an arg to sprintf
    long abs_scaled = sign * scaled;
    long whole = abs_scaled / SCALE_FACTOR;
    long frac = abs_scaled % SCALE_FACTOR;
    // digit 9 here should be an arg to sprintf
    snprintf(buf, BUFLEN, "%s%ld.%09ld", (sign>0)?"":"-", whole, frac);
    return buf;
};

// NOT THREAD SAFE For now, returns a static char* buffer for the string.  
char *vertexToSharedString(struct vertex v) {
    static char buf[BUFLEN];
    char xbuf[BUFLEN];
    char ybuf[BUFLEN];
    strcpy (xbuf, scaledToSharedString(v.x_));
    // TODO can remove one copy here
    strcpy (ybuf, scaledToSharedString(v.y_));
    snprintf(buf, BUFLEN, "(%s,%s)", xbuf, ybuf);
    return buf;
};

