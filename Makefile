all:
	g++ vector.cpp -c -std=c++23
	g++ global_variables.cpp -c -std=c++23
	g++ vector_visualizer.cpp -c -std=c++23
	g++ test.cpp -c -std=c++23
	g++ -o test.out test.o vector.o global_variables.o vector_visualizer.o -lraylib -std=c++23
test:
	g++ -o test.out test.cpp vector.o matrix.o global_variables.o vector_visualizer.o -lraylib -std=c++23
