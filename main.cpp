#include "ball.h"
#include "carriage.h"
#include "brick.h"
#include "bonus.h"
#include <iostream>
#include <vector>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

bool pause = false; // ���������� ��������� �����, ���� �� �����������, ���� ����� true

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
		768,//������ ������
		768,//������ ������
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);

	/* enable OpenGL for the window */
	EnableOpenGL(hwnd, &hDC, &hRC);

	glScalef(float(768) / float(768), 1, 1);


	std::vector<Ball*> balls; // ������� ������ ������ ��� �������, �� ����� ������� ����� - 2� �����
	balls.push_back(new Ball(0, 0));

	Carriage carriage; // �������������� �������

	std::vector <Brick*> bricks; // ������� ������ ������ ��� ����������, �� �� ����� ������ ��� �����,
	//������� ������ ��������� � Brick
	std::vector <Ball*> lifes; // ������� ������ �������, ����� 
	std::vector <Bonus*> bonuses; // ������� ������ ������ ��� �������



	int score = 0;

	float startX = -0.95f; // ��������� ����� ��� ���������� ����� �� ����������
	float startY = 0.8f;

	srand(time(NULL)); // �������������� ��������� ��������� �����, ����� �� ��� ������ ���������, � �� ���������������
	int brick_gen;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 20; j++) {
			brick_gen = rand() % 100 + 1; // ��������� ����� �� 1 �� 100
			if (brick_gen < 15) // ���� �� ��������� ���������������� ����� 15%
			{ 
				bricks.push_back(new BrickIndestrctbl(startX + j * 0.1f, startY - i * 0.1f));
			}
			else if (brick_gen > 70) //���� �� ��������� ����������� ����� 30%
			{
				bricks.push_back(new BrickBoost(startX + j * 0.1f, startY - i * 0.1f));
			}
			else // ���� �� ��������� �������� ����� 55%
			{
				bricks.push_back(new Brick(startX + j * 0.1f, startY - i * 0.1f));
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		lifes.push_back(new Ball(0.95f - i * 0.05f, -0.95f)); // ������� ����� � ������ ������ ����
	}

	// ��������� ��� �������� �������, ���������� � �������
	std::vector<Brick*>::iterator it;

	AllocConsole(); // ��������� �������, ���� ����� ���������� ����, ��� ���� � ������ ����� cout
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
		else if (pause != true) // ���� ����� true �� ���� �� �����������
		{
			/* ����� ������� ��� �������� � ����� */

			glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // ���� ����
			glClear(GL_COLOR_BUFFER_BIT);
			
			it = bricks.begin(); // ������ �������� �� ������ ������� ����������
			for (; it != bricks.end(); it++)
			{
				(*it)->drawBrick();// ���������� ���������������� ��������� ����������
			}


			if (balls.size() == 2) // ������������ �������
			{
				if (balls[0]->CrossPoint(balls[1]->getX(), balls[1]->getY())) // ���� ����� ������� ������������
				{
					balls[0]->Mirror(balls[1]->getX(), balls[1]->getY()); // �� �������� ��� ��� ������ 
					balls[1]->Mirror(balls[0]->getX(), balls[0]->getY()); // �� ����� ����������
				}
			}


			for (size_t iter_balls = 0; iter_balls < balls.size(); iter_balls++)
			{
				balls[iter_balls]->drawBall();// ���������� ���������������� ��������� ����������

				if (balls[iter_balls]->Move(carriage, bricks, bonuses, score)) // ���������� �������� ������
				{
					if (balls.size() == 2) // ���� ������� � ���� 2 ��-�� ������, �� ������� �������
					{
						delete balls[iter_balls]; // ������� ������ ���������� ��� �����
						balls.erase(balls.begin() + iter_balls); // �������� ������ � ����� � ��������� ������ ������
					}
					else if (!lifes.empty()) {
						score -= 25;
						std::cout << "You loste 1 life" << std::endl << lifes.size() << " lifes remained" << std::endl;
						std::cout << "-25 points" << std::endl;
						std::cout << "Your SCORE: " << score << std::endl;
						lifes.pop_back(); // ������� ���� �����
						delete balls[iter_balls]; // ��� �� ������� ����� �� ������ � �������
						balls.erase(balls.begin() + iter_balls);
						balls.push_back(new Ball(carriage.getX(), carriage.getY() + 0.1f)); // ������� ����� ����� �� �������� �������
					}
					else // ���� ����� ��������� - ����� ����
					{
						exit(1);
					}
				}
			}

			for (size_t iter_bonuses = 0; iter_bonuses < bonuses.size(); iter_bonuses++)
			{
				bonuses[iter_bonuses]->drawBonus(); //���������� ��������� �������
				if (bonuses[iter_bonuses]->Fall(carriage, balls, score)) // ���������� ������� �������
				{
					delete bonuses[iter_bonuses]; // Fall ���� true ���� ����� ������ �������� ��� ���� �� ������� �����
					// ������� ������� ������ ���������� �� ���� �����
					bonuses.erase(bonuses.begin() + iter_bonuses); // ������� �� ������� 
				}
			}

			for (size_t iter_lifes = 0; iter_lifes < lifes.size(); iter_lifes++) 
			{
				lifes[iter_lifes]->drawBall(); // ������ ����� � ����� ������ ����
			}

			carriage.drawCarriage(); // ������ �������
			
			carriage.Move('A', 'D', -1, 1); // A - ������� �����, D - ������� ������, -1 � 1 - ������� �����

			SwapBuffers(hDC);

			Sleep(10); //�������� ����� ������� � ��
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

	case WM_KEYDOWN: //����� ������ ������ ����� ������ ����������
	{
		switch (wParam) //� ����� ����, � ������ ������ ���� ��������
		{
		case VK_ESCAPE: //������ ESCAPE ������ ����
			//PostQuitMessage(0);
			if (pause == false) // ���� ����� ���, ������ ����� ��� ������� ESC
			{
				std::cout << "GAME IS PAUSED, PRESS ESC TO UNPAUSE THE GAME" << std::endl;
				pause = true;
		    }
			else if (pause == true) // ���� ����� ����, �������� � ��� ������� ESC
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