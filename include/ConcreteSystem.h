#ifndef _CONCRETE_H_
#define _CONCRETE_H_
#include"System.h"
#include<vector>
class Environment;
class CollisionWall: public Event
{
	public:
		CollisionWall(Environment *env);
		~CollisionWall(){}
};
class Collision: public Event
{
	public:
		Collision(Environment *env);
		~Collision(){}
};
class Environment: public State
{
	public:
		double smallM;
		double smallX;
		double bigM;
		double bigX;
		std::vector<Event*> EventsList;
		double smallV;
		double bigV;
	public:
		Environment(double bigM);
		~Environment();
		bool nextState();
};
CollisionWall::CollisionWall(Environment* env): Event(env)
{
	env->smallV = -env->smallV;
}
Collision::Collision(Environment *env): Event(env)
{
	double m1 = env->smallM;
	double v1 = env->smallV;
	double m2 = env->bigM;
	double v2 = env->bigV;

	double vG = (m1*v1 + m2*v2)/(m1+m2);
	double v1G = v1-vG;
	double v2G = v2-vG;

	//after collision
	v1G = -v1G;
	v2G = -v2G;

	v1 = vG + v1G;
	v2 = vG + v2G;

	env->smallV = v1;
	env->bigV = v2;
}
Environment::Environment(double bigM)
	: State(), EventsList(),
	smallM(1), smallX(1), smallV(0),
	bigM(bigM), bigX(2), bigV(-1)
{}
Environment::~Environment()
{
	for (auto it = EventsList.begin(); it != EventsList.end(); ++it)
		delete *it;
	EventsList.clear();
}
bool Environment::nextState()
{
	//time until small collides wall
	double dt1 = - smallX / smallV;
	//time until small collides big
	double dt2 = (bigX - smallX) / (smallV - bigV);

	if (bigV >= smallV)
	{
		if (smallV < 0)
		{
			clock += dt1;
			smallX = 0;
			bigX += bigV * dt1;
			EventsList.push_back(new CollisionWall(this));
			return true;
		}
		else //(smallV = 0)
			return false;
	}
	else //(bigV < smallV)
	{
		if (smallV >= 0)
		{
			clock += dt2;
			smallX = smallV * dt2;
			bigX = bigV * dt2;
			EventsList.push_back(new Collision(this));
			return true;
		}
		else //(small < 0)
		{
			if (dt1 < dt2)
			{
				clock += dt1;
				smallX = 0;
				bigX += bigV * dt1;
				EventsList.push_back(new CollisionWall(this));
				return true;	
			}
			else if (dt1 > dt2)
			{
				clock += dt2;
				smallX = smallV * dt2;
				bigX = bigV * dt2;
				EventsList.push_back(new Collision(this));
				return true;	
			}
			else // (dt1=dt2)
			{
				__builtin_trap();
				return false;
			}
		}
	}
}

#endif
