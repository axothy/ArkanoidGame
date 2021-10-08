#include "ball.h"
#include "carriage.h"
#include "brick.h"
#include "bonus.h"
#include <iostream>
#include <vector>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

bool pause = false; // глобальная константа паузы, игра не продолжится, если будет true

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hwnd;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	BOOL bQuit = FALSE;

	/* register window class */
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = (LPCWSTR)"GLSample";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


	if (!RegisterClassEx(&wcex))
		return 0;


	/* create main window */
	hwnd = CreateWindowEx(0,
		(LPCWSTR)"GLSample",
		(LPCWSTR)"OpenGL Sample",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		768,//ширина экрана
		768,//высота экрана
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);

	/* enable OpenGL for the window */
	EnableOpenGL(hwnd, &hDC, &hRC);

	glScalef(float(768) / float(768), 1, 1);


	std::vector<Ball*> balls; // создаем пустой вектор для шариков, тк может выпасть бонус - 2й шарик
	balls.push_back(new Ball(0, 0));

	Carriage carriage; // инициализируем каретку

	std::vector <Brick*> bricks; // создаем пустой вектор для кирпичиков, мы не знаем какими они будут,
	//поэтому ставим указатель у Brick
	std::vector <Ball*> lifes; // создаем вектор шариков, когда 
	std::vector <Bonus*> bonuses; // создаем пустой вектор для бонусов



	int score = 0;

	float startX = -0.95f; // начальная точка для построения стены из кирпичиков
	float startY = 0.8f;

	srand(time(NULL)); // инициализируем генератор случайных чисел, чтобы он был именно случайным, а не псевдослучайным
	int brick_gen;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 20; j++) {
			brick_gen = rand() % 100 + 1; // случайные числа от 1 до 100
			if (brick_gen < 15) // шанс на выпадение неразбивающегося блока 15%
			{ 
				bricks.push_back(new BrickIndestrctbl(startX + j * 0.1f, startY - i * 0.1f));
			}
			else if (brick_gen > 70) //шанс на выпадение ускоряющего блока 30%
			{
				bricks.push_back(new BrickBoost(startX + j * 0.1f, startY - i * 0.1f));
			}
			else // шанс на выпадение обычного блока 55%
			{
				bricks.push_back(new Brick(startX + j * 0.1f, startY - i * 0.1f));
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		lifes.push_back(new Ball(0.95f - i * 0.05f, -0.95f)); // создаем жизни в нижнем правом углу
	}

	// итераторы для векторов шариков, кирпичиков и бонусов
	std::vector<Brick*>::iterator it;

	AllocConsole(); // открываем консоль, куда будем записывать счет, ход игры и прочее через cout
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	std::cout << "THE GAME HAS STARTED" << std::endl;

	/* program main loop */
	while (!bQuit)
	{
		/* check for messages */
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/* handle or dispatch messages */
			if (msg.message == WM_QUIT)
			{
				bQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else if (pause != true) // если пауза true то игра не продолжится
		{
			/* здесь пишутся все действия в цикле */

			glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // цвет фона
			glClear(GL_COLOR_BUFFER_BIT);
			
			it = bricks.begin(); // ставим итератор на начало вектора кирпичиков
			for (; it != bricks.end(); it++)
			{
				(*it)->drawBrick();// производим последовательное рисование кирпичиков
			}


			if (balls.size() == 2) // столкновение шариков
			{
				if (balls[0]->CrossPoint(balls[1]->getX(), balls[1]->getY())) // если точки шариков пересекаются
				{
					balls[0]->Mirror(balls[1]->getX(), balls[1]->getY()); // то отражаем эти оба шарика 
					balls[1]->Mirror(balls[0]->getX(), balls[0]->getY()); // от точки персечения
				}
			}


			for (size_t iter_balls = 0; iter_balls < balls.size(); iter_balls++)
			{
				balls[iter_balls]->drawBall();// производим последовательное рисование кирпичиков

				if (balls[iter_balls]->Move(carriage, bricks, bonuses, score)) // подключаем движение шарика
				{
					if (balls.size() == 2) // если шариков в игре 2 из-за бонуса, то удаляем упавший
					{
						delete balls[iter_balls]; // очищаем память выделенную под шарик
						balls.erase(balls.begin() + iter_balls); // изменяем вектор в связи с удалением одного шарика
					}
					else if (!lifes.empty()) {
						score -= 25;
						std::cout << "You loste 1 life" << std::endl << lifes.size() << " lifes remained" << std::endl;
						std::cout << "-25 points" << std::endl;
						std::cout << "Your SCORE: " << score << std::endl;
						lifes.pop_back(); // удаляем одну жизнь
						delete balls[iter_balls]; // так же удаляем мячик из памяти и вектора
						balls.erase(balls.begin() + iter_balls);
						balls.push_back(new Ball(carriage.getX(), carriage.getY() + 0.1f)); // создаем новый шарик по середине каретки
					}
					else // если жизни кончились - конец игры
					{
						exit(1);
					}
				}
			}

			for (size_t iter_bonuses = 0; iter_bonuses < bonuses.size(); iter_bonuses++)
			{
				bonuses[iter_bonuses]->drawBonus(); //производим рисование бонусов
				if (bonuses[iter_bonuses]->Fall(carriage, balls, score)) // подключаем падение бонусов
				{
					delete bonuses[iter_bonuses]; // Fall дает true если бонус поднят кареткой или упал за пределы карты
					// поэтому очищаем память выделенную на этот бонус
					bonuses.erase(bonuses.begin() + iter_bonuses); // удаляем из вектора 
				}
			}

			for (size_t iter_lifes = 0; iter_lifes < lifes.size(); iter_lifes++) 
			{
				lifes[iter_lifes]->drawBall(); // рисуем жизни в нижем правом углу
			}

			carriage.drawCarriage(); // рисуем каретку
			
			carriage.Move('A', 'D', -1, 1); // A - каретка влево, D - каретка вправо, -1 и 1 - границы карты

			SwapBuffers(hDC);

			Sleep(10); //задержка между циклами в мс
		}
	}

	/* shutdown OpenGL */
	DisableOpenGL(hwnd, hDC, hRC);

	/* destroy the window explicitly */
	DestroyWindow(hwnd);

	return int(msg.wParam);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN: //здесь писать случаи когда кнопка опускается
	{
		switch (wParam) //в свитч надо, у каждой кнопки свое название
		{
		case VK_ESCAPE: //кнопка ESCAPE паусит игру
			//PostQuitMessage(0);
			if (pause == false) // если паузы нет, ставим паузу при нажатии ESC
			{
				std::cout << "GAME IS PAUSED, PRESS ESC TO UNPAUSE THE GAME" << std::endl;
				pause = true;
		    }
			else if (pause == true) // если пауза есть, отжимаем её при нажатии ESC
			{
				std::cout << "GAME IS UNPAUSED, PRESS ESC TO PAUSE THE GAME" << std::endl;
				pause = false;
			}
			break;
		}
	}
	break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
	PIXELFORMATDESCRIPTOR pfd;

	int iFormat;

	/* get the device context (DC) */
	*hDC = GetDC(hwnd);

	/* set the pixel format for the DC */
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat(*hDC, &pfd);

	SetPixelFormat(*hDC, iFormat, &pfd);

	/* create and enable the render context (RC) */
	*hRC = wglCreateContext(*hDC);

	wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
}