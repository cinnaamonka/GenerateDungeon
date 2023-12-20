#pragma once

#include "../../Mappings/ColorMapper/ColorMapper.h"
#include "../../GameEngine/GameEngine.h"
#include "../../AbstractGame/AbstractGame.h"

#include "../../../Resource.h"	

class Cell : public AbstractGame, public Callable
{
public:

	Cell(POINT pos, COLORREF color, int size);

	virtual ~Cell() override;

	Cell(const Cell& other) = delete;
	Cell(Cell&& other) noexcept = delete;
	Cell& operator=(const Cell& other) = delete;
	Cell& operator=(Cell&& other) noexcept = delete;

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
	void SetColor(const std::string& colorName) { m_Color = ColorMapper::GetColor(colorName); }

private:

	int m_Size;

	COLORREF m_Color;
	POINT m_Position;
};
