#include "stdafx.h"
#include "Scene.h"
#include "Tank.h"
#include "Bullet.h"
#include "Obstacle.h"
#include "SceneRenderer.h"

#define RENDER(obj, ch, color)								\
	Coordinates renderPos = GetRenderPositionForObject( (obj) );		\
	Print( renderPos, (ch), (color) );						\

SceneRenderer::SceneRenderer( Scene* scene )
	: scene_(scene)
{
}

void SceneRenderer::Render( const Tank* tank )
{
	RENDER(tank, 2, FOREGROUND_GREEN );
}

void SceneRenderer::Render( const Bullet* bullet )
{
	RENDER(bullet, 15, FOREGROUND_RED );
}

void SceneRenderer::Render( const Obstacle* obstacle )
{
	RENDER(obstacle, 178, FOREGROUND_BLUE );
}

Coordinates SceneRenderer::GetRenderPositionForObject( const GraphicObjectBase* obj )
{
	return scene_->LevelMapCoordToWndCoord( obj->GetCoordinates() );
}

void SceneRenderer::Print( const Coordinates& pos, char ch, WORD color )
{
	COORD coord;
	coord.X = pos.X;
	coord.Y = pos.Y;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if( SetConsoleCursorPosition(hConsole, coord) )
	{
		SetConsoleTextAttribute(hConsole, color | FOREGROUND_INTENSITY);
		printf ("%c", ch);
	}
}
