#include "shape.h"
#include "test.h"

void testShapesToString() {
  struct vertex v;
  initVertex(&v,1.0,0.5);
  struct shape s;
  initShape(&s);
  addVertex(&s,v);
  char *str1 = shapeToNewString(s);
  TESTSTREQ(str1, "1.000000000:0.500000000", "s shapeToNewString");
  free(str1);
  freeShape(s);

  // out of bounds vertex 
  initShape(&s);
  initVertex(&v,2.1,0.5);
  addVertex(&s,v);
  str1 = shapeToNewString(s);
  TESTSTREQ(str1, ":", "empty shapeToNewString");
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
  TESTSTREQ(str2, "1.000000000,0.500000000,0.500000000,1.000000000:0.500000000,0.500000000,0.100000000,0.123456789", "s shapeToNewString()");
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
  struct shape t = applyOffsets(s);
  TEST(!shapeIsInside(t),"s1 shape not inside after move down");
  freeShape(t);

  // move right into lower hall
  moveShape(&s,2, 0.0);
  t = applyOffsets(s);
  TEST(shapeIsInside(t),"s shape inside after move right");
  freeShape(t);

  moveShape(&s,1, 0.0);
  t = applyOffsets(s);
  TEST(!shapeIsInside(t),"s shape not inside after move right again");
  freeShape(t);
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
  struct shape t;
  moveShape(&s, 2.0, -1.0);
  t = applyOffsets(s);
  TEST(shapeIsInside(t),"s inside lower hall");
  freeShape(t);

  // rectangle inside corner hall 
  moveShape(&s, -2, 1); // back to start
  moveShape(&s, 2, 0);
  t = applyOffsets(s);
  TEST(shapeIsInside(t),"s inside corner hall");
  freeShape(t);

  // rectangle inside top and corner hall 
  moveShape(&s, -2, 0); // back to start
  moveShape(&s, 1.5, 0);
  t = applyOffsets(s);
  TEST(shapeIsInside(s),"s inside top and corner hall");
  freeShape(t);

  // rectangle inside bottom and corner hall 
  moveShape(&s, -1.5, 0); // back to start
  moveShape(&s, 2, -1);
  t = applyOffsets(s);
  TEST(shapeIsInside(t),"s inside bottom and corner hall");
  freeShape(t);
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
  struct shape t = applyOffsets(s);
  TEST(!shapeIsInside(t),"s outside above");
  freeShape(t);

  // rectangle goes below upper hall
  moveShape(&s,0,-1); // back to start
  moveShape(&s,0,-1); // and too low
  t = applyOffsets(s);
  TEST(!shapeIsInside(t),"s outside below");
  freeShape(t);

  // rectangle goes right of corner
  moveShape(&s,0,1); // back to start
  moveShape(&s,3,0); // too far right
  t = applyOffsets(s);
  TEST(!shapeIsInside(t),"s outside to right");
  freeShape(t);
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
  struct shape t = applyOffsets(s);
  TEST(shapeIsInside(t),"s doesn't cut corner yet");
  moveShape(&s, -0.5, -1);
  t = applyOffsets(s);
  printShape(t);
  TEST(!shapeIsInside(t),"s now cuts corner");
  freeShape(t);
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
  t = applyOffsets(s2);
  TEST(shapeIsInside(s2),"s2 doesn't cut corner");
  freeShape(t);
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
  t = applyOffsets(s3);
  TEST(!shapeIsInside(t),"s3 cuts corner");
  freeShape(t);
  freeShape(s3);
}


int main(int argc, char** argv) {
    testShapesToString();
    testShapesInside();
    testShapesOutside();
    testShapesCutCorner();
    testShapesMove();
}
