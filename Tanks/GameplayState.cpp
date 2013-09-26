#include "stdafx.h"
#include "Tank.h"
#include "Obstacle.h"
#include "Scene.h"
#include "GraphicObjectsFactory.h"
#include "GameplayCommandsFactory.h"
#include "GameplayState.h"

GameplayState::GameplayState( Game* game )
	: GameState( game )
{
}

void GameplayState::Start()
{
	GraphicObjectsFactory goFactory;
	Tank::Ptr tank = goFactory.CreateTank();
	tank->SetCoordinates(20, 20);

	Obstacle::Ptr obstacle = goFactory.CreateObstacle();
	obstacle->SetCoordinates(20, 30);
	obstacle = goFactory.CreateObstacle();
	obstacle->SetCoordinates(20, 25);
	obstacle = goFactory.CreateObstacle();
	obstacle->SetCoordinates(20, 26);
	obstacle = goFactory.CreateObstacle();
	obstacle->SetCoordinates(21, 27);
	obstacle = goFactory.CreateObstacle();
	obstacle->SetCoordinates(10, 15);
	obstacle = goFactory.CreateObstacle();
	obstacle->SetCoordinates(15, 15);
	obstacle = goFactory.CreateObstacle();
	obstacle->SetCoordinates(18, 21);
	obstacle = goFactory.CreateObstacle();
	obstacle->SetCoordinates(8, 18);
	obstacle = goFactory.CreateObstacle();
	obstacle->SetCoordinates(18, 8);
	obstacle = goFactory.CreateObstacle();
	obstacle->SetCoordinates(11, 3);

	evtHandler_->SetTank(tank.get());
	Scene scene;
	scene.PinToLevelMap( Coordinates(10, 10) );
	scene.PinToWindow( Coordinates(30, 30) );
	scene.SetSize(20, 50);
	scene.SetFollowedObject(tank);

	while(1)
	{
		scene.Draw();
		Sleep(100);
	}
}

void GameplayState::Stop()
{
}

void GameplayState::Pause()
{
}

void GameplayState::Resume()
{
}

GameScreen::Ptr GameplayState::Screen()
{
	if( ! screen_ )
	{
		//screen_.reset( new GamePlayScreen );
	}

	return screen_;
}

GameCommandsFactory::Ptr GameplayState::CommandsFactory()
{
	return GameCommandsFactory::Ptr( new GameplayCommandsFactory( game_ ) );
}