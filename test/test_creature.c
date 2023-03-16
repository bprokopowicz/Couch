#include "creature.h"
#include "test.h"


void testCreaturesStep() {
    int numVertices = 3;
    struct creature c;
    initCreature(&c);
    randomizeCreature(&c, numVertices);
    
    
}

int main(int argc, char** argv) {
    testCreaturesStep();
}
