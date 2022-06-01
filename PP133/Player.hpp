#pragma once
#include "Object.hpp"

class Player : public Object
{

	
public:
	Player()
	{
		Reset();
	}
	~Player() {}

	void Reset()
	{
		x = 20;
		y = 20;
	}
	void Left(float distance)
	{
		
		if (x > 0)
		{
			x -= distance;
		}
	}
	void Right(float distance)
	{
		if (x < 40)
		{
			x += distance;
		}
	}
};