#include "creature.h"
#include "test.h"


void testRandomCreatures() {
    // triangle that fits in a 1 x 1 box
    struct creature c = randomCreature(3, 1.0, 1.0);
    TEST(c.shape_.nVertices_ == 3, "random creature has 3 vertices");
    TEST(shapeIsInside(c.shape_), "random creature is inside");
}

int main(int argc, char** argv) {
    testRandomCreatures();
}
