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
	const float height = 0.1f, width = 0.1f; // ����� ����� �������
	int lifes = 3; // 3 ����� �� �����������
public:
	Brick(float x0, float y0) : x(x0), y(y0) {} // ����������� ������ ������

	virtual void drawBrick(); // ������ ����������� �������, �� ����� ������������ -> ����� �����������

	virtual int lifeBreak(Ball& ball, int& score); // ������� �����������, ��� ��� ����� ��� ��������������
	// ������� ������ ��������� ������, � ��� ����������� �������� ���������� �������� ������

	float getX() { return x; }
	float getY() { return y; }
	float getHeight() { return height; }
	float getWidth() { return width; }

};


class BrickIndestrctbl : public Brick { 
public:

	BrickIndestrctbl(float x0, float y0) : Brick(x0, y0) {} // ����������� ������ ������������� �������
	// �.�. ���� ������������ ���� ����������, ���������� ������ ������������ ����������� �������� ������

	int lifeBreak(Ball& ball, int& score); // ����� �� ���������� ��� ������������ � �������

	void drawBrick(); // ��� ������������ �������, �� �� ����� ������ ��� ������������ �� �����
};

class BrickBoost : public Brick {
public:
	float boost = 0.0005f;


	BrickBoost(float x0, float y0) : Brick(x0, y0) {} // ����������� ������ ������������� �������
	// �.�. ���� ������������ ���� ����������, ���������� ������ ������������ ����������� �������� ������

	int lifeBreak(Ball& ball, int& score);

	void drawBrick(); // ��� ������������ �������, �� �� ����� ������ ��� ������������ �� �����
};