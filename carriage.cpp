#include "carriage.h"



void Carriage::Move(char left, char right, float borderL, float borderR)

{
	// GeyKeyState(key) - проверяет зажатие той или иной кнопки
	if (GetKeyState(left) < 0) x -= dx;
	else if (GetKeyState(right) < 0) x += dx;

	// проверка левых и правых краев на то, что они меньше левых и правых границ
	// в случае если край выбивается за границы
	// просто перемещаем каретку на то место, где край упирается в границу
	if (x - length < borderL) x = borderL + length;
	if (x + length > borderR) x = borderR - length;
}
