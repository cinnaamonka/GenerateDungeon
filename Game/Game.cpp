//-----------------------------------------------------------------
// Main Game File
// C++ Source - X.cpp - version v7_02
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

//-----------------------------------------------------------------
// X methods																				
//-----------------------------------------------------------------
#include "Game.h"

Game::Game() :m_ScreenSize{ 900 }
{
	m_pMap = new Map(100);
}

Game::~Game()
{
	// nothing to destroy
}


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

	GAME_ENGINE->SetKeyList(buffer.str());

	m_pMap->Initialize(hInstance);
}

void Game::Start()
{
	m_pMap->Start();
}

void Game::End()
{
	// Insert the code that needs to be executed at the closing of the game
}

void Game::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{
	m_pMap->MouseButtonAction(isLeft, isDown, x, y, wParam);
}


void Game::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{
	// Insert the code that needs to be executed when the game registers a mouse wheel action
}

void Game::MouseMove(int x, int y, WPARAM wParam)
{
	// Insert the code that needs to be executed when the mouse pointer moves across the game window

	/* Example:
	if ( x > 261 && x < 261 + 117 ) // check if mouse position is within x coordinates of choice
	{
		if ( y > 182 && y < 182 + 33 ) // check if mouse position also is within y coordinates of choice
		{
			GAME_ENGINE->MessageBox(_T("Da mouse wuz here."));
		}
	}
	*/
}

void Game::CheckKeyboard()
{
	// Here you can check if a key of choice is held down
	// Is executed once per frame if the Game Loop is running 

	/* Example:
	if (GAME_ENGINE->IsKeyDown(_T('K'))) xIcon -= xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('L'))) yIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('M'))) xIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('O'))) yIcon -= ySpeed;
	*/
}

void Game::KeyPressed(TCHAR cKey)
{
	m_pMap->KeyPressed(cKey);
	// DO NOT FORGET to use SetKeyList() !!

	// Insert the code that needs to be executed when a key of choice is pressed
	// Is executed as soon as the key is released
	// You first need to specify the keys that the game engine needs to watch by using the SetKeyList() method

	/* Example:
	switch (cKey)
	{
	case _T('K'): case VK_LEFT:
		GAME_ENGINE->MessageBox(_T("Moving left."));
		break;
	case _T('L'): case VK_DOWN:
		GAME_ENGINE->MessageBox(_T("Moving down."));
		break;
	case _T('M'): case VK_RIGHT:
		GAME_ENGINE->MessageBox(_T("Moving right."));
		break;
	case _T('O'): case VK_UP:
		GAME_ENGINE->MessageBox(_T("Moving up."));
		break;
	case VK_ESCAPE:
		GAME_ENGINE->MessageBox(_T("Escape menu."));
	}
	*/
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

void Game::CallAction(Caller* callerPtr)
{
	// Insert the code that needs to be executed when a Caller has to perform an action
}


