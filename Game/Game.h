#pragma once

#include "../Resource.h"	

#include "GameClasses/Map/Map.h"
#include "GameClasses/Cell/Cell.h"
#include "../Game/GameEngine/GameEngine.h"	
#include "../Game/AbstractGame/AbstractGame.h"

class Cell;
class Map;

class Game : public AbstractGame, public Callable
{
public:

	Game();

	virtual ~Game() override;

	Game(const Game& other) = delete;
	Game(Game&& other) noexcept = delete;
	Game& operator=(const Game& other) = delete;
	Game& operator=(Game&& other) noexcept = delete;

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

private:

	int m_Size;
	COLORREF m_Color;
	POINT m_Position;
	int m_MaxTunnels;
	int m_MaxLength;

	int m_ScreenSize;


	Map* m_pMap;
};
