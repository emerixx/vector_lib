all:
	g++ vector.cpp -c
	g++ global_variables.cpp -c
	g++ vector_visualizer.cpp -c
	g++ -o test.out test.cpp vector.o global_variables.o vector_visualizer.o -lraylib
test:
	g++ -o test.out test.cpp vector.o -lraylib
