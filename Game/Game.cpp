#include <iostream>
#include <cstdlib> 
#include <ctime>   

#include "Game.h"

Game::Game() :m_ScreenSize{ 900 }
{
	m_pMap = new Map(100,10000,70,30);
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

	m_pChanceRoomTextBox = new TextBox();
	m_pChanceRoomTextBox->SetBounds(25, 25, 100, 25);
	m_pChanceRoomTextBox->AddActionListener(this);
	m_pChanceRoomTextBox->Show();

	m_pFont = new Font(_T("Verdana"), true, false, false, 32);

	m_pChanceCorridorTextBox = new TextBox();
	m_pChanceCorridorTextBox->SetBounds(25, 75, 100, 25);
	m_pChanceCorridorTextBox->AddActionListener(this);
	m_pChanceCorridorTextBox->Show();
}

void Game::End() 
{
	delete m_pChanceRoomTextBox;
	delete m_pFont;
}

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

	GAME_ENGINE->SetFont(m_pFont);
	GAME_ENGINE->SetColor(RGB(27, 27, 27));

	GAME_ENGINE->DrawString(_T("Room chance"), 130, 20);
	GAME_ENGINE->DrawString(_T("Corridor chance"), 130, 70);
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