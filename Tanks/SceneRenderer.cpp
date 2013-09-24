#include "stdafx.h"
#include "Scene.h"
#include "Tank.h"
#include "Bullet.h"
#include "Obstacle.h"
#include "SceneRenderer.h"

#define RENDER(obj, ch, color)								\
	size_t posX, posY;										\
	GetRenderPositionForObject( (obj), posX, posY );		\
	Print( posX, posY, (ch), (color) );						\

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

void SceneRenderer::GetRenderPositionForObject( const GraphicObjectBase* obj, size_t& posX, size_t& posY )
{
	scene_->LevelMapCoordinatesToWndCoordinates( obj->GetX(), obj->GetY(), posX, posY );
}

void SceneRenderer::Print( size_t posX, size_t posY, char ch, WORD color )
{
	COORD coord;
	coord.X = posX;
	coord.Y = posY;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if( SetConsoleCursorPosition(hConsole, coord) )
	{
		SetConsoleTextAttribute(hConsole, color | FOREGROUND_INTENSITY);
		printf ("%c", ch);
	}
}
