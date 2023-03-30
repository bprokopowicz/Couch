#include "test.h"
#include "vertex.h"

void testPointConstructors() {
    struct vertex v1;
    initVertex(&v1, 0.000000003, 123.123456789);
    TESTLONGEQ(3L, v1.x_, "v1 constructor x_ value");
    TESTLONGEQ(123123456789L, v1.y_, "v1 constructor y_ value");
}

void testPointsScaling() {
    struct vertex v1;
    initVertex(&v1, 0.000000003, 123.123456789);
    TESTLONGEQ(3L, v1.x_, "v1 scaled x_ value");
    TESTLONGEQ(123123456789L, v1.y_, "v1 scaled y_ value");
    struct vertex v2;
    initVertex(&v2, -0.000000003, -123.123456789);
    TESTLONGEQ(-3L, v2.x_, "v2 scaled x_ value");
    TESTLONGEQ(-123123456789L, v2.y_, "v2 scaled y_ value");
}

void testPointsToString() {
    struct vertex v1;
    initVertex(&v1,-1.0,0.05);
    TESTSTREQ("(-1.000000000,0.050000000)", vertexToSharedString(v1), "v1 toString");

    struct vertex v2;
    initVertex(&v2,12.0012345,0.123456789);
    TESTSTREQ("(12.001234500,0.123456789)", vertexToSharedString(v2), "v2 toString");
}

void testPointsInside() {
    // top hall
    struct vertex v1;
    initVertex(&v1,-1.0,0.5);
	TEST(vertexIsInside(v1),"v1 inside");
	// corner hall
    struct vertex v2;
    initVertex(&v2,0.5,0.5);
	TEST(vertexIsInside(v2),"v2 inside");
	// bottom hall
    struct vertex v3;
    initVertex(&v3,0.5,-0.5);
	TEST(vertexIsInside(v3),"v3 inside");

}

void testPointsOutside() {
	// too low in left hall
    struct vertex v1;
    initVertex(&v1,-1.0,-0.5);
	TEST(! vertexIsInside(v1),"v1 outside");
	// too high in left hall
    struct vertex v2;
    initVertex(&v2,-1.0,1.5);
	TEST(! vertexIsInside(v2),"v2 outside");
	// too right near corner
    struct vertex v3;
    initVertex(&v3,1.1,0.5);
	TEST(! vertexIsInside(v3),"v3 outside");
	// too high near corner
    struct vertex v4;
    initVertex(&v4,0.5,1.5);
	TEST(! vertexIsInside(v4),"v4 outside");
	// too left in bottom hall
    struct vertex v5;
    initVertex(&v5,-0.5,-0.5);
	TEST(! vertexIsInside(v5),"v5 outside");
	// too right in bottom hall
    struct vertex v6;
    initVertex(&v6,1.5,-0.5);
	TEST(! vertexIsInside(v6),"v6 outside");
}

int main(int argc, char **argv) {
    testPointConstructors();
    testPointsScaling();
	testPointsToString();
	testPointsInside();
	testPointsOutside();
}
