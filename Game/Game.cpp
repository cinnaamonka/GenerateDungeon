#include <iostream>
#include <cstdlib> 
#include <ctime>   

#include "Game.h"

Game::Game() :m_ScreenSize{ 900 }
{
	m_pMap = new Map(100);
}

Game::~Game() {}


void Game::Initialize(HINSTANCE hInstance)
{
	AbstractGame::Initialize(hInstance);

	GAME_ENGINE->SetTitle(_T("Game Engine version 7_02"));
	GAME_ENGINE->RunGameLoop(true);

	GAME_ENGINE->SetWidth(m_ScreenSize);
	GAME_ENGINE->SetHeight(m_ScreenSize);
	GAME_ENGINE->SetFrameRate(50);

	tstringstream buffer;

	buffer << _T("PR");

	buffer << (TCHAR)VK_LEFT;
	buffer << (TCHAR)VK_RIGHT;
	buffer << (TCHAR)VK_UP;
	buffer << (TCHAR)VK_DOWN;

	GAME_ENGINE->SetKeyList(buffer.str());

	m_pMap->Initialize(hInstance);
}

void Game::Start()
{
	m_pMap->Start();
}

void Game::End() {}

void Game::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{
	m_pMap->MouseButtonAction(isLeft, isDown, x, y, wParam);
}

void Game::MouseWheelAction(int x, int y, int distance, WPARAM wParam) {}

void Game::MouseMove(int x, int y, WPARAM wParam) {}

void Game::CheckKeyboard() {}

void Game::KeyPressed(TCHAR cKey)
{
	m_pMap->KeyPressed(cKey);
}

void Game::Paint(RECT rect)
{
	m_pMap->Paint(rect);
}

void Game::Tick()
{
	const int ticks = 1;

	for (int i = 0; i < ticks; ++i)
	{
		m_pMap->Tick();
	}
}

void Game::CallAction(Caller* callerPtr) {}