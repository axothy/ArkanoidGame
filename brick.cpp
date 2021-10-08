#include "brick.h"
#include "ball.h"

int Brick::lifeBreak(Ball& ball, int& score) // ��������� ����� � �������� �������, ��������� ���� � ������� ����� �������
{ 
	score++; 
	std::cout << "You took down 1 life of a brick" << std::endl << "+1 point" << std::endl;
	std::cout << "Your SCORE: " << score << std::endl;

	lifes--; 
	return lifes; 
}

int BrickIndestrctbl::lifeBreak(Ball& ball, int& score) // � �������������� ������� ����� �� �������
{ 
	std::cout << "You hit an indestructible brick" << std::endl;

	return lifes; 
}

int BrickBoost::lifeBreak(Ball& ball, int& score) //�������� �����, ��������� ����, �������� �����
{
	score++;
	std::cout << "You took down 1 life of a brick" << std::endl << "+1 point" << std::endl;
	std::cout << "Your SCORE: " << score << std::endl;


	lifes--;
	ball.speedBoost(boost);
	return lifes;
}


