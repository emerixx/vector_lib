all:
	g++ vector.cpp -c
	g++ -o test.out test.cpp vector.o -lraylib
test:
	g++ -o test.out test.cpp vector.o -lraylib
