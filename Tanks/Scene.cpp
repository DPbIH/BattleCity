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
	size_t left(0), bottom(0), distanceExcess(0);
	size_t right           = width_;
	size_t top             = height_;
	size_t minimumDistance    = 10;

	Coordinates followedObjectCoord = LevelMapCoordToSceneCoord( followedObj_->GetCoordinates() );

	size_t distanceFromLeft   = followedObjectCoord.X - left;
	size_t distanceFromRight  = right - followedObjectCoord.X;
	size_t distanceFromBottom = followedObjectCoord.Y - bottom;
	size_t distanceFromTop    = top - followedObjectCoord.Y;

	if( distanceFromLeft < minimumDistance )
	{
		distanceExcess = minimumDistance - distanceFromLeft;

		if( levelMapLeftBottom_.X >= distanceExcess )
		{
			levelMapLeftBottom_.X -= distanceExcess;
		}
	}

	if( distanceFromRight < minimumDistance )
	{
		distanceExcess = minimumDistance - distanceFromRight;
		levelMapLeftBottom_.X += distanceExcess;
	}

	if( distanceFromTop < minimumDistance )
	{
		distanceExcess = minimumDistance - distanceFromTop;
		levelMapLeftBottom_.Y += distanceExcess;
	}

	if( distanceFromBottom < minimumDistance )
	{
		distanceExcess = minimumDistance - distanceFromBottom;

		if( levelMapLeftBottom_.Y >= distanceExcess )
		{
			levelMapLeftBottom_.Y -= distanceExcess;
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