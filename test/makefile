bin/test_vertex: ../src/vertex.h test.h test_vertex.c ../src/bin/libcouch.a
	cc -I../src/ test_vertex.c -o bin/test_vertex -L../src/bin/ -lcouch

bin/test_edge: test.h test_edge.c ../src/bin/libcouch.a
	cc -I../src/ test_edge.c -o bin/test_edge -L../src/bin/ -lcouch

bin/test_shape: test.h test_shape.c ../src/bin/libcouch.a
	cc -I../src/ test_shape.c -o bin/test_shape -L../src/bin/ -lcouch

bin/test_creature: test.h test_creature.c ../src/bin/libcouch.a
	cc -I../src/ test_creature.c -o bin/test_creature -L../src/bin/ -lcouch

tests: bin/test_vertex bin/test_edge bin/test_shape bin/test_creature
	bin/test_vertex
	bin/test_edge
	bin/test_shape
	bin/test_creature

bin/test_moving: ../src/shape.h ../src/vertex.h test_moving.c
	cc -I../src/ test_moving.c -o bin/test_moving -L../src/bin/ -lcouch

all: tests bin/test_moving

clean:
	rm bin/test_*
