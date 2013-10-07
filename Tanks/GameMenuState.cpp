#include "stdafx.h"
#include "MenuCommandsFactory.h"
#include "Game.h"
#include "GameMenuState.h"

GameMenuState::GameMenuState( Game* game )
	: GameState(game)
{
}

void GameMenuState::Update()
{
	if( ! game_->paused_ )
	{
		game_->ChangeState( game_->GetState( Gameplay ) );
		return;
	}

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