#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <math.h>

class Carriage {
	const float dx = 0.05f; // скорость горизонтального перемещения каретки при нажатии кнопок влево, вправо
	float x;
	float y;
	float length = 0.2f;
public:
	Carriage() : x(0), y(-0.9f) {} // конструктор каретки, задаем её начальные координаты, как удобно

	// функция рисовки каретки
	void drawCarriage();
	
	// функция перемещения каретки
	// left - наименование кнопки, отвечающей за перемещение каретки влево
    // right - наименование кнопки, отвечающей за перемещение каретки вправо
    // borderL - левая граница перемещения каретки
    // borderR - правая граница перемещения каретки
	void Move(char left, char right, float borderL, float borderR);

	void Grade(float koeff) { length *= koeff; }

	float getX() { return x; }
	float getY() { return y; }
	float getLength() { return length; }
};