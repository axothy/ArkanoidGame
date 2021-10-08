#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <math.h>

class Carriage {
	const float dx = 0.05f; // �������� ��������������� ����������� ������� ��� ������� ������ �����, ������
	float x;
	float y;
	float length = 0.2f;
public:
	Carriage() : x(0), y(-0.9f) {} // ����������� �������, ������ � ��������� ����������, ��� ������

	// ������� ������� �������
	void drawCarriage();
	
	// ������� ����������� �������
	// left - ������������ ������, ���������� �� ����������� ������� �����
    // right - ������������ ������, ���������� �� ����������� ������� ������
    // borderL - ����� ������� ����������� �������
    // borderR - ������ ������� ����������� �������
	void Move(char left, char right, float borderL, float borderR);

	void Grade(float koeff) { length *= koeff; }

	float getX() { return x; }
	float getY() { return y; }
	float getLength() { return length; }
};