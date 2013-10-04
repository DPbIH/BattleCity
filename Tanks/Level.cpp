#include "stdafx.h"
#include "GraphicObjectsRegistry.h"
#include "Level.h"

Level::Level()
{
	InitScene();
}

void Level::InitScene()
{
	scene.PinToLevelMap( Coordinates(10, 10) );
	scene.PinToWindow( Coordinates(30, 30) );
	scene.SetSize(20, 50);
}

void Level::AddPlayer( const Player::Ptr& player )
{
	player_ = player;
	AddImpl( player_->Vehicle() );
	scene.SetFollowedObject( player_->Vehicle() );
}

void Level::AddEnemy( const Tank::Ptr& enemy )
{
	AddImpl( enemy );
}

void Level::AddObstacle( const Obstacle::Ptr& obstacle )
{
	AddImpl( obstacle );
}

void Level::AddImpl( const GraphicObjectBase::Ptr& go )
{
	GORegistry().Add( go->UID(), go );
}

void Level::RenderScene()
{
	scene.Draw();
}