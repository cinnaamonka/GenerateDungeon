//-----------------------------------------------------------------
// Main Game File
// C++ Source - X.cpp - version v7_02
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Cell.h"			

//-----------------------------------------------------------------
// X methods																				
//-----------------------------------------------------------------

Cell::Cell(POINT pos, COLORREF color,int size):
	m_Size(size), m_Color(color), m_Position(pos)
{
	// nothing to create
}

Cell::~Cell()
{
	// nothing to destroy
}


void Cell::Initialize(HINSTANCE hInstance)
{
	// Set the required values
	AbstractGame::Initialize(hInstance);
	GAME_ENGINE->SetTitle(_T("Game Engine version 7_02"));
	GAME_ENGINE->RunGameLoop(true);

	// Set the optional values
	GAME_ENGINE->SetWidth(1024);
	GAME_ENGINE->SetHeight(768);
	GAME_ENGINE->SetFrameRate(50);

	// Set the keys that the game needs to listen to
	//tstringstream buffer;
	//buffer << _T("KLMO");
	//buffer << (TCHAR) VK_LEFT;
	//buffer << (TCHAR) VK_RIGHT;
	//GAME_ENGINE->SetKeyList(buffer.str());
}

void Cell::Start()
{
	
}

void Cell::End()
{
	// Insert the code that needs to be executed at the closing of the game
}

void Cell::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{
	// Insert the code that needs to be executed when the game registers a mouse button action

	/* Example:
	if (isLeft == true && isDown == true) // is it a left mouse click?
	{
		if ( x > 261 && x < 261 + 117 ) // check if click lies within x coordinates of choice
		{
			if ( y > 182 && y < 182 + 33 ) // check if click also lies within y coordinates of choice
			{
				GAME_ENGINE->MessageBox(_T("Clicked."));
			}
		}
	}
	*/
}


void Cell::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{
	// Insert the code that needs to be executed when the game registers a mouse wheel action
}

void Cell::MouseMove(int x, int y, WPARAM wParam)
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

void Cell::CheckKeyboard()
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

void Cell::KeyPressed(TCHAR cKey)
{
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

void Cell::Paint(RECT rect)
{
	GAME_ENGINE->SetColor(m_Color);
	GAME_ENGINE->FillRect(m_Position.x, m_Position.y, m_Size, m_Size);
}

void Cell::Tick()
{
	
}

void Cell::CallAction(Caller* callerPtr)
{
	// Insert the code that needs to be executed when a Caller has to perform an action
}








