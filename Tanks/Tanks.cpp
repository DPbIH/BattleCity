// Tanks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tank.h"
#include "Obstacle.h"
#include "Scene.h"
#include "GraphicObjectsFactory.h"
#include "KeyboardEventsListener.h"
#include "KeyboardEventsHandler.h"

int _tmain(int argc, _TCHAR* argv[])
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

	KeyboardEventsListener::Ptr listener( new KeyboardEventsListener() );
	KeyboardEventsHandler::Ptr controller( new KeyboardEventsHandler( listener ) );
	controller->SetTank(tank.get());
	listener->Start();
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

	return 0;
}

