#include "ball.h"
#include "carriage.h" // *не подключаем carriage.h в ball.h, а подключаем в ball.cpp , так мы решаем проблему
// циклического подключения, это используется и для brick.h и для bonus.h
#include "brick.h" // то же самое
#include "bonus.h"


int sgn(float val) // математическая функция сигнум
{
	if (val > 0) {
		return 1;
	}
	else if (val < 0) {
		return -1;
	}
	else {
		return 0;
	}
}

bool Ball::CrossPoint(float x1, float y1) // функия пересечения точки шариком
{
	// если расстояние от центра шарика до точки меньше или равно квадрату радиуса шарика
	// возвращаем true, если расстояние больше, то возвращаем false
	return (x - x1) * (x - x1) + (y - y1) * (y - y1) < radius * radius;
}

bool Ball::CrossLine(float x1, float y1, float x2, float y2) // функция пересечения линии шариком
{
	float A = y2 - y1;
	float B = x1 - x2;
	float C = x2 * y1 - x1 * y2;
	return fabs(A * x + B * y + C) / sqrt(A * A + B * B) < radius;
	//по обычной формуле из линала находим расстояние от центра шарика до линии
	//и сравниваем его так же как в прошлой функции
}

void Ball::BounceOffCarriage(Carriage& carriage) 
{
	// проверяем на попадание шарика на каретку
	//cначала проверяем шарик по принадлежности к отрезку относительно левых и правых краев кареткию
	//затем проверяем, чтобы шарик был ниже или равен координате каретки по Y
	if (x + radius >= carriage.getX() - carriage.getLength() &&
		x - radius <= carriage.getX() + carriage.getLength() &&
		y - radius <= carriage.getY() && !(y + radius <= carriage.getY())
		)
	{
		dy = float(cos(((x - carriage.getX()) / carriage.getLength()) * M_PI_4) * M_SQRT2 * speed);
		dx = float(sin(((x - carriage.getX()) / carriage.getLength()) * M_PI_4) * M_SQRT2 * speed);
		// изменяем компоненты скорости по х и у в соответствии с формулами:
		// dy = cos(x - car.x/car.length)*pi/4*speed
		// dy = sin(x - car.x/car.length)*pi/4*speed
	}
}

void Ball::Mirror(float x1, float y1) 
{
	float ballvec = float(atan2(dx, dy)); // вектор движения шарика
	float crossvec = float(atan2(x - x1, y - y1)); // вектор столкновения шарика и точки

	float resvec = float(M_PI - ballvec + crossvec * 2.0f); // результирующий вектор столкновения
	float speed = float(sqrt(dx * dx + dy * dy)); // модуль скорости

	// получаем новые компоненты скорости по осям Y и X
	dx = float(sin(resvec) * speed); 
	dy = float(cos(resvec) * speed);
}

int const ZERO_LIFES = 0;
int const BONUS_CHANCE = 10;


void Ball::BounceOffBrick(std::vector<Brick*>& bricks, std::vector<Bonus*>& bonuses, int& score)
{
	if (!bricks.empty()) {
		float height_2 = bricks[0]->getHeight() / 2.0f; // половина высоты кирпичика для удобства
		float width_2 = bricks[0]->getWidth() / 2.0f; // половина ширины кирпичика для удобства

		for (size_t i = 0; i < bricks.size(); i++)
		{
			// первые четыре проверки, это проверки на столкновение с горизонтальными
			// и вертикальными линиями кирпичиков, в этом случае отражение происходит без изменения угла
			if (x > bricks[i]->getX() - width_2 && x < bricks[i]->getX() + width_2 &&
				CrossLine(bricks[i]->getX() - width_2, bricks[i]->getY() - height_2,
					bricks[i]->getX() + width_2, bricks[i]->getY() - height_2))
			{
				// общий для всех проверок кусок кода
				// после столкновения происходит удаление одной из трех жизней кирпичика
				// и когда жизни кирпичика равны нулю, очищаем память, выделенную для кирпичика
				// и удаляем позицию кирпичика из вектора кирпичиков
				if (bricks[i]->lifeBreak(*this, score) == ZERO_LIFES) 
				{
					score++;
					std::cout << "You have destroyed a brick" << std::endl << "+1 point" << std::endl;
					std::cout << "Your SCORE: " << score << std::endl;

					if (rand() % BONUS_CHANCE == 1) 
					{
						bonuses.push_back(new Bonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				dy *= -1;
				return;
			}
			if (y > bricks[i]->getY() - height_2 && y < bricks[i]->getY() + height_2 &&
				CrossLine(bricks[i]->getX() - width_2, bricks[i]->getY() - height_2,
					bricks[i]->getX() - width_2, bricks[i]->getY() + height_2))
			{
				if (bricks[i]->lifeBreak(*this, score) == ZERO_LIFES)
				{
					score++;
					std::cout << "You have destroyed a brick" << std::endl << "+1 point" << std::endl;
					std::cout << "Your SCORE: " << score << std::endl;

					if (rand() % BONUS_CHANCE == 1) 
					{
						bonuses.push_back(new Bonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				dx *= -1;
				return;
			}
			if (x > bricks[i]->getX() - width_2 && x < bricks[i]->getX() + width_2 &&
				CrossLine(bricks[i]->getX() - width_2, bricks[i]->getY() + height_2,
					bricks[i]->getX() + width_2, bricks[i]->getY() + height_2))
			{
				if (bricks[i]->lifeBreak(*this, score) == ZERO_LIFES)
				{
					score++;
					std::cout << "You have destroyed a brick" << std::endl << "+1 point" << std::endl;
					std::cout << "Your SCORE: " << score << std::endl;

					if (rand() % BONUS_CHANCE == 1) {
						bonuses.push_back(new Bonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				dy *= -1;
				return;
			}
			if (y > bricks[i]->getY() - height_2 && y < bricks[i]->getY() + height_2 &&
				CrossLine(bricks[i]->getX() + width_2, bricks[i]->getY() + height_2,
					bricks[i]->getX() + width_2, bricks[i]->getY() - height_2))
			{
				if (bricks[i]->lifeBreak(*this, score) == ZERO_LIFES)
				{
					score++;
					std::cout << "You have destroyed a brick" << std::endl << "+1 point" << std::endl;
					std::cout << "Your SCORE: " << score << std::endl;

					if (rand() % BONUS_CHANCE == 1) 
					{
						bonuses.push_back(new Bonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				dx *= -1;
				return;
			}
			// следующие четыре серии проверок созданы для более менее реалистичного отражения шарика от угла
			// проверяется пересечение каждого угла кирпичика с шариком, а затем происходит отражение шарика от угла
			if (CrossPoint(bricks[i]->getX() - width_2, bricks[i]->getY() - height_2))
			{
				if (bricks[i]->lifeBreak(*this, score) == ZERO_LIFES)
				{
					score++;
					std::cout << "You have destroyed a brick" << std::endl << "+1 point" << std::endl;
					std::cout << "Your SCORE: " << score << std::endl;

					if (rand() % BONUS_CHANCE == 1) {
						bonuses.push_back(new Bonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				Mirror(bricks[i]->getX() - width_2, bricks[i]->getY() - height_2);
				return;
			}
			if (CrossPoint(bricks[i]->getX() - width_2, bricks[i]->getY() + height_2)) 
			{
				if (bricks[i]->lifeBreak(*this, score) == ZERO_LIFES)
				{
					score++;
					std::cout << "You have destroyed a brick" << std::endl << "+1 point" << std::endl;
					std::cout << "Your SCORE: " << score << std::endl;

					if (rand() % BONUS_CHANCE == 1) {
						bonuses.push_back(new Bonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				Mirror(bricks[i]->getX() - width_2, bricks[i]->getY() + height_2);
				return;
			}
			if (CrossPoint(bricks[i]->getX() + width_2, bricks[i]->getY() + height_2)) 
			{
				if (bricks[i]->lifeBreak(*this, score) == ZERO_LIFES)
				{
					score++;
					std::cout << "You have destroyed a brick" << std::endl << "+1 point" << std::endl;
					std::cout << "Your SCORE: " << score << std::endl;

					if (rand() % BONUS_CHANCE == 1) 
					{
						bonuses.push_back(new Bonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				Mirror(bricks[i]->getX() + width_2, bricks[i]->getY() + height_2);
				return;
			}
			if (CrossPoint(bricks[i]->getX() + width_2, bricks[i]->getY() - height_2)) 
			{
				if (bricks[i]->lifeBreak(*this, score) == ZERO_LIFES)
				{
					score++;
					std::cout << "You have destroyed a brick" << std::endl << "+1 point" << std::endl;
					std::cout << "Your SCORE: " << score << std::endl;

					if (rand() % BONUS_CHANCE == 1) 
					{
						bonuses.push_back(new Bonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				Mirror(bricks[i]->getX() + width_2, bricks[i]->getY() - height_2);
				return;
			}
		}
	}
}

bool Ball::Move(Carriage& carriage, std::vector<Brick*>& bricks, std::vector<Bonus*>& bonuses, int& score) // cамая важная функция, отвечает за перемещение шарика
{
	x += dx; //при каждом вызове функции координаты меняются на dx
	y += dy; //или, в случае с y, на dy

	BounceOffCarriage(carriage); // подключили к движению шарика его отражение от каретки
	BounceOffBrick(bricks, bonuses, score); // подключили к движению шарика его отражение от кирпичиков

	// дальше мы ставим ограничения для шарика
	// он не может пересекать границы поля
	if (CrossLine(-1, 1, 1, 1)) // верхняя граница поля
	{
		dy *= -1; // изменяем скорость обратно текущей
		return false;
	}
	if (CrossLine(-1, -1, 1, -1))  // нижняя граница поля
	{
		std::cout << "Ball fell over the lower border" << std::endl;

		dy *= -1; // изменяем скорость обратно текущей
		return true; // если упало внизз возвращаем true
	}
	if (CrossLine(-1, -1, -1, 1)) // левая граница поля
	{
		dx *= -1; // изменяем скорость обратно текущей
		return false;
	}
	if (CrossLine(1, -1, 1, 1)) // правая граница поля
	{
		dx *= -1; // изменяем скорость обратно текущей
		return false;
	}
	return false;
}