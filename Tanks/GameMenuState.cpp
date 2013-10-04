#include "stdafx.h"
#include "MenuCommandsFactory.h"
#include "GameMenuState.h"

GameMenuState::GameMenuState( Game* game )
	: GameState(game)
{
}

void GameMenuState::Update()
{
	system("CLS");
	std::cout << "MENU";
}

//GameScreen::Ptr GameMenuState::Screen()
//{
//	return screen_;
//}

GameCommandsFactory::Ptr GameMenuState::CommandsFactory()
{
	return GameCommandsFactory::Ptr( new MenuCommandsFactory(game_) );
}