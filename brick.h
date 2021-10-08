#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include <vector>
#include <iostream>

class Ball;

class Brick {
protected:
	float x;
	float y;
	const float height = 0.1f, width = 0.1f; // пусть будет квадрат
	int lifes = 3; // 3 жизни до уничтожения
public:
	Brick(float x0, float y0) : x(x0), y(y0) {} // конструктор класса кирпич

	virtual void drawBrick(); // делаем виртуальную функцию, тк будет наследование -> будет полиморфизм

	virtual int lifeBreak(Ball& ball, int& score); // функция виртуальная, так как нужно для неразбиваемого
	// кирпича убрать отнимание жизней, а для ускоряющего добавить увеличение скорости шарика

	float getX() { return x; }
	float getY() { return y; }
	float getHeight() { return height; }
	float getWidth() { return width; }

};


class BrickIndestrctbl : public Brick { 
public:

	BrickIndestrctbl(float x0, float y0) : Brick(x0, y0) {} // конструктор класса неразрушимого кирпича
	// т.к. идет наследование всех переменных, достаточно просто использовать конструктор базового класса

	int lifeBreak(Ball& ball, int& score); // жизни не отнимаются при столкновении с шариком

	void drawBrick(); // уже невиртульная функция, тк от этого класса уже наследований не будет
};

class BrickBoost : public Brick {
public:
	float boost = 0.0005f;


	BrickBoost(float x0, float y0) : Brick(x0, y0) {} // конструктор класса неразрушимого кирпича
	// т.к. идет наследование всех переменных, достаточно просто использовать конструктор базового класса

	int lifeBreak(Ball& ball, int& score);

	void drawBrick(); // уже невиртульная функция, тк от этого класса уже наследований не будет
};