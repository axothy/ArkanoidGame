#include "bonus.h"
#include "carriage.h"
#include "ball.h"

const float SPEED_BOOST = 0.0025f;

bool Bonus::Fall(Carriage& carriage, std::vector<Ball*> balls, int& score) 
{
	dy += ddy;
	y += dy;
	int randomizer;
	// проверяем на попадание бонуса на каретку
	//cначала проверяем бонус по принадлежности к отрезку относительно левых и правых краев кареткию
	//затем проверяем, чтобы бонус был ниже или равен координате каретки по Y
	if (x + radius >= carriage.getX() - carriage.getLength() &&
		x - radius <= carriage.getX() + carriage.getLength() &&
		y - radius <= carriage.getY() && !(y + radius <= carriage.getY())
		) // можно добавлять любые бонусы ниже
	{
		randomizer = rand() % 100 + 1; // число от 1 до 100
		score += 10;
		if (randomizer <= 20)
		{
			std::cout << "You have picked up a bonus: ball speed up " << std::endl << "+10 points" << std::endl;
			std::cout << "Your SCORE: " << score << std::endl;

			for (int i = 0; i < balls.size(); i++) // бонус на ускорение шариков
			{
				balls[i]->speedBoost(SPEED_BOOST);
			}
		}
		else if (randomizer > 20 && randomizer <= 40) 
		{
			std::cout << "You have picked up a bonus: carriage extension" << std::endl << "+10 points" << std::endl;
			std::cout << "Your SCORE: " << score << std::endl;

			carriage.Grade(1.5); // бонус на расширение каретки
		}
		else if (randomizer > 40 && randomizer <= 60) 
		{
			std::cout << "You have picked up a bonus: carriage compression" << std::endl << "+10 points" << std::endl;
			std::cout << "Your SCORE: " << score << std::endl;
			carriage.Grade(0.75); // бонус на сжатие каретки
		}
		else if (randomizer > 60 && randomizer <= 80 && balls.size() < 2) 
		{
			std::cout << "You have picked up a bonus extra ball" << std::endl << "+10 points" << std::endl;
			std::cout << "Your SCORE: " << score << std::endl;

			if (balls.size() < 2) // бонус на добавление нового шарика
			{
				balls.push_back(new Ball(0, 0.5f));
			}
		}
		else 
		{
			std::cout << "You have picked up a bonus: changing ball trajectory" << std::endl << "+10 points" << std::endl;
			std::cout << "Your SCORE: " << score << std::endl;

			for (int i = 0; i < balls.size(); i++) // бонус на изменение направления движения шариков
			{
				if (rand() % 2 == 1) 
				{
					balls[i]->changedX();
				}
				else
				{
					balls[i]->changedY();
				}
			}
		}
		return true;
	}
	else if (y < -1) // если ниже нижней границы карты
	{
		std::cout << "Bonus fell under the border and was removed" << std::endl;
		return true;
	}
	return false;
}