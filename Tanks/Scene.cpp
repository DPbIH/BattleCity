#include "stdafx.h"
#include <conio.h>
#include "SceneRenderer.h"
#include "DrawVisitor.h"
#include "SceneObjectsVisitor.h"
#include "GraphicObjectsRegistry.h"
#include "DoubleBuffer.h"
#include "Scene.h"

const size_t FrameWidth = 1;

Scene::Scene()
	: height_(0)
	, width_(0)
{
	InitDrawer();
}

void Scene::SetFollowedObject( const GraphicObjectBase::Ptr& obj )
{
	assert( obj );

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
	Console().CleanupBuffer(DoubleConsoleBuffer::BackgroundBuffer);
	DrawBattlefield();
	DrawBorders();
	Console().FlipBuffers();
}

void Scene::DrawBorders()
{
	COORD coord;

	for( size_t x = wndLeftBottom_.X; x <= wndLeftBottom_.X + width_; ++x )
	{
		coord.X = x;

		coord.Y = wndLeftBottom_.Y;
		Console().Write( "x", coord, FOREGROUND_GREEN, DoubleConsoleBuffer::BackgroundBuffer );

		coord.Y = wndLeftBottom_.Y - height_;
		Console().Write( "x", coord, FOREGROUND_GREEN, DoubleConsoleBuffer::BackgroundBuffer );
	}

	for( size_t y = wndLeftBottom_.Y; ( y >= wndLeftBottom_.Y - height_ ) && y; --y )
	{
		coord.Y = y;

		coord.X = wndLeftBottom_.X;
		Console().Write( "x", coord, FOREGROUND_GREEN, DoubleConsoleBuffer::BackgroundBuffer );

		coord.X = wndLeftBottom_.X + width_;
		Console().Write( "x", coord, FOREGROUND_GREEN, DoubleConsoleBuffer::BackgroundBuffer );
	}
}

void Scene::InitDrawer()
{
	renderer_.reset( new SceneRenderer(this) );
	drawer_.reset( new DrawVisitor(renderer_.get() ) );
	sceneDrawer_.reset( new SceneObjectsVisitor( this, drawer_.get() ) );
}

void Scene::DrawBattlefield()
{
	AlignLevelMapPinPoint();
	GORegistry().Accept( *sceneDrawer_ );
}

void Scene::AlignLevelMapPinPoint()
{
	if( ! followedObj_ )
	{
		return;
	}

	Coordinates followedCoord = LevelMapCoordToSceneCoord( followedObj_->GetCoordinates() );

	size_t excess       = 0;
	size_t minIndent    = (width_ <= height_) ? width_/4 : height_/4;
	size_t leftIndent   = followedCoord.X;
	size_t rightIndent  = width_ - followedCoord.X;
	size_t bottomIndent = followedCoord.Y;
	size_t topIndent    = height_ - followedCoord.Y;

	// Align left
	if( leftIndent < minIndent )
	{
		excess = minIndent - leftIndent;

		if( levelMapLeftBottom_.X >= excess )
		{
			levelMapLeftBottom_.X -= excess;
		}
	}

	// Align right
	if( rightIndent < minIndent )
	{
		excess = minIndent - rightIndent;
		levelMapLeftBottom_.X += excess;
	}

	// Align top
	if( topIndent < minIndent )
	{
		excess = minIndent - topIndent;
		levelMapLeftBottom_.Y += excess;
	}

	// Align bottom
	if( bottomIndent < minIndent )
	{
		excess = minIndent - bottomIndent;

		if( levelMapLeftBottom_.Y >= excess )
		{
			levelMapLeftBottom_.Y -= excess;
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