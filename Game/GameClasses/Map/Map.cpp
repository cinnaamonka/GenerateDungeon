//-----------------------------------------------------------------
// Main Game File
// C++ Source - X.cpp - version v7_02
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Map.h"	
#include <numeric>

//-----------------------------------------------------------------
// X methods																				
//-----------------------------------------------------------------

Map::Map(int size) :
	m_Size(size)
{
	POINT pos = { 200,100 };
	for (int row = 0; row < size; row++)
	{
		for (int coll = 0; coll < size; coll++)
		{
			Cell* cell = new Cell({ pos.x + coll * m_Size / 5 , pos.y + row * m_Size / 5 }, COLORREF(0x0000FF00), m_Size / 5);
			m_Cells.push_back(cell);
		}
	}
}

Map::~Map()
{
	for (const auto& cell : m_Cells)
	{
		delete cell;
	}
}


void Map::Initialize(HINSTANCE hInstance)
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

void Map::Start()
{
	const int maxFeatures = 20;
	const int chanceRooms = 75;
	const int chanceCorridor = 25;

	DungeonGenerator generator = DungeonGenerator(m_Size, m_Size, maxFeatures, chanceRooms, chanceCorridor);

	m_DungeonMap = generator.Generate();

	ColorizeMap();
}


void Map::ColorizeMap()
{
	std::vector<Tile> tiles = m_DungeonMap.GetCells();

	for (int i = 0; i < m_Cells.size(); i++)
	{
		Tile tile = tiles[i];

		COLORREF lightGray = RGB(211, 211, 211);
		COLORREF gray = RGB(128, 128, 128);
		COLORREF darkGray = RGB(85, 85, 85);
		COLORREF darkerGray = RGB(40, 40, 40);

		COLORREF brown = RGB(139, 69, 19);
		COLORREF mediumAquamarine = RGB(102, 205, 170);
		COLORREF mediumSlateBlue = RGB(123, 104, 238);
		COLORREF mediumSpringGreen = RGB(112, 219, 147);
		COLORREF blueViolet = RGB(138, 43, 226);

		switch (tile) {
		case Tile::Unused:
			m_Cells[i]->SetColor(lightGray);
			break;
		case Tile::DirtWall:
			m_Cells[i]->SetColor(darkerGray);
			break;
		case Tile::DirtFloor:
			m_Cells[i]->SetColor(gray);
			break;
		case Tile::Corridor:
			m_Cells[i]->SetColor(darkGray);
			break;
		case Tile::Door:
			m_Cells[i]->SetColor(brown);
			break;
			m_Cells[i]->SetColor(mediumSpringGreen);
			break;
		case Tile::DownStairs:
			m_Cells[i]->SetColor(blueViolet);
			break;
		};
	}
}

void Map::End()
{
	// Insert the code that needs to be executed at the closing of the game
}

void Map::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
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


void Map::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{
	// Insert the code that needs to be executed when the game registers a mouse wheel action
}

void Map::MouseMove(int x, int y, WPARAM wParam)
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

void Map::CheckKeyboard()
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

void Map::KeyPressed(TCHAR cKey)
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

void Map::Paint(RECT rect)
{
	for (const auto& cell : m_Cells)
	{
		cell->Paint(rect);
	}

}

void Map::Tick() {}


void Map::CallAction(Caller* callerPtr) {}