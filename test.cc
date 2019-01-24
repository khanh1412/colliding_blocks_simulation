#include"ConcreteSystem.h"
#include<iostream>
#include<cstring>
int main(int argc, char **argv)
{
	double bigM = 2;

	if (argc >= 2)
		bigM = std::atof(argv[1]);

	Environment env(bigM);
	while (env.nextState());
	std::cout<<"num of collisions "<<env.EventsList.size()<<std::endl;
	return 0;
}
