#include "Map.h"	
#include <numeric>

#include "../../Mappings/ColorMapper/ColorMapper.h"


Map::Map(int size, int maxFeatures /* = 100 */, int chanceRoom /* = 100 */, int chanceCorridor /* = 0 */) :
	m_Size(size),
	m_NumberOfDisplayedCells(0),
	m_CellsPerTick(1),
	m_IsPaintingPaused(false),
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
}

void Map::ColorizeCell(Cell* cell, Tile tile) const
{
	std::string colorName = TileMapper::GetColorName(tile);

	cell->SetColor(colorName);
}


void Map::ColorizeMap() const 
{
	std::vector<DungeonCell> tiles = m_DungeonMap.GetCells();

	const auto compareCells = [](const DungeonCell& a, const DungeonCell& b)
	{
		if (a.orderIndex == -1) { return false; }

		if (b.orderIndex == -1) { return true; }

		return a.orderIndex < b.orderIndex;
	};

	std::sort(tiles.begin(), tiles.end(), compareCells);

	for (int i = 0; i < m_NumberOfDisplayedCells; i++)
	{
		const auto& tile = tiles[i].data.second;
		const auto& mapIndex = tiles[i].data.first;

		ColorizeCell(m_Cells[mapIndex], tile);
	}
}

void Map::End() {}

void Map::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{

	if (isLeft && isDown)
	{
		m_DungeonGenerator = DungeonGenerator(m_Size, m_Size, m_MaxFeatures, m_ChanceRoom, m_ChanceCorridor);
		m_DungeonMap = m_DungeonGenerator.Generate();

		m_NumberOfDisplayedCells = 0;

		ClearMap();
	}
}


void Map::MouseWheelAction(int x, int y, int distance, WPARAM wParam) {}

void Map::MouseMove(int x, int y, WPARAM wParam) {}

void Map::CheckKeyboard() {}

void Map::KeyPressed(TCHAR cKey)
{
	const auto resetKey = _T('R');
	const auto pauseKey = _T('P');
	const auto arrowLeftKey = VK_LEFT;
	const auto arrowRightKey = VK_RIGHT;

	switch (cKey)
	{
	case resetKey:
	{
		ClearMap();

		m_NumberOfDisplayedCells = 0;

		break;
	}
	case pauseKey:
	{
		m_IsPaintingPaused = ~m_IsPaintingPaused;

		break;
	}
	case arrowLeftKey:
	{
		if (m_NumberOfDisplayedCells > 0 && m_IsPaintingPaused)
		{
			m_NumberOfDisplayedCells -= m_CellsPerTick;

			if (m_NumberOfDisplayedCells < 0) m_NumberOfDisplayedCells = 0;

			ClearMap();
			ColorizeMap();
		}

		break;
	}
	case arrowRightKey:
	{
		const int mapSize = m_Cells.size() * m_Cells.size();

		if (m_NumberOfDisplayedCells < mapSize && m_IsPaintingPaused)
		{
			m_NumberOfDisplayedCells += m_CellsPerTick;

			if (m_NumberOfDisplayedCells > mapSize) m_NumberOfDisplayedCells = mapSize;

			ColorizeMap();
		}

		break;
	}
	case VK_UP:
	{
		const int mapSize = m_Cells.size() * m_Cells.size();

		if (m_CellsPerTick < mapSize)
		{
			++m_CellsPerTick;
		}

		break;
	}
	case VK_DOWN:
	{

		if (m_CellsPerTick > 1)
		{
			--m_CellsPerTick;
		}

		break;
	}
	}
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
	const int mapSize = m_Cells.size() * m_Cells.size();

	if (m_NumberOfDisplayedCells < mapSize && !m_IsPaintingPaused)
	{
		m_NumberOfDisplayedCells += m_CellsPerTick;

		if (m_NumberOfDisplayedCells > mapSize) m_NumberOfDisplayedCells = mapSize;

		ColorizeMap();
	}
}


void Map::CallAction(Caller* callerPtr) {}