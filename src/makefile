bin/vertex.o: vertex.h vertex.c
	cc -g -c vertex.c -o bin/vertex.o

bin/edge.o: vertex.h edge.c edge.h  
	cc -g -c edge.c -o bin/edge.o

bin/shape.o: shape.h shape.c edge.h vertex.h
	cc -g -c shape.c -o bin/shape.o

bin/creature.o: creature.h creature.c shape.h vertex.h
	cc -g -c creature.c -o bin/creature.o

bin/libcouch.a: bin/vertex.o bin/edge.o bin/shape.o bin/creature.o
	ar rcs bin/libcouch.a bin/vertex.o bin/edge.o bin/shape.o bin/creature.o

lib: bin/libcouch.a

clean: 
	rm bin/*.o  bin/libcouch.a
