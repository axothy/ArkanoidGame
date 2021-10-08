#include "ball.h"
#include "carriage.h" // *�� ���������� carriage.h � ball.h, � ���������� � ball.cpp , ��� �� ������ ��������
// ������������ �����������, ��� ������������ � ��� brick.h � ��� bonus.h
#include "brick.h" // �� �� �����
#include "bonus.h"


int sgn(float val) // �������������� ������� ������
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

bool Ball::CrossPoint(float x1, float y1) // ������ ����������� ����� �������
{
	// ���� ���������� �� ������ ������ �� ����� ������ ��� ����� �������� ������� ������
	// ���������� true, ���� ���������� ������, �� ���������� false
	return (x - x1) * (x - x1) + (y - y1) * (y - y1) < radius * radius;
}

bool Ball::CrossLine(float x1, float y1, float x2, float y2) // ������� ����������� ����� �������
{
	float A = y2 - y1;
	float B = x1 - x2;
	float C = x2 * y1 - x1 * y2;
	return fabs(A * x + B * y + C) / sqrt(A * A + B * B) < radius;
	//�� ������� ������� �� ������ ������� ���������� �� ������ ������ �� �����
	//� ���������� ��� ��� �� ��� � ������� �������
}

void Ball::BounceOffCarriage(Carriage& carriage) 
{
	// ��������� �� ��������� ������ �� �������
	//c������ ��������� ����� �� �������������� � ������� ������������ ����� � ������ ����� ��������
	//����� ���������, ����� ����� ��� ���� ��� ����� ���������� ������� �� Y
	if (x + radius >= carriage.getX() - carriage.getLength() &&
		x - radius <= carriage.getX() + carriage.getLength() &&
		y - radius <= carriage.getY() && !(y + radius <= carriage.getY())
		)
	{
		dy = float(cos(((x - carriage.getX()) / carriage.getLength()) * M_PI_4) * M_SQRT2 * speed);
		dx = float(sin(((x - carriage.getX()) / carriage.getLength()) * M_PI_4) * M_SQRT2 * speed);
		// �������� ���������� �������� �� � � � � ������������ � ���������:
		// dy = cos(x - car.x/car.length)*pi/4*speed
		// dy = sin(x - car.x/car.length)*pi/4*speed
	}
}

void Ball::Mirror(float x1, float y1) 
{
	float ballvec = float(atan2(dx, dy)); // ������ �������� ������
	float crossvec = float(atan2(x - x1, y - y1)); // ������ ������������ ������ � �����

	float resvec = float(M_PI - ballvec + crossvec * 2.0f); // �������������� ������ ������������
	float speed = float(sqrt(dx * dx + dy * dy)); // ������ ��������

	// �������� ����� ���������� �������� �� ���� Y � X
	dx = float(sin(resvec) * speed); 
	dy = float(cos(resvec) * speed);
}

int const ZERO_LIFES = 0;
int const BONUS_CHANCE = 10;


void Ball::BounceOffBrick(std::vector<Brick*>& bricks, std::vector<Bonus*>& bonuses, int& score)
{
	if (!bricks.empty()) {
		float height_2 = bricks[0]->getHeight() / 2.0f; // �������� ������ ��������� ��� ��������
		float width_2 = bricks[0]->getWidth() / 2.0f; // �������� ������ ��������� ��� ��������

		for (size_t i = 0; i < bricks.size(); i++)
		{
			// ������ ������ ��������, ��� �������� �� ������������ � ���������������
			// � ������������� ������� ����������, � ���� ������ ��������� ���������� ��� ��������� ����
			if (x > bricks[i]->getX() - width_2 && x < bricks[i]->getX() + width_2 &&
				CrossLine(bricks[i]->getX() - width_2, bricks[i]->getY() - height_2,
					bricks[i]->getX() + width_2, bricks[i]->getY() - height_2))
			{
				// ����� ��� ���� �������� ����� ����
				// ����� ������������ ���������� �������� ����� �� ���� ������ ���������
				// � ����� ����� ��������� ����� ����, ������� ������, ���������� ��� ���������
				// � ������� ������� ��������� �� ������� ����������
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
			// ��������� ������ ����� �������� ������� ��� ����� ����� ������������� ��������� ������ �� ����
			// ����������� ����������� ������� ���� ��������� � �������, � ����� ���������� ��������� ������ �� ����
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

bool Ball::Move(Carriage& carriage, std::vector<Brick*>& bricks, std::vector<Bonus*>& bonuses, int& score) // c���� ������ �������, �������� �� ����������� ������
{
	x += dx; //��� ������ ������ ������� ���������� �������� �� dx
	y += dy; //���, � ������ � y, �� dy

	BounceOffCarriage(carriage); // ���������� � �������� ������ ��� ��������� �� �������
	BounceOffBrick(bricks, bonuses, score); // ���������� � �������� ������ ��� ��������� �� ����������

	// ������ �� ������ ����������� ��� ������
	// �� �� ����� ���������� ������� ����
	if (CrossLine(-1, 1, 1, 1)) // ������� ������� ����
	{
		dy *= -1; // �������� �������� ������� �������
		return false;
	}
	if (CrossLine(-1, -1, 1, -1))  // ������ ������� ����
	{
		std::cout << "Ball fell over the lower border" << std::endl;

		dy *= -1; // �������� �������� ������� �������
		return true; // ���� ����� ����� ���������� true
	}
	if (CrossLine(-1, -1, -1, 1)) // ����� ������� ����
	{
		dx *= -1; // �������� �������� ������� �������
		return false;
	}
	if (CrossLine(1, -1, 1, 1)) // ������ ������� ����
	{
		dx *= -1; // �������� �������� ������� �������
		return false;
	}
	return false;
}