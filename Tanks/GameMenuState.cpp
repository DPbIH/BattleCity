#include "stdafx.h"
#include "MenuCommandsFactory.h"
#include "Game.h"
#include "DoubleBuffer.h"
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

	Console().CleanupBuffer();
	COORD coord = {30,30};
	Console().Write( "MENU", coord, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
}

//GameScreen::Ptr GameMenuState::Screen()
//{
//	return screen_;
//}

GameCommandsFactory::Ptr GameMenuState::CommandsFactory()
{
	return GameCommandsFactory::Ptr( new MenuCommandsFactory(game_) );
}