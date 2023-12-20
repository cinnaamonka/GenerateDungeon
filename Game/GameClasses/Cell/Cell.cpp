#include "Cell.h"			

Cell::Cell(POINT pos, COLORREF color, int size) :m_Size(size), m_Color(color), m_Position(pos) {}

Cell::~Cell() {}

void Cell::Initialize(HINSTANCE hInstance) {}

void Cell::Start() {}

void Cell::End() {}

void Cell::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam) {}

void Cell::MouseWheelAction(int x, int y, int distance, WPARAM wParam) {}

void Cell::MouseMove(int x, int y, WPARAM wParam) {}

void Cell::CheckKeyboard() {}

void Cell::KeyPressed(TCHAR cKey) {}

void Cell::Paint(RECT rect)
{
	GAME_ENGINE->SetColor(m_Color);
	GAME_ENGINE->FillRect(m_Position.x, m_Position.y, m_Size, m_Size);
}

void Cell::Tick() {}

void Cell::CallAction(Caller* callerPtr) {}