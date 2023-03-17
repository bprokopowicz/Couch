#include "shape.h"
#include "test.h"

void testShapesToString() {
  struct vertex v;
  initVertex(&v,1.0,0.5);
  struct shape s;
  initShape(&s);
  addVertex(&s,v);
  char *str1 = shapeToNewString(s);
  TESTSTREQ("1.000000000:0.500000000", str1, "s shapeToNewString");
  free(str1);
  freeShape(s);

  // out of bounds vertex 
  initShape(&s);
  initVertex(&v,2.1,0.5);
  addVertex(&s,v);
  str1 = shapeToNewString(s);
  TESTSTREQ(":", str1, "empty shapeToNewString");
  free(str1);
  freeShape(s);

  struct vertex v1;
  initVertex(&v1,1.0,0.5);
  struct vertex v2;
  initVertex(&v2,0.5,0.5);
  struct vertex v3;
  initVertex(&v3,0.5,0.1);
  struct vertex v4;
  initVertex(&v4,1.0,0.123456789);
  struct shape s1;
  initShape(&s1);
  addVertex(&s1,v1);
  addVertex(&s1,v2);
  addVertex(&s1,v3);
  addVertex(&s1,v4);
  char *str2 = shapeToNewString(s1);
  TESTSTREQ("1.000000000,0.500000000,0.500000000,1.000000000:0.500000000,0.500000000,0.100000000,0.123456789", str2, "s shapeToNewString()");
  free(str2);
  freeShape(s1);
}

void testShapesMove() {
  // rectangle inside upper hall
  struct vertex v1;
  initVertex(&v1,0,0.5);
  struct vertex v2;
  initVertex(&v2,0.5,0.5);
  struct vertex v3;
  initVertex(&v3,0.5,0.1);
  struct vertex v4;
  initVertex(&v4,0,0.1);
  struct shape s;
  initShape(&s);
  addVertex(&s,v1);
  addVertex(&s,v2);
  addVertex(&s,v3);
  addVertex(&s,v4);
  TEST(shapeIsInside(s),"s shape starts inside");

  // drop into negative zone
  moveShape(&s,0.0, -0.6);
  TEST(!shapeIsInside(s),"s1 shape not inside after move down");

  // move right into lower hall
  moveShape(&s,2, 0.0);
  TEST(shapeIsInside(s),"s shape inside after move right");

  moveShape(&s,1, 0.0);
  TEST(!shapeIsInside(s),"s shape not inside after move right again");
  freeShape(s);
}

void testShapesInside() {
  // rectangle inside upper hall
  struct vertex v1;
  initVertex(&v1,0.1,0.5);
  struct vertex v2;
  initVertex(&v2,0.5,0.5);
  struct vertex v3;
  initVertex(&v3,0.5,0.1);
  struct vertex v4;
  initVertex(&v4,0.1,0.1);
  struct shape s;
  initShape(&s);
  addVertex(&s,v1);
  addVertex(&s,v2);
  addVertex(&s,v3);
  addVertex(&s,v4);
  TEST(shapeIsInside(s),"s inside upper hall at start");

  // rectangle inside lower right hall
  moveShape(&s, 2.0, -1.0);
  TEST(shapeIsInside(s),"s inside lower hall");

  // rectangle inside corner hall 
  moveShape(&s, -2, 1); // back to start
  moveShape(&s, 2, 0);
  TEST(shapeIsInside(s),"s inside corner hall");

  // rectangle inside top and corner hall 
  moveShape(&s, -2, 0); // back to start
  moveShape(&s, 1.5, 0);
  TEST(shapeIsInside(s),"s inside top and corner hall");

  // rectangle inside bottom and corner hall 
  moveShape(&s, -1.5, 0); // back to start
  moveShape(&s, 2, -1);
  TEST(shapeIsInside(s),"s inside bottom and corner hall");
  freeShape(s);
}

void testShapesOutside() {
  // rectangle goes above upper hall
  struct vertex v1;
  initVertex(&v1,0.1,0.5);
  struct vertex v2;
  initVertex(&v2,0.5,0.5);
  struct vertex v3;
  initVertex(&v3,0.5,0.1);
  struct vertex v4;
  initVertex(&v4,0.1,0.1);
  struct shape s;
  initShape(&s);
  addVertex(&s,v1);
  addVertex(&s,v2);
  addVertex(&s,v3);
  addVertex(&s,v4);
  moveShape(&s,0,1);
  TEST(!shapeIsInside(s),"s outside above");

  // rectangle goes below upper hall
  moveShape(&s,0,-1); // back to start
  moveShape(&s,0,-1); // and too low
  TEST(!shapeIsInside(s),"s outside below");

  // rectangle goes right of corner
  moveShape(&s,0,1); // back to start
  moveShape(&s,3,0); // too far right
  TEST(!shapeIsInside(s),"s outside to right");
  freeShape(s);
}

void testHighestPoint() {
  struct vertex v1;
  initVertex(&v1,0,0.5);
  struct vertex v2;
  initVertex(&v2,1,0.5);
  struct vertex v3;
  initVertex(&v3,1,0);
  struct shape s;
  initShape(&s);
  addVertex(&s,v1);
  addVertex(&s,v2);
  addVertex(&s,v3);
  TEST(highestPointScaled(s) == scaleIt(0.5), "highest point at start");
  moveShape(&s, 2, 0);
  TEST(highestPointScaled(s) == scaleIt(0.5), "highest point after move right");
  moveShape(&s, -0.5, -1);
  TEST(highestPointScaled(s) == scaleIt(-0.5), "highest point after move down");
  moveShape(&s, -0.5, -1);
  TEST(highestPointScaled(s) == scaleIt(-1.5), "highest point after 2nd move down");
  freeShape(s);
}


void testShapesCutCorner() {
  // triangle cuts corner quadrant
  struct vertex v1;
  initVertex(&v1,0,0.5);
  struct vertex v2;
  initVertex(&v2,1,0.5);
  struct vertex v3;
  initVertex(&v3,1,0);
  struct shape s;
  initShape(&s);
  addVertex(&s,v1);
  addVertex(&s,v2);
  addVertex(&s,v3);
  moveShape(&s, 2, 0);
  TEST(shapeIsInside(s),"s doesn't cut corner yet");
  moveShape(&s, -0.5, -1);
  TEST(!shapeIsInside(s),"s now cuts corner");
  freeShape(s);

  // triangle stays inside 
  struct vertex v5;
  initVertex(&v5,0,1);
  struct vertex v6;
  initVertex(&v6,1,1);
  struct vertex v7;
  initVertex(&v7,1,0);
  struct shape s2;
  initShape(&s2);
  addVertex(&s2,v5);
  addVertex(&s2,v6);
  addVertex(&s2,v7);
  moveShape(&s2, 1.9, -0.5);
  TEST(shapeIsInside(s2),"s2 doesn't cut corner");
  freeShape(s2);

  // single edge cuts the corner
  struct vertex v8;
  initVertex(&v8,0,1);
  struct vertex v9;
  initVertex(&v9,2,0);
  struct shape s3;
  initShape(&s3);
  addVertex(&s3,v8);
  addVertex(&s3,v9);
  moveShape(&s3, 0.5, -0.5);
  TEST(!shapeIsInside(s3),"s3 cuts corner");
  freeShape(s3);
}


int main(int argc, char** argv) {
    testShapesToString();
    testShapesInside();
    testShapesOutside();
    testShapesCutCorner();
    testShapesMove();
    testHighestPoint();
}
