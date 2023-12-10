//-----------------------------------------------------------------
// Main Game  File
// C++ Header - X.h - version v7_02			
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "../../Resource.h"	
#include "../TileMapper/TileMapper.h"
#include "../../Game/GameEngine/GameEngine.h"	
#include "../../Game/AbstractGame/AbstractGame.h"
#include "../../lib/DungeonBuilder/DungeonGenerator/DungeonGenerator.h"
#include "../Cell/Cell.h"

//-----------------------------------------------------------------
// X Class																
//-----------------------------------------------------------------
class Map : public AbstractGame, public Callable
{
public:
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	Map(int size);

	virtual ~Map() override;

	//---------------------------
	// Disabling copy/move constructors and assignment operators   
	//---------------------------
	Map(const Map& other) = delete;
	Map(Map&& other) noexcept = delete;
	Map& operator=(const Map& other) = delete;
	Map& operator=(Map&& other) noexcept = delete;

	//---------------------------
	// General Methods
	//---------------------------
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
	void ColorizeMap();

	void ColorizeCell(Cell* cell, Tile tile) const;
private:
	// -------------------------
	// Datamembers
	// -------------------------

	int m_Size;
	DungeonMap m_DungeonMap;
	std::vector<Cell*> m_Cells;
};
