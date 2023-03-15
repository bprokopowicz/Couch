#include "shape.h"
#include "test.h"

void testShapesToString() {
  struct vertex v;
  initVertex(&v,-1.0,0.5);
  struct shape s;
  initShape(&s);
  addVertex(&s,v);
  char *str1 = shapeToNewString(s);
  TESTSTREQ(str1, "-1.000000000:0.500000000", "s shapeToNewString");
  free(str1);

  struct vertex v1;
  initVertex(&v1,-1.0,0.5);
  struct vertex v2;
  initVertex(&v2,-0.5,0.5);
  struct vertex v3;
  initVertex(&v3,-0.5,0.1);
  struct vertex v4;
  initVertex(&v4,-1.0,0.123456789);
  struct shape s1;
  initShape(&s1);
  addVertex(&s1,v1);
  addVertex(&s1,v2);
  addVertex(&s1,v3);
  addVertex(&s1,v4);
  char *str2 = shapeToNewString(s1);
  TESTSTREQ(str2, "-1.000000000,-0.500000000,-0.500000000,-1.000000000:0.500000000,0.500000000,0.100000000,0.123456789", "s shapeToNewString()");
  free(str2);
}

void testShapesMove() {
  // rectangle inside upper hall
  struct vertex v1;
  initVertex(&v1,-1.0,0.5);
  struct vertex v2;
  initVertex(&v2,-0.5,0.5);
  struct vertex v3;
  initVertex(&v3,-0.5,0.1);
  struct vertex v4;
  initVertex(&v4,-1.0,0.1);
  struct shape s1;
  initShape(&s1);
  addVertex(&s1,v1);
  addVertex(&s1,v2);
  addVertex(&s1,v3);
  addVertex(&s1,v4);
  TEST(shapeIsInside(s1),"s1 shape starts inside");
  // drop into negative zone
  moveShape(&s1,0.0, -0.6);
  TEST(!shapeIsInside(s1),"s1 shape not inside after move down");
  // move right into lower hall
  moveShape(&s1,1.1, 0.0);
  TEST(shapeIsInside(s1),"s1 shape inside after move right");
  moveShape(&s1,1.1, 0.0);
  TEST(!shapeIsInside(s1),"s1 shape not inside after move right again");
}

void testShapesInside() {
  // rectangle inside upper hall
  struct vertex v1;
  initVertex(&v1,-1.0,0.5);
  struct vertex v2;
  initVertex(&v2,-0.5,0.5);
  struct vertex v3;
  initVertex(&v3,-0.5,0.1);
  struct vertex v4;
  initVertex(&v4,-1.0,0.1);
  struct shape s1;
  initShape(&s1);
  addVertex(&s1,v1);
  addVertex(&s1,v2);
  addVertex(&s1,v3);
  addVertex(&s1,v4);
  TEST(shapeIsInside(s1),"s1 inside upper hall");

  // rectangle inside lower hall
  struct vertex v5;
  initVertex(&v5, 0.5, -0.1);
  struct vertex v6;
  initVertex(&v6,0.9,-0.1);
  struct vertex v7;
  initVertex(&v7,0.9,-0.7);
  struct vertex v8;
  initVertex(&v8,0.5,-0.7);
  struct shape s2;
  initShape(&s2);
  addVertex(&s2,v5);
  addVertex(&s2,v6);
  addVertex(&s2,v7);
  addVertex(&s2,v8);
  TEST(shapeIsInside(s2),"s2 inside lower hall");

  // rectangle inside corner hall 
  struct vertex v9;
  initVertex(&v9,0.5, 0.1);
  struct vertex v10;
  initVertex(&v10,0.9, 0.1);
  struct vertex v11;
  initVertex(&v11,0.9, 0.7);
  struct vertex v12;
  initVertex(&v12,0.5, 0.7);
  struct shape s3;
  initShape(&s3);
  addVertex(&s3,v9);
  addVertex(&s3,v10);
  addVertex(&s3,v11);
  addVertex(&s3,v12);
  TEST(shapeIsInside(s3),"s3 inside corner hall");

  // rectangle inside top and corner hall 
  struct vertex v13;
  initVertex(&v13,-0.5, 0.1);
  struct vertex v14;
  initVertex(&v14,0.9, 0.1);
  struct vertex v15;
  initVertex(&v15,0.9, 0.7);
  struct vertex v16;
  initVertex(&v16,-0.5, 0.7);
  struct shape s4;
  initShape(&s4);
  addVertex(&s4,v13);
  addVertex(&s4,v14);
  addVertex(&s4,v15);
  addVertex(&s4,v16);
  TEST(shapeIsInside(s4),"s4 inside top and corner hall");

  // rectangle inside bottom and corner hall 
  struct vertex v17;
  initVertex(&v17,0.5,-0.1);
  struct vertex v18;
  initVertex(&v18,0.9,-0.1);
  struct vertex v19;
  initVertex(&v19,0.9,0.7);
  struct vertex v20;
  initVertex(&v20,0.5,0.7);
  struct shape s5;
  initShape(&s5);
  addVertex(&s5,v17);
  addVertex(&s5,v18);
  addVertex(&s5,v19);
  addVertex(&s5,v20);
  TEST(shapeIsInside(s5),"s5 inside bottom and corner hall");
}

void testShapesOutside() {
  // rectangle goes above upper hall
  struct vertex v1;
  initVertex(&v1,-1.0,1.5);
  struct vertex v2;
  initVertex(&v2,-0.5,1.5);
  struct vertex v3;
  initVertex(&v3,-0.5,0.1);
  struct vertex v4;
  initVertex(&v4,-1.0,0.1);
  struct shape s1;
  initShape(&s1);
  addVertex(&s1,v1);
  addVertex(&s1,v2);
  addVertex(&s1,v3);
  addVertex(&s1,v4);
  TEST(!shapeIsInside(s1),"s1 outside above");

  // rectangle goes below upper hall
  struct vertex v5;
  initVertex(&v5,-1.0,0.5);
  struct vertex v6;
  initVertex(&v6,-0.5,0.5);
  struct vertex v7;
  initVertex(&v7,-0.5,-0.1);
  struct vertex v8;
  initVertex(&v8,-1.0,-0.1);
  struct shape s2;
  initShape(&s2);
  addVertex(&s2,v5);
  addVertex(&s2,v6);
  addVertex(&s2,v7);
  addVertex(&s2,v8);
  TEST(!shapeIsInside(s2),"s2 outside below");

  // rectangle goes right of corner
  struct vertex v9;
  initVertex(&v9,-1.0,0.5);
  struct vertex v10;
  initVertex(&v10,1.5,0.5);
  struct vertex v11;
  initVertex(&v11,1.5,0.1);
  struct vertex v12;
  initVertex(&v12,-1.0,0.1);
  struct shape s3;
  initShape(&s3);
  addVertex(&s3,v9);
  addVertex(&s3,v10);
  addVertex(&s3,v11);
  addVertex(&s3,v12);
  TEST(!shapeIsInside(s3),"s3 outside to right");
}

void testShapesCutCorner() {
  // triangle cuts corner quadrant
  struct vertex v1;
  initVertex(&v1,-0.5,0.5);
  struct vertex v2;
  initVertex(&v2,0.5,0.5);
  struct vertex v3;
  initVertex(&v3,0.5,-2.0);
  struct shape s1;
  initShape(&s1);
  addVertex(&s1,v1);
  addVertex(&s1,v2);
  addVertex(&s1,v3);
  TEST(!shapeIsInside(s1),"s1 cuts corner");

  // triangle stays inside 
  struct vertex v5;
  initVertex(&v5,-0.1,0.5);
  struct vertex v6;
  initVertex(&v6,0.9,0.5);
  struct vertex v7;
  initVertex(&v7,0.9,-0.5);
  struct shape s2;
  initShape(&s2);
  addVertex(&s2,v5);
  addVertex(&s2,v6);
  addVertex(&s2,v7);
  TEST(shapeIsInside(s2),"s2 doesn't cut corner");

  // single edge cuts the corner
  struct vertex v8;
  initVertex(&v8,-1.0,0.5);
  struct vertex v9;
  initVertex(&v9,1.0,-0.5);
  struct shape s3;
  initShape(&s3);
  addVertex(&s3,v8);
  addVertex(&s3,v9);
  TEST(!shapeIsInside(s3),"s3 cuts corner");
}


int main(int argc, char** argv) {
    testShapesToString();
    testShapesInside();
    testShapesOutside();
    testShapesCutCorner();
    testShapesMove();
}
