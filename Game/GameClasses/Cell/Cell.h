//-----------------------------------------------------------------
// Main Game  File
// C++ Header - X.h - version v7_02			
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "../../Resource.h"	

#include "../../Mappings/ColorMapper/ColorMapper.h"
#include "../../Game/GameEngine/GameEngine.h"	
#include "../../Game/AbstractGame/AbstractGame.h"

//-----------------------------------------------------------------
// X Class																
//-----------------------------------------------------------------
class Cell : public AbstractGame, public Callable
{
public:
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	Cell(POINT pos, COLORREF color, int size);

	virtual ~Cell() override;

	//---------------------------
	// Disabling copy/move constructors and assignment operators   
	//---------------------------
	Cell(const Cell& other) = delete;
	Cell(Cell&& other) noexcept = delete;
	Cell& operator=(const Cell& other) = delete;
	Cell& operator=(Cell&& other) noexcept = delete;

	//---------------------------
	// General Methods
	//---------------------------
	void Initialize(HINSTANCE hInstance) override;
	void Start() override;
	void End() override;
	void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam) override;
	void MouseWheelAction(int x, int y, int distance, WPARAM wParam) override;
	void MouseMove(int x, int y, WPARAM wParam) override;
	void CheckKeyboard() override;
	void KeyPressed(TCHAR cKey) override;
	void Paint(RECT rect) override;
	void Tick() override;

	void CallAction(Caller* callerPtr) override;
	void SetColor(const std::string& colorName) { m_Color = ColorMapper::getColor(colorName); }

private:
	// -------------------------
	// Datamembers
	// -------------------------

	int m_Size;

	COLORREF m_Color;
	POINT m_Position;
};
