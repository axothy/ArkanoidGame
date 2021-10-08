#include <windows.h> //необходимо для открытия окна
#include <gl/gl.h> //подключение h файла библиотеки openGL
#include <math.h> // подключим матешу для функций синуса и косинуса
#include <vector> // vector нужен для использования вектора кирпичиков
#include <iostream>

#define _USE_MATH_DEFINES // подключим математические константы

#pragma comment(lib, "opengl32.lib") //подключение самой библиотеки openGL

class Carriage; // *пишем ссылку на класс, это требуется чтобы использовать этот класс в функциях шарика,
// избегая при этом циклического подключения
class Brick; // то же самое
class Bonus;

class Ball { // создаем класс шарик
	//можно назвать то что снизу - интерфейс класса
	//т.к. перечислены все характеристики класса, методы, свойства и тд
protected:
	float x, y; // координаты шарика
	float speed = 0.01f; // величина компоненты скорости, сделано таким образом, чтобы удобно было
	float dx = speed, dy = speed; // компоненты скорости шарика
	const float radius = 0.02f; //радиус шарика
	// ускорять шарик и изменять его угол полета при отражении от каретки

public:
	Ball(float x1, float y1) : x(x1), y(y1) {} // конструктор мячика
	// здесь я задаю его координаты х и у как начальные х1 и у1, а dx dy покомпонентно 0.01

	// функция рисовки шарика
	void drawBall(); 


	// функия пересечения точки шариком
	bool CrossPoint(float x1, float y1); 

	// функция пересечения линии шариком
	bool CrossLine(float x1, float y1, float x2, float y2); 

	// функция отскока шарика от каретки
	void BounceOffCarriage(Carriage& carriage); 
	// функция отскока шарика от кирпича
	void BounceOffBrick(std::vector<Brick*>& bricks, std::vector<Bonus*>& bonuses, int& score);
	// функция зеркального отражения шарика от точки
	void Mirror(float x1, float y1);

	// функция перемещения шарика
	bool Move(Carriage& carriage, std::vector<Brick*>& bricks, std::vector<Bonus*>& bonuses, int& score);

	// функция увеличения скорости шарика
	void speedBoost(float boost) { speed += boost; }

	float getX() { return x; } // так как координаты и радиус у нас protected
	float getY() { return y; } // создаем эти функции для получения данных значений шарика
	float getRad() { return radius; } 
	// если функцию возможно реализовать в одну строчку,
	// то её реализацию можно писать в .h файл

	void changedY() { dy *= -1; } // функции для бонусного изменения
	void changedX() { dx *= -1; } // направления движения шарика
};