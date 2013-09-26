#include "stdafx.h"
#include "MenuCommandsFactory.h"
#include "GameMenuState.h"

GameMenuState::GameMenuState( Game* game )
	: GameState(game)
{
}

void GameMenuState::Start()
{
	system("CLS");
	std::cout << "MENU";
}

void GameMenuState::Stop()
{
}

void GameMenuState::Pause()
{
}

void GameMenuState::Resume()
{
}

GameScreen::Ptr GameMenuState::Screen()
{
	return screen_;
}

GameCommandsFactory::Ptr GameMenuState::CommandsFactory()
{
	return GameCommandsFactory::Ptr( new MenuCommandsFactory(game_) );
}