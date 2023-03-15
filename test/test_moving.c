#include "shape.h"
#include "test.h"

void testShapesMoving() {
  // rectangle inside upper hall
  struct vertex v1;
  initVertex(&v1,-1.0,0.5);
  struct vertex v2;
  initVertex(&v2,-0.5,0.5);
  struct vertex v3;
  initVertex(&v3,-0.5,0.1);
  struct vertex v4;
  initVertex(&v4,-1.0,0.1);
  struct shape s;
  struct shape t;
  initShape(&s);
  addVertex(&s,v1);
  addVertex(&s,v2);
  addVertex(&s,v3);
  addVertex(&s,v4);
  for (int i = 0; i < 100; i++) {
      printShape(s);
      moveShape(&s, 0.001, -0.002);
      t = applyOffsets(s);
      printShape(t);
      freeShape(t);
  }
}


int main(int argc, char** argv) {
    testShapesMoving();
}
