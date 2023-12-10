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
	m_Size(size) {}

Map::~Map()
{
	for (const auto& cell : m_Cells)
	{
		delete cell;
	}
}


void Map::Initialize(HINSTANCE hInstance)
{
	const int width = GAME_ENGINE->GetWidth() / m_Size;

	for (int row = 0; row < m_Size; row++)
	{
		for (int coll = 0; coll < m_Size; coll++)
		{
			Cell* cell = new Cell({ coll * width, row * width }, COLORREF(0x0000FF00), width);
			m_Cells.push_back(cell);
		}
	}
}

void Map::Start()
{
	const int maxFeatures = 50;
	const int chanceRooms = 100;
	const int chanceCorridor = 0;

	DungeonGenerator generator = DungeonGenerator(m_Size, m_Size, maxFeatures, chanceRooms, chanceCorridor);

	m_DungeonMap = generator.Generate();

	ColorizeMap();
}

void Map::ColorizeCell(Cell* cell, Tile tile) const
{
	std::string colorName = TileMapper::getColorName(tile);

	cell->SetColor(colorName);
}


void Map::ColorizeMap()
{
	std::vector<Tile> tiles = m_DungeonMap.GetCells();

	for (int i = 0; i < m_Cells.size(); i++) { ColorizeCell(m_Cells[i], tiles[i]); }
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