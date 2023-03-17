#include "creature.h"
#include "test.h"


void testRandomCreatures() {
    // triangle that fits in a 1 x 1 box
    struct creature c = randomCreature(3, 1.0, 1.0);
    TEST(c.shape_.nVertices_ == 3, "random creature has 3 vertices");
    TEST(shapeIsInside(c.shape_), "random creature is inside");
    freeCreature(c);

    c = randomCreature(100, 1.0, 1.0);
    TEST(c.shape_.nVertices_ == 100, "random creature has 100 vertices");
    TEST(shapeIsInside(c.shape_), "random creature is inside");
    freeCreature(c);
}

void testStep() {
    // rectangle inside upper hall
    struct vertex v1;
    initVertex(&v1,0.1,0.5);
    struct vertex v2;
    initVertex(&v2,0.5,0.0);
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

    struct creature c;
    initCreature(&c);
    c.shape_ = s;
    TEST(shapeIsInside(c.shape_), "rectange is inside before step");
    int offsetX = c.shape_.x_off_;
    int offsetY = c.shape_.y_off_;
    stepCreature(&c);
    TEST(shapeIsInside(c.shape_), "rectange is inside after step");
    // did it move?
    TEST(((offsetX!=c.shape_.x_off_)  || (offsetY!=c.shape_.y_off_)), "testOffsetChanged");
    TESTLONGEQ(1, c.steps_, "one step recorded");

    // no down-move in first 50 steps
    long highest = highestPointScaled(c.shape_);

    int movedDown = 0;
    for (int i=1; i < 50; i++) {
        stepCreature(&c);
        if (highestPointScaled(c.shape_) < highest) {
            movedDown = 1;
            break;
        }
    }
    TEST(!movedDown, "No down move within first 50 steps");
    TESTLONGEQ(50, c.steps_, "50 steps recorded");
    TESTLONGEQ(scaleIt(-1.5), c.shape_.x_off_, "shaped stepped right by 0.5");

    // move until a down-move happens
    movedDown = 0;
    for (int i=0; i < 1000; i++) {
        stepCreature(&c);
        if (highestPointScaled(c.shape_) < highest) {
            movedDown = 1;
            break;
        }
    }
    TEST(movedDown, "Down move within next 1000 steps");
    TESTLONGEQ(150, c.steps_, "Down move after 150 steps");
}

int main(int argc, char** argv) {
    testRandomCreatures();
    testStep();
}
