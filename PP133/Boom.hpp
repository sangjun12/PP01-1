#pragma once
#include <random>
#include "Object.hpp"

using namespace std;
class Boom : public Object
{
private:
	const double speed = 10.0f;
public:
	double length;
	bool isOn;

	Boom()
	{
		Hide();
	}
	~Boom() {}
	void Initialize()
	{
		random_device rd;
		mt19937 gen(rd());
		
		uniform_int_distribution<int> dis1(5, 37);
		x = dis1(gen);
		uniform_int_distribution<int> dis2(-100, -5);
		y = dis2(gen);
		
		length = 1.0f;
		isOn = true;
	}
	void Hide()
	{
		x = 0;
		y = 0;
		length = 0;
		isOn = false;
	}

	void Move(double deltaTime)
	{
		y += deltaTime * speed;
	}
	bool Collider(Object* obj)
	{
		double x = obj->x, y = obj->y;
		bool xCondition = abs(x - this->x) < 4;
		double ySub = y - this->y;
		bool yCondition = abs(y - this->y) < 3;
		return xCondition && yCondition;
	}
};