#include "stdafx.h"
#include <conio.h>
#include "SceneRenderer.h"
#include "DrawVisitor.h"
#include "SceneObjectsVisitor.h"
#include "GraphicObjectsRegistry.h"
#include "Scene.h"

Scene::Scene()
	: height_(0)
	, width_(0)
	, wndLeftBottomX_(0)
	, wndLeftBottomY_(0)
	, levelMapLeftBottomX_(0)
	, levelMapLeftBottomY_(0)
{
}

void Scene::SetFollowedObject( const GraphicObjectBase::Ptr& obj )
{
	followedObj_ = obj;
}

void Scene::SetSize( size_t height, size_t width )
{
	height_ = height;
	width_   = width;
}

void Scene::PinToLevelMapCoordinaets( size_t levelMapLeftBottomX, size_t levelMapLeftBottomY )
{
	levelMapLeftBottomX_ = levelMapLeftBottomX;
	levelMapLeftBottomY_ = levelMapLeftBottomY;
}

void Scene::PinToWindowCordinates( size_t wndLeftBottomX, size_t wndLeftBottomY )
{
	wndLeftBottomX_ = wndLeftBottomX;
	wndLeftBottomY_ = wndLeftBottomY;
}

bool Scene::CheckLevelMapCoordinatesAreCovered(
	size_t levelMapX, size_t levelMapY
	) const
{
	return ( levelMapLeftBottomX_ <= levelMapX ) &&
		( levelMapX < levelMapLeftBottomX_ + width_ ) &&
		( levelMapLeftBottomY_ <= levelMapY ) &&
		( levelMapY < levelMapLeftBottomY_ + height_ );
}

void Scene::Draw()
{
	system("CLS");

	DrawBorders();
	DrawBattlefield();
}

void Scene::DrawBorders()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute( hConsole, FOREGROUND_RED );

	COORD coord;

	for( size_t x = wndLeftBottomX_; x <= wndLeftBottomX_ + width_; ++x )
	{
		if (x%2==1)
		{
			continue;
		}

		coord.X = x;

		coord.Y = wndLeftBottomY_;
		SetConsoleCursorPosition(hConsole, coord);
		printf ("x");

		coord.Y = wndLeftBottomY_ - height_;
		SetConsoleCursorPosition(hConsole, coord);
		printf ("x");
	}

	for( size_t y = wndLeftBottomY_; y >= wndLeftBottomY_ - height_ ; --y )
	{
		if (y%2==1)
		{
			continue;
		}

		coord.Y = y;

		coord.X = wndLeftBottomX_;
		SetConsoleCursorPosition(hConsole, coord);
		printf ("x");

		coord.X = wndLeftBottomX_ + width_;
		SetConsoleCursorPosition(hConsole, coord);
		printf ("x");
	}
}

void Scene::DrawBattlefield()
{
	AlignCoveredLevelMapArea();

	SceneRenderer renderer(this);
	DrawVisitor drawer( &renderer );
	SceneObjectsVisitor sceneDrawer( this, &drawer );
	GORegistry().Accept( sceneDrawer );
}

void Scene::AlignCoveredLevelMapArea()
{
	size_t minLeft(0), minBottom(0);
	size_t maxRight           = width_;
	size_t maxTop             = height_;
	size_t currX, currY;
	LevelMapCoordinatesToSceneCoordinates( followedObj_->GetX(), followedObj_->GetY(), currX, currY );

	size_t deltaLeft   = currX - minLeft;
	size_t deltaRight  = maxRight - currX;
	size_t deltaBottom = currY - minBottom;
	size_t deltaTop    = maxTop - currY;
	size_t minIndent   = 10;
	size_t overshoot;

	if( deltaLeft < minIndent )
	{
		overshoot = minIndent - deltaLeft;

		if( levelMapLeftBottomX_ >= overshoot )
		{
			levelMapLeftBottomX_ -= overshoot;
		}
	}

	if( deltaRight < minIndent )
	{
		overshoot = minIndent - deltaRight;
		levelMapLeftBottomX_ += overshoot;
	}

	if( deltaTop < minIndent )
	{
		overshoot = minIndent - deltaTop;
		levelMapLeftBottomY_ += overshoot;
	}

	if( deltaBottom < minIndent )
	{
		overshoot = minIndent - deltaBottom;

		if( levelMapLeftBottomY_ >= overshoot )
		{
			levelMapLeftBottomY_ -= overshoot;
		}
	}
}

void Scene::SceneCoordinatesToWndCoordinates(
	size_t sceneX, size_t sceneY,
	size_t& consoleWndX, size_t& consoleWndY
	) const
{
	assert( ( sceneX < width_ ) && ( sceneY < height_ ) );

	consoleWndX = wndLeftBottomX_ + sceneX;
	consoleWndY = wndLeftBottomY_ - sceneY;
}

void Scene::LevelMapCoordinatesToSceneCoordinates(
	size_t levelMapX, size_t levelMapY,
	size_t& sceneX, size_t& sceneY
	) const
{
	if( ! CheckLevelMapCoordinatesAreCovered( levelMapX, levelMapY ) )
	{
		return;
	}

	sceneX = levelMapX - levelMapLeftBottomX_;
	sceneY = levelMapY - levelMapLeftBottomY_;
}

void Scene::LevelMapCoordinatesToWndCoordinates(
	size_t levelMapX, size_t levelMapY,
	size_t& consoleWndX, size_t& consoleWndY
	) const
{
	size_t sceneX, sceneY;
	LevelMapCoordinatesToSceneCoordinates( levelMapX, levelMapY, sceneX, sceneY );
	SceneCoordinatesToWndCoordinates( sceneX, sceneY, consoleWndX, consoleWndY );
}