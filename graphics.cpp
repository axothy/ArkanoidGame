#include "ball.h"
#include "brick.h"
#include "carriage.h"
#include "bonus.h"

void Ball::drawBall() // ���������� ������� ������� ������
{
	float x0;
	float y0;
	glBegin(GL_TRIANGLE_FAN); // ������� �������������
	// � ������ ������, ������������ ����� ��������� 
	// ������ ������ �����, ���� ����
	glColor3f(1, 1, 1); // ���� �����
	int cnt = 20; // ��� ������ �����, ��� ����� ������� ����� �����
	float alpha = 3.1415926f * 2.0f / cnt; // ����, ��������� �� ������ ������
	for (int i = -1; i < cnt; i++) { // ������ �������� ����� �� ����������
		x0 = (float)sin((double)alpha * (double)i) * radius;
		y0 = (float)cos((double)alpha * (double)i) * radius;
		glVertex2f(x0 + x, y0 + y); // ������ ����� �� ����������
	}
	glEnd();
}

void Carriage::drawCarriage() // ������ �������
{
	glBegin(GL_LINE_STRIP); // ������� �����
	glColor3f(1, 1, 1); // ����� ����
	glVertex2f(x - length, y); // ����� ���� �������
	glVertex2f(x + length, y); // ������ ���� �������
	glEnd();
}


int const GREEN = 3; // ���� � ����������� �� �������� ����� ������
int const YELLOW = 2;
int const RED = 1;

void Brick::drawBrick() {
	glBegin(GL_TRIANGLE_FAN); // ������� �������������
	// � ������ ������, ������������ ����� ��������� 
	// ������ ������ �����, ���� ���� 
	//�������� ���� ��������� � ����������� �� ��� ������
	if (lifes == GREEN)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else if (lifes == YELLOW) {
		glColor3f(1.0f, 1.0f, 0.0f);
	}
	else if (lifes == RED) {
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	//�������� ������� ����� ���������
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();

	glBegin(GGL_STRING); // ������ ����� ��� ���������, ����� ���� �������
	glColor3f(0, 0, 0);
	//�������� ������� ����� ���������
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();
}


void BrickIndestrctbl::drawBrick() {
	//������ ������������� �������� ����� ������
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();

	glBegin(GGL_STRING);
	glColor3f(0, 0, 0);
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();
}

void BrickBoost::drawBrick() {
	glBegin(GL_TRIANGLE_FAN); // ������� �������������
	// � ������ ������, ������������ ����� ��������� 
	// ������ ������ �����, ���� ���� 
	//�������� ���� ��������� � ����������� �� ��� ������
	if (lifes == GREEN)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else if (lifes == YELLOW) {
		glColor3f(1.0f, 1.0f, 0.0f);
	}
	else if (lifes == RED) {
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	//�������� ������� ����� ���������
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();

	glBegin(GGL_STRING); // ������ ����� ��� ���������, ����� ���� �������
	glColor3f(0, 0, 0);
	//�������� ������� ����� ���������
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();

	//������ ������� ��������� ������ �������
	glColor3f(0.0f, 0.75f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x - width * 0.3f, y - height * 0.1f);
	glVertex2f(x - width * 0.3f, y + height * 0.1f);
	glVertex2f(x + width * 0.1f, y + height * 0.1f);
	glVertex2f(x + width * 0.1f, y - height * 0.1f);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x + width * 0.1f, y - height * 0.2f);
	glVertex2f(x + width * 0.3f, y);
	glVertex2f(x + width * 0.1f, y + height * 0.2f);
	glEnd();
}


void Bonus::drawBonus() // ������ �����, ��� ����� rgb �����
{
	float x0;
	float y0;
	glBegin(GL_TRIANGLE_FAN); // ������� �������������
	// � ������ ������, ������������ ����� ��������� 
	// ������ ������ �����, ���� ����
	int cnt = 20; // ��� ������ �����, ��� ����� ������� ����� �����
	float alpha = 3.1415926f * 2.0f / cnt; // ����, ��������� �� ������ ������
	for (int i = -1; i < cnt; i++) { // ������ �������� ����� �� ����������
		if (i < 6) { // ���-��� ������ ����� �����������

			glColor3f(1, 0, 0);
		}
		else if (i > 5 && i < 13) {
			glColor3f(0, 1, 0);
		}
		else {
			glColor3f(0, 0, 1);
		}
		x0 = (float)sin((double)alpha * (double)i) * radius;
		y0 = (float)cos((double)alpha * (double)i) * radius;
		glVertex2f(x0 + x, y0 + y); // ������ ����� �� ����������
	}
	glEnd();
}