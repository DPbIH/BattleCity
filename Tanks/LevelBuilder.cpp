#include "stdafx.h"
#include "Obstacle.h"
#include "Tank.h"
#include "LevelBuilder.h"

LevelBuilder::LevelBuilder( const GraphicObjectsFactory::Ptr& factory )
	: factory_(factory)
{
	assert( factory_ );
}

void LevelBuilder::BuildLevel()
{
	level_.reset( new Level );
}

void LevelBuilder::BuildObstacle( const Coordinates& coord )
{
	Obstacle::Ptr newObstacle = factory_->CreateObstacle();
	newObstacle->SetCoordinates(coord);
	level_->AddObstacle( newObstacle );
}

void LevelBuilder::BuildEnemy( const Coordinates& coord )
{
	// Add random enemy { Tank, Heli, Marine etc }
	Tank::Ptr newTank = factory_->CreateTank();
	newTank->SetCoordinates(coord);
	level_->AddEnemy( newTank );
}

void LevelBuilder::BuildPlayer( const Coordinates& coord )
{
	Player::Ptr player( new Player );
	Tank::Ptr newTank = factory_->CreateTank();
	newTank->SetCoordinates(coord);
	player->UseVehicle(newTank);
	level_->AddPlayer( player );
}

Level::Ptr LevelBuilder::GetLevel()
{
	return level_;
}