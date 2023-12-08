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
	MakePath();
}

char Map::GetRandomDirection(int x, int y, int gridSize) 
{
	double centerX = gridSize / 2.0;
	double centerY = gridSize / 2.0;
	double distance = std::sqrt(std::pow(x - centerX, 2) + std::pow(y - centerY, 2));

	double weights[4];
	double sigma = std::pow(gridSize / 3.0, 2);
	for (int i = 0; i < 4; ++i) 
	{
		weights[i] = std::exp(-std::pow(distance, 2) / (2 * sigma));
	}

	double totalWeight = std::accumulate(std::begin(weights), std::end(weights), 0.0);

	std::for_each(std::begin(weights), std::end(weights), [totalWeight](double& weight) 
		{
		weight /= totalWeight;
		});

	double randomValue = static_cast<double>(std::rand()) / RAND_MAX;

	double cumulativeWeight = 0.0;
	for (int i = 0; i < 4; ++i) {
		cumulativeWeight += weights[i];
		if (randomValue < cumulativeWeight) 
		{
			return "UDLR"[i];
		}
	}

	return 'R'; // Fallback, though it should never reach here
}

void Map::MakePath() 
{
	const int gridSize = m_Size;

	int x = std::rand() % gridSize + 1;
	int y = std::rand() % gridSize + 1;

	const int numSteps = 700;

	std::cout << "Initial position: (" << x << ", " << y << ")\n";

	for (int step = 0; step < numSteps; ++step) 
	{
		char direction = GetRandomDirection(x, y, m_Size);

		switch (direction) {
		case 'U': --y; break;
		case 'D': ++y; break;
		case 'L': --x; break;
		case 'R': ++x; break;
		}

		x = std::clamp(x, 0, gridSize - 1);
		y = std::clamp(y, 0, gridSize - 1);

		int currentPos = y * m_Size + x;

		// Assuming m_Cells is a vector of cell objects
		 m_Cells[currentPos]->SetColor(0x00FFFFFF);
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

void Map::Tick()
{

//	MakePath();

}

void Map::CallAction(Caller* callerPtr)
{
	// Insert the code that needs to be executed when a Caller has to perform an action
}









