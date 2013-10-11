#include "stdafx.h"
#include "Scene.h"
#include "Tank.h"
#include "Bullet.h"
#include "Terrain.h"
#include "Mine.h"
#include "DoubleBuffer.h"
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
	RENDER(bullet, 42, FOREGROUND_BLUE| FOREGROUND_RED );
}

void SceneRenderer::Render( const Terrain* terrain )
{
	WORD color;
	size_t ch;

	switch(terrain->Type())
	{
	case Terrain::Ice:
		color = FOREGROUND_BLUE;
		ch = 176;
		break;

	case Terrain::Rock:
		color = 0;
		ch = 219;
		break;

	case Terrain::Grass:
		color = FOREGROUND_GREEN;
		ch = 5;
		break;
	}

	RENDER(terrain, ch, color );
}

void SceneRenderer::Render( const Mine* mine )
{
	RENDER(mine, 15, FOREGROUND_RED );
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

	std::string str;
	str.push_back( ch );

	Console().Write( str, coord, color | FOREGROUND_INTENSITY, DoubleConsoleBuffer::BackgroundBuffer );
}
