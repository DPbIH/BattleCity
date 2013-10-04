#include "stdafx.h"
#include "Tank.h"
#include "Obstacle.h"
#include "Scene.h"
#include "GraphicObjectsFactory.h"
#include "GameplayCommandsFactory.h"
#include "Game.h"
#include "GameplayState.h"

GameplayState::GameplayState( Game* game )
	: GameState( game )
{
}

void GameplayState::OnEnterImpl()
{
	if( ! game_->currentLevel_ )
	{
		game_->LoadRandomLevel();
	}
}

void GameplayState::Update()
{
	game_->currentLevel_->RenderScene();
}

//GameScreen::Ptr GameplayState::Screen()
//{
//	if( ! screen_ )
//	{
//		//screen_.reset( new GamePlayScreen );
//	}
//
//	return screen_;
//}

GameCommandsFactory::Ptr GameplayState::CommandsFactory()
{
	return GameCommandsFactory::Ptr( new GameplayCommandsFactory( game_ ) );
}