#pragma once

#include "../Cell/Cell.h"

#include "../../Mappings/TileMapper/TileMapper.h"
#include "../../GameEngine/GameEngine.h"	
#include "../../AbstractGame/AbstractGame.h"

#include "../../../Resource.h"	
#include "../../../lib/DungeonBuilder/DungeonGenerator/DungeonGenerator.h"


class Map : public AbstractGame, public Callable
{
public:
	Map(int size, int maxFeatures = 100, int chanceRooms = 100, int chanceCorridor = 0);

	virtual ~Map() override;

	Map(const Map& other) = delete;
	Map(Map&& other) noexcept = delete;
	Map& operator=(const Map& other) = delete;
	Map& operator=(Map&& other) noexcept = delete;

	void Initialize(HINSTANCE hInstance) override;
	void Start() override;
	void End() override;
	void Paint(RECT rect) override;

	void Tick() override;
	void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam) override;
	void MouseWheelAction(int x, int y, int distance, WPARAM wParam) override;
	void MouseMove(int x, int y, WPARAM wParam) override;
	void CheckKeyboard() override;
	void KeyPressed(TCHAR cKey) override;
	void CallAction(Caller* callerPtr) override;

	void ColorizeMap() const;
	void ColorizeCell(Cell* cell, Tile tile) const;

	void ClearMap();

	void SetMaxChanceRoom(int maxChanceRoom)
	{
		m_ChanceRoom = maxChanceRoom;
	}
	void SetMaxChanceFeature(int maxFeatures)
	{
		m_MaxFeatures = maxFeatures;
	}
	void SetMaxChanceCorridor(int maxChanceCorridor)
	{
		m_ChanceCorridor = maxChanceCorridor;
	}
	void StartDungeonGeneration()
	{
		m_IsPaintingPaused = false;

		m_DungeonGenerator = DungeonGenerator(m_Size, m_Size, m_MaxFeatures, m_ChanceRoom, m_ChanceCorridor);
		m_DungeonMap = m_DungeonGenerator.Generate();

		m_NumberOfDisplayedCells = 0;

		ClearMap();
	}
private:

	int m_Size;

	int m_NumberOfDisplayedCells;
	int m_CellsPerTick;

	bool m_IsPaintingPaused;

	int m_MaxFeatures;
	int m_ChanceRoom;
	int m_ChanceCorridor;

	DungeonGenerator m_DungeonGenerator;
	DungeonMap m_DungeonMap;

	std::vector<Cell*> m_Cells;

};