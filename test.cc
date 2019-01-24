#include"ConcreteSystem.h"
#include<iostream>
#include<cstring>
double raise(long d)
{
	double r = 1;
	for (long i=0; i<d-1; ++i)
		r *= 100;
	return r;
}
int main(int argc, char **argv)
{
	long digits = 0;

	if (argc >= 2)
		digits  = std::atoi(argv[1]);

	double bigM = raise(digits);
	Environment env(bigM);
	while (env.nextState());
	std::cout<<"num of collisions "<<env.EventsList.size()<<std::endl;
	return 0;
}
