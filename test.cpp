#include <iostream>
#include "vector.hpp"
int main (){
	std::cout<<"Hello, world!"<<"\n";
	vector vec = vector(1, 6, 2);
	std::cout<<"x: "<<vec.x<<"\n";
	std::cout<<"y: "<<vec.y<<"\n";
	std::cout<<"z: "<<vec.z<<"\n";
	vec = vec*5;
	std::cout<<"x: "<<vec.x<<"\n";
	std::cout<<"y: "<<vec.y<<"\n";
	std::cout<<"z: "<<vec.z<<"\n";
	return 0;
}
