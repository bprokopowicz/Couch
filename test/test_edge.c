#include "edge.h"
#include "test.h"

void testEdgesDontCutCorner() {
  // all in upper hall
  struct vertex a1;
  initVertex(&a1,-1.0,0.5);
  struct vertex b1;
  initVertex(&b1,-0.5,0.5);
  struct edge e1;
  initEdge(&e1,a1,b1);
  TEST(!edgeCutsCorner(&e1),"e1 doesn't cut corner");

  // opposite corners, but the whole edge stays in bounds
  struct vertex a2;
  initVertex(&a2,-0.1,0.5);
  struct vertex b2;
  initVertex(&b2,0.5,-0.5);
  struct edge e2;
  initEdge(&e2,a2,b2);
  struct edge e2r;
  initEdge(&e2r,b2,a2);
  TEST(!edgeCutsCorner(&e2),"e2 doesn't cut corner");
  TEST(!edgeCutsCorner(&e2r),"e2r doesn't cut corner");
}

void testEdgesCutCorner() {
  // upper to lower cuts corner right at 0,0
  struct vertex a1, b1;
  initVertex(&a1,-0.5,0.5);
  initVertex(&b1, 0.5,-0.5);
  struct edge e1;
  initEdge(&e1,a1,b1);
  TEST(edgeCutsCorner(&e1),"e1 cuts corner at vertex");
  struct vertex a2,b2;
  initVertex(&a2,-0.5,0.1);
  initVertex(&b2,0.5,-0.5);
  struct edge e2;
  initEdge(&e2,a2,b2);
  TEST(edgeCutsCorner(&e2),"e2 cuts corner");
  struct vertex a3, b3;
  initVertex(&a3,-0.5,0.9);
  initVertex(&b3,0.5,-0.9);
  struct edge e3;
  initEdge (&e3,a3,b3);
  TEST(edgeCutsCorner(&e3),"e3 cuts corner");
}

int main(int argc, char** argv) {
    testEdgesDontCutCorner();
    testEdgesCutCorner();
}
