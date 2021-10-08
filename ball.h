#include <windows.h> //���������� ��� �������� ����
#include <gl/gl.h> //����������� h ����� ���������� openGL
#include <math.h> // ��������� ������ ��� ������� ������ � ��������
#include <vector> // vector ����� ��� ������������� ������� ����������
#include <iostream>

#define _USE_MATH_DEFINES // ��������� �������������� ���������

#pragma comment(lib, "opengl32.lib") //����������� ����� ���������� openGL

class Carriage; // *����� ������ �� �����, ��� ��������� ����� ������������ ���� ����� � �������� ������,
// ������� ��� ���� ������������ �����������
class Brick; // �� �� �����
class Bonus;

class Ball { // ������� ����� �����
	//����� ������� �� ��� ����� - ��������� ������
	//�.�. ����������� ��� �������������� ������, ������, �������� � ��
protected:
	float x, y; // ���������� ������
	float speed = 0.01f; // �������� ���������� ��������, ������� ����� �������, ����� ������ ����
	float dx = speed, dy = speed; // ���������� �������� ������
	const float radius = 0.02f; //������ ������
	// �������� ����� � �������� ��� ���� ������ ��� ��������� �� �������

public:
	Ball(float x1, float y1) : x(x1), y(y1) {} // ����������� ������
	// ����� � ����� ��� ���������� � � � ��� ��������� �1 � �1, � dx dy ������������� 0.01

	// ������� ������� ������
	void drawBall(); 


	// ������ ����������� ����� �������
	bool CrossPoint(float x1, float y1); 

	// ������� ����������� ����� �������
	bool CrossLine(float x1, float y1, float x2, float y2); 

	// ������� ������� ������ �� �������
	void BounceOffCarriage(Carriage& carriage); 
	// ������� ������� ������ �� �������
	void BounceOffBrick(std::vector<Brick*>& bricks, std::vector<Bonus*>& bonuses, int& score);
	// ������� ����������� ��������� ������ �� �����
	void Mirror(float x1, float y1);

	// ������� ����������� ������
	bool Move(Carriage& carriage, std::vector<Brick*>& bricks, std::vector<Bonus*>& bonuses, int& score);

	// ������� ���������� �������� ������
	void speedBoost(float boost) { speed += boost; }

	float getX() { return x; } // ��� ��� ���������� � ������ � ��� protected
	float getY() { return y; } // ������� ��� ������� ��� ��������� ������ �������� ������
	float getRad() { return radius; } 
	// ���� ������� �������� ����������� � ���� �������,
	// �� � ���������� ����� ������ � .h ����

	void changedY() { dy *= -1; } // ������� ��� ��������� ���������
	void changedX() { dx *= -1; } // ����������� �������� ������
};