#include "creature.h"
#include "test.h"

void testShapesMoving() {
  // rectangle inside upper hall
  struct creature c;
  initCreature(&c);

  struct vertex v1;
  initVertex(&v1,0.0,0.5);
  struct vertex v2;
  initVertex(&v2,0.5,0.6);
  struct vertex v3;
  initVertex(&v3,0.5,0.1);
  struct vertex v4;
  initVertex(&v4,0.0,0.05);
  addVertex(&c.shape_,v1);
  addVertex(&c.shape_,v2);
  addVertex(&c.shape_,v3);
  addVertex(&c.shape_,v4);
  for (int i = 0; i < 40; i++) {
      printShape(c.shape_);
      stepCreature(&c);
      struct shape t = applyOffsets(c.shape_);
      printShape(t);
      freeShape(t);
  }
}


int main(int argc, char** argv) {
    testShapesMoving();
}
