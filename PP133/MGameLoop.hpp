#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <string>
#include <iostream>
#include "Player.hpp"
#include "Item.hpp"
#include "Boom.hpp"
#include "MWindowUtil.hpp"
#include <random>

using namespace std;

namespace MuSeoun_Engine
{
	class MGameLoop
	{
	private:
		bool _isGameRunning, gameOver, gameClear;
		
		MWindowUtil* cWindow;
		chrono::system_clock::time_point startRenderTimePoint;
		chrono::duration<double> renderDuration;
		Player* p = new Player();
		Boom* b[10];
		Item* t[1];
		int itemSize = sizeof(t) / sizeof(t[0]);
		int boomSize = sizeof(b) / sizeof(b[0]);
		int scoreR = 0;
		int scoreG = 0;
		int scoreB = 0;
		Image* gameOverImg = new Image("gameOver.bmp");
		Image* gameClearImg = new Image("gameClear.bmp");

		int key;
		double deltaTime;
	public:
		MGameLoop()
		{
			_isGameRunning = false;
			startRenderTimePoint = chrono::system_clock::now();
			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			gameOver = false;
			gameClear = false;
			
			for (int i = 0; i < itemSize; i++)
			{
				t[i] = new Item();
			}
			for (int i = 0; i < boomSize; i++)
			{
				b[i] = new Boom();
			}
			
			char TitleName[] = "KSJ";
			cWindow = new MWindowUtil(480, 640, TitleName, 0.025, 1.0 / 3 * 0.1, 40, 20);
			key = -1;
			deltaTime = 0;
		}
		~MGameLoop() {}

		void Run()
		{
			_isGameRunning = true;
			Initialize();
			while (_isGameRunning)
			{
				Input();
				Update();
				Render();
			}
			Release();
		}
		void Stop()
		{
			_isGameRunning = false;
		}
	private:
		void Initialize() {}
		void Release()
		{
			delete(p);
			for (int i = 0; i < itemSize; i++)
				delete(t[i]);
			for (int i = 0; i < boomSize; i++)
				delete(b[i]);
			delete(cWindow);
		}
		void Input()
		{
			key = cWindow->FindKey();
			
			if (gameOver || gameClear)
			{
				
				if (key == GLFW_KEY_R)
				{
					for (int i = 0; i < itemSize; i++)
					{				
						t[i]->Hide();
					}
					for (int i = 0; i < boomSize; i++)
					{
						b[i]->Hide();
					}
					scoreB = 0;
					scoreG = 0;
					scoreR = 0;
					p->Reset();
					gameOver = false;
					gameClear = false;
				}
			}
			else if(!gameOver)
			{
				cWindow->GameStartscreen();
				if (key == GLFW_KEY_LEFT)
				{
					p->Left(0.3);
				}
				if (key == GLFW_KEY_RIGHT)
				{
					p->Right(0.3);
				}
			}
			
		}
		void Update()
		{
			cWindow->WindowEvent();
			if (cWindow->isEnd())
				_isGameRunning = false;

			if (!gameOver && !gameClear)
			{ 	
				for (int i = 0; i < itemSize; i++)
				{
					if (t[i]->isOn)
					{
						t[i]->Move(deltaTime);
						if (t[i]->y > 25.0f)
						{
							t[i]->Hide();
						}
					}
				}
				int arrNum = -1;
				for (int i = 0; i < itemSize; i++)
				{
					if (!(t[i]->isOn))
					{
						arrNum = i;
						break;
					}
				}
				if (arrNum != -1)
				{
					int count = 0;
					for (int i = 0; i < itemSize; i++)
					{
						if (t[i]->y < 1)
						{
							count++;
						}
					}
					if (count == 1)
					{
						t[arrNum]->Initialize();
					}
				}
				for (int i = 0; i < itemSize; i++)
				{
					if (t[i]->isOn && t[i]->Collider(p))
					{
						t[i]->Hide();
						if (scoreR < 250)
						{
							scoreR += 250;
						}
						else if (scoreR >= 250 && scoreG < 250)
						{
							scoreG += 250;
						}
						else if(scoreR >= 250 && scoreG >= 250 && scoreB < 250)
						{
							scoreB += 250;
							if (scoreR >= 250 && scoreG >= 250 && scoreB >= 250)
							{
								gameClear = true;
								
							}
						}
					}
				}
				
				for (int i = 0; i < boomSize; i++)
				{
					if (b[i]->isOn)
					{
						b[i]->Move(deltaTime);
						if (b[i]->y > 25.0f)
						{ 
							b[i]->Hide();
						}
					}
				}
				int arrNum1 = -1;
				for (int i = 0; i < boomSize; i++)
				{
					if (!(b[i]->isOn))
					{
						arrNum1 = i;
						break;
					}
				}
				if (arrNum1 != -1)
				{
					int count = 0;
					for (int i = 0; i < boomSize; i++)
					{
						if (b[i]->y < 10)
						{
							count++;
						}
					}
					if (count == 10)
					{
						b[arrNum1]->Initialize();
						
					}
				}
				for (int i = 0; i < boomSize; i++)
				{
					if (b[i]->isOn && b[i]->Collider(p))
					{
						gameOver = true;
						
					}
				}
			}

		}
		void Render()
		{
			cWindow->Clear();
			if (!gameOver && !gameClear)
			{

				cWindow->PrintRectangle(p->x, p->y, 0, 0, 0);
				cWindow->PrintcoreRectangle(p->x, p->y, scoreR, scoreG, scoreB);
				
				for (int i = 0; i < boomSize; i++)
				{
					if (b[i]->isOn)
						cWindow->PrintRectangle(b[i]->x, b[i]->y, 0, 0, 0);
				}
				for (int i = 0; i < itemSize; i++)
				{
					if (t[i]->isOn)
						cWindow->PrintRectangle(t[i]->x, t[i]->y, 255, 0, 0);
				}
			}
			if(gameOver)
			{
				cWindow->GameOverscreen(gameOverImg, GL_RED, -0.8, 0.8, -0.05, 0.25);;
			}
			if (gameClear)
			{
				cWindow->GameClearscreen(gameClearImg, GL_GREEN, -0.8, 0.8, -0.05, 0.25);;
			}

			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			startRenderTimePoint = chrono::system_clock::now();
			deltaTime = renderDuration.count();
		}
	};
}
