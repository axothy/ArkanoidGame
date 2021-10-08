#include "ball.h"
#include "brick.h"
#include "carriage.h"
#include "bonus.h"

void Ball::drawBall() // реализация функции рисовки шарика
{
	float x0;
	float y0;
	glBegin(GL_TRIANGLE_FAN); // рисовка треугольником
	// в данном случае, треугольники будут строиться 
	// вокруг первой точки, типа веер
	glColor3f(1, 1, 1); // цвет белый
	int cnt = 20; // чем больше точек, тем более гладкий будет шарик
	float alpha = 3.1415926f * 2.0f / cnt; // угол, исходящий от центра шарика
	for (int i = -1; i < cnt; i++) { // просто получаем точки на окружности
		x0 = (float)sin((double)alpha * (double)i) * radius;
		y0 = (float)cos((double)alpha * (double)i) * radius;
		glVertex2f(x0 + x, y0 + y); // ставим точку на окружности
	}
	glEnd();
}

void Carriage::drawCarriage() // рисуем каретку
{
	glBegin(GL_LINE_STRIP); // простая линия
	glColor3f(1, 1, 1); // белый цвет
	glVertex2f(x - length, y); // левый край каретки
	glVertex2f(x + length, y); // правый край каретки
	glEnd();
}


int const GREEN = 3; // цвет в зависимости от текущего числа жизней
int const YELLOW = 2;
int const RED = 1;

void Brick::drawBrick() {
	glBegin(GL_TRIANGLE_FAN); // рисовка треугольником
	// в данном случае, треугольники будут строиться 
	// вокруг первой точки, типа веер 
	//выбираем цвет кирпичика в зависимости от его жизней
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
	//выбираем крайние точки кирпичика
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();

	glBegin(GGL_STRING); // рисуем рамку для крпичиков, чтобы было понятно
	glColor3f(0, 0, 0);
	//выбираем крайние точки кирпичика
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();
}


void BrickIndestrctbl::drawBrick() {
	//рисуем неразрушаемый кирпичик серым цветом
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
	glBegin(GL_TRIANGLE_FAN); // рисовка треугольником
	// в данном случае, треугольники будут строиться 
	// вокруг первой точки, типа веер 
	//выбираем цвет кирпичика в зависимости от его жизней
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
	//выбираем крайние точки кирпичика
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();

	glBegin(GGL_STRING); // рисуем рамку для крпичиков, чтобы было понятно
	glColor3f(0, 0, 0);
	//выбираем крайние точки кирпичика
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();

	//рисуем голубую стрелочку внутри кирпича
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


void Bonus::drawBonus() // рисуем бонус, это будет rgb шарик
{
	float x0;
	float y0;
	glBegin(GL_TRIANGLE_FAN); // рисовка треугольником
	// в данном случае, треугольники будут строиться 
	// вокруг первой точки, типа веер
	int cnt = 20; // чем больше точек, тем более гладкий будет шарик
	float alpha = 3.1415926f * 2.0f / cnt; // угол, исходящий от центра шарика
	for (int i = -1; i < cnt; i++) { // просто получаем точки на окружности
		if (i < 6) { // кое-как делаем шарик трехцветным

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
		glVertex2f(x0 + x, y0 + y); // ставим точку на окружности
	}
	glEnd();
}