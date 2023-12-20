//-----------------------------------------------------------------
// Main Game File
// C++ Source - X.cpp - version v7_02
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Map.h"	
#include <numeric>

#include "../../Mappings/ColorMapper/ColorMapper.h"

//-----------------------------------------------------------------
// X methods																				
//-----------------------------------------------------------------

Map::Map(int size, int maxFeatures /* = 100 */, int chanceRoom /* = 100 */, int chanceCorridor /* = 0 */) :
	m_Size(size),
	m_MaxFeatures(maxFeatures),
	m_ChanceRoom(chanceRoom),
	m_ChanceCorridor(chanceCorridor),
	m_DungeonGenerator{ m_Size, m_Size, m_MaxFeatures, m_ChanceRoom, m_ChanceCorridor }
{}

Map::~Map()
{
	for (const auto& cell : m_Cells)
	{
		delete cell;
	}
}

void Map::ClearMap()
{
	m_Cells.clear();

	const int width = GAME_ENGINE->GetWidth();
	const int roundedWidth = static_cast<int>(std::floor(static_cast<float>(width) / m_Size));

	POINT startPoint =
	{
		(m_Size * roundedWidth - m_Size * (roundedWidth - 1)) / 2,
		(m_Size * roundedWidth - m_Size * (roundedWidth - 1)) / 2
	};


	for (int row = 0; row < m_Size; row++)
	{
		for (int coll = 0; coll < m_Size; coll++)
		{
			POINT position = { startPoint.x + coll * (roundedWidth - 1), startPoint.y + row * (roundedWidth - 1) };

			Cell* cell = new Cell(position, ColorMapper::GetColor("lightGray"), roundedWidth);

			m_Cells.push_back(cell);
		}
	}
}

void Map::Initialize(HINSTANCE hInstance)
{
	ClearMap();
}

void Map::Start()
{
	m_DungeonMap = m_DungeonGenerator.Generate();

	ColorizeMap();
}

void Map::ColorizeCell(Cell* cell, Tile tile) const
{
	std::string colorName = TileMapper::GetColorName(tile);

	cell->SetColor(colorName);
}


void Map::ColorizeMap()
{
	std::vector<DungeonCell> tiles = m_DungeonMap.GetCells();

	auto compareFunction = [](const DungeonCell& a, const DungeonCell& b) {
		return (a.orderIndex == -1) ? false : ((b.orderIndex == -1) ? true : (a.orderIndex < b.orderIndex));
	};

	std::sort(tiles.begin(), tiles.end(), compareFunction);

	for (int i = 0; i < 1; i++)
	{
		const auto& tile = tiles[i].data.second;
		const auto& mapIndex = tiles[i].data.first;

		ColorizeCell(m_Cells[mapIndex], tile);
	}
}

void Map::End()
{
	// Insert the code that needs to be executed at the closing of the game
}

void Map::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{

	if (isLeft && isDown)
	{
		m_DungeonGenerator = DungeonGenerator(m_Size, m_Size, m_MaxFeatures, m_ChanceRoom, m_ChanceCorridor);
		m_DungeonMap = m_DungeonGenerator.Generate();
		ClearMap();

		ColorizeMap();
	}
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
	GAME_ENGINE->SetColor(ColorMapper::GetColor("lightGray"));
	GAME_ENGINE->FillRect(0, 0, GAME_ENGINE->GetWidth(), GAME_ENGINE->GetHeight());

	for (const auto& cell : m_Cells)
	{
		cell->Paint(rect);
	}

}

void Map::Tick() {
}


void Map::CallAction(Caller* callerPtr) {}