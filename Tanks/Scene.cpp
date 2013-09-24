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

void Scene::PinToLevelMap( const Coordinates& levelMapLeftBottom )
{
	levelMapLeftBottom_ = levelMapLeftBottom;
}

void Scene::PinToWindow( const Coordinates& wndLeftBottom )
{
	wndLeftBottom_ = wndLeftBottom;
}

bool Scene::CheckSceneCoversLevelMapCoord( const Coordinates& coord ) const
{
	return ( levelMapLeftBottom_.X <= coord.X ) &&
		( coord.X < levelMapLeftBottom_.X + width_ ) &&
		( levelMapLeftBottom_.Y <= coord.Y ) &&
		( coord.Y < levelMapLeftBottom_.Y + height_ );
}

void Scene::Draw()
{
	system("CLS");

	DrawBorders();
	DrawBattlefield();
}

void Scene::DrawBorders()
{
	/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
	}*/
}

void Scene::DrawBattlefield()
{
	AlignLevelMapPinPoint();

	SceneRenderer renderer(this);
	DrawVisitor drawer( &renderer );
	SceneObjectsVisitor sceneDrawer( this, &drawer );
	GORegistry().Accept( sceneDrawer );
}

void Scene::AlignLevelMapPinPoint()
{
	size_t minLeft(0), minBottom(0);
	size_t maxRight           = width_;
	size_t maxTop             = height_;
	Coordinates followedObjectCoord = LevelMapCoordToSceneCoord( followedObj_->GetCoordinates() );

	size_t deltaLeft   = followedObjectCoord.X - minLeft;
	size_t deltaRight  = maxRight - followedObjectCoord.X;
	size_t deltaBottom = followedObjectCoord.Y - minBottom;
	size_t deltaTop    = maxTop - followedObjectCoord.Y;
	size_t minIndent   = 10;
	size_t overshoot;

	if( deltaLeft < minIndent )
	{
		overshoot = minIndent - deltaLeft;

		if( levelMapLeftBottom_.X >= overshoot )
		{
			levelMapLeftBottom_.X -= overshoot;
		}
	}

	if( deltaRight < minIndent )
	{
		overshoot = minIndent - deltaRight;
		levelMapLeftBottom_.X += overshoot;
	}

	if( deltaTop < minIndent )
	{
		overshoot = minIndent - deltaTop;
		levelMapLeftBottom_.Y += overshoot;
	}

	if( deltaBottom < minIndent )
	{
		overshoot = minIndent - deltaBottom;

		if( levelMapLeftBottom_.Y >= overshoot )
		{
			levelMapLeftBottom_.Y -= overshoot;
		}
	}
}

Coordinates Scene::SceneCoordToWndCoord( const Coordinates& sceneCoord ) const
{
	assert( ( sceneCoord.X < width_ ) && ( sceneCoord.Y < height_ ) );

	Coordinates wndCoord;

	wndCoord.X = wndLeftBottom_.X + sceneCoord.X;
	wndCoord.Y = wndLeftBottom_.Y - sceneCoord.Y;

	return wndCoord;
}

Coordinates Scene::LevelMapCoordToSceneCoord( const Coordinates& levelMapCoord ) const
{
	Coordinates sceneCoord;

	if( CheckSceneCoversLevelMapCoord( levelMapCoord ) )
	{
		sceneCoord.X = levelMapCoord.X - levelMapLeftBottom_.X;
		sceneCoord.Y = levelMapCoord.Y - levelMapLeftBottom_.Y;
	}

	return sceneCoord;
}

Coordinates Scene::LevelMapCoordToWndCoord( const Coordinates& levelMapCoord ) const
{
	Coordinates sceneCoord = LevelMapCoordToSceneCoord( levelMapCoord );
	return SceneCoordToWndCoord( sceneCoord );
}