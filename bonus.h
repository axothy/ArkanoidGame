#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include <vector>
#include <iostream>


class Carriage;
class Ball;

class Bonus  {
	float x, y;
	float radius = 0.05f;
	float ddy = -0.0001f;
	float dy = -0.001f;
public:
	Bonus(float x0, float y0) : x(x0), y(y0) {}

	void drawBonus();

	bool Fall(Carriage& carriage, std::vector<Ball*> balls, int& score);
};