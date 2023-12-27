#include <iostream>
#include <cstdlib> 
#include <ctime>   

#include "Game.h"

class NegativeNumberException : public std::exception 
{
public:
	const char* what() const noexcept override
	{
		return "Negative number not allowed.";
	}
};

class NotANumberException : public std::exception 
{
public:
	const char* what() const noexcept override 
	{
		return "Input is not a valid number.";
	}
};
class BiggerThan100 : public std::exception 
{
public:
	const char* what() const noexcept override 
	{
		return "Chance is higher than 100";
	}
};

Game::Game() :m_ScreenSize{ 900 }
{
	m_pMap = new Map(100);
}

Game::~Game() {}


void Game::Initialize(HINSTANCE hInstance)
{
	AbstractGame::Initialize(hInstance);

	GAME_ENGINE->SetTitle(_T("Game Engine version 7_02"));
	GAME_ENGINE->RunGameLoop(true);

	GAME_ENGINE->SetWidth(m_ScreenSize);
	GAME_ENGINE->SetHeight(m_ScreenSize);
	GAME_ENGINE->SetFrameRate(50);

	tstringstream buffer;

	buffer << _T("PR");

	buffer << (TCHAR)VK_LEFT;
	buffer << (TCHAR)VK_RIGHT;
	buffer << (TCHAR)VK_UP;
	buffer << (TCHAR)VK_DOWN;

	GAME_ENGINE->SetKeyList(buffer.str());

	m_pMap->Initialize(hInstance);
}

void Game::Start()
{
	m_pMap->Start();

	m_pFeaturesTextBox = new TextBox();
	m_pFeaturesTextBox->SetBounds(25, 25, 100, 25);
	m_pFeaturesTextBox->AddActionListener(this);
	m_pFeaturesTextBox->Show();

	m_pFont = new Font(_T("Verdana"), true, false, false, 32);

	m_pChanceRoomTextBox = new TextBox();
	m_pChanceRoomTextBox->SetBounds(25, 75, 100, 25);
	m_pChanceRoomTextBox->AddActionListener(this);
	m_pChanceRoomTextBox->Show();

	m_pButton = new Button();
	m_pButton->SetBounds(25, 160, 200, 40);
	m_pButton->SetText(L"Generate Dungeon");
	m_pButton->AddActionListener(this);
	m_pButton->Show();
}

void Game::End() 
{
	delete m_pChanceRoomTextBox;
	delete m_pFeaturesTextBox;
	delete m_pFont;
	delete m_pButton;
}

void Game::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{
	m_pMap->MouseButtonAction(isLeft, isDown, x, y, wParam);
}

void Game::MouseWheelAction(int x, int y, int distance, WPARAM wParam) {}

void Game::MouseMove(int x, int y, WPARAM wParam) {}

void Game::CheckKeyboard() {}

void Game::KeyPressed(TCHAR cKey)
{
	m_pMap->KeyPressed(cKey);
}

void Game::Paint(RECT rect)
{
	m_pMap->Paint(rect);

	GAME_ENGINE->SetFont(m_pFont);
	GAME_ENGINE->SetColor(RGB(27, 27, 27));

	GAME_ENGINE->DrawString(_T("Max features"), 130, 20);
	GAME_ENGINE->DrawString(_T("Corridor chance"), 130, 120);
	GAME_ENGINE->DrawString(_T("Room chance"), 130, 70);
	GAME_ENGINE->DrawString(_T("Pause - P"), 550, 30);
	GAME_ENGINE->DrawString(_T("Faster - up arrow"), 550, 60);
	GAME_ENGINE->DrawString(_T("Slower - down arrow"), 550, 90);
	GAME_ENGINE->DrawString(_T("Next step - right arrow"), 550, 120);
	GAME_ENGINE->DrawString(_T("Prior step - left arrow"), 550, 150);
	GAME_ENGINE->DrawString(m_ChanceCorridors, 75, 120);
}

void Game::Tick()
{
	const int ticks = 1;

	for (int i = 0; i < ticks; ++i)
	{
		m_pMap->Tick();
	}
}


void Game::CallAction(Caller* callerPtr) 
{
	if (callerPtr == m_pButton)
	{
		try
		{
			std::wstring wsRoom(m_pChanceRoomTextBox->GetText());
			std::wstring wsFeature(m_pFeaturesTextBox->GetText());

			int maxChanceRoom = 0;
			int maxFeatures = 0;

			
			if (wsFeature == _T(""))
			{
				maxFeatures = 100;
				m_pMap->SetMaxChanceFeature(maxFeatures);
			}
			else
			{
				if (std::stoi(wsFeature) < 0)
				{
					throw NegativeNumberException();
				}
				m_pMap->SetMaxChanceFeature(std::stoi(wsFeature));
			}
			
			if (wsRoom == _T(""))
			{
				maxChanceRoom = 100;
				m_pMap->SetMaxChanceRoom(maxChanceRoom);
			}
			else
			{
				if (std::stoi(wsRoom) > 100)
				{
					throw BiggerThan100();
				}
				if (std::stoi(wsRoom) < 0)
				{
					throw NegativeNumberException();
				}
				m_ChanceCorridors = std::to_wstring(100 - std::stoi(wsRoom));

				m_pMap->SetMaxChanceRoom(std::stoi(wsRoom));
				m_pMap->SetMaxChanceCorridor(100 - std::stoi(wsRoom));
			}
			m_pMap->StartDungeonGeneration();

		}
		
		catch (const std::invalid_argument& e) 
		{
			// This is for NotANumberException
			m_pFeaturesTextBox->SetText(_T(""));
			m_pChanceRoomTextBox->SetText(_T(""));

			GAME_ENGINE->MessageBox(_T("Argument is not valid"));
		}
		catch (const std::out_of_range& e)
		{

			m_pFeaturesTextBox->SetText(_T(""));
			m_pChanceRoomTextBox->SetText(_T(""));
			GAME_ENGINE->MessageBox(_T("The input is not a number"));
		}
		catch (const BiggerThan100& e)
		{
			// This is for NotANumberException

			std::wstringstream wss;
			wss << e.what();
			std::wstring notANumberExceptionWString = wss.str();

			m_pFeaturesTextBox->SetText(_T(""));
			m_pChanceRoomTextBox->SetText(_T(""));
			GAME_ENGINE->MessageBox(notANumberExceptionWString);
		}
		catch (const NegativeNumberException& e) 
		{
			std::wstringstream wss;
			wss << e.what();
			std::wstring notANumberExceptionWString = wss.str();

			m_pFeaturesTextBox->SetText(_T(""));
			m_pChanceRoomTextBox->SetText(_T(""));
			GAME_ENGINE->MessageBox(notANumberExceptionWString);
		}
		catch (const NotANumberException& e) 
		{
			std::wstringstream wss;
			wss << e.what();
			std::wstring notANumberExceptionWString = wss.str();

			m_pFeaturesTextBox->SetText(_T(""));
			m_pChanceRoomTextBox->SetText(_T(""));
			GAME_ENGINE->MessageBox(notANumberExceptionWString);
		}
		catch (...)
		{
			GAME_ENGINE->MessageBox(_T("Invalid argument."));
		}
		
		
	}
}