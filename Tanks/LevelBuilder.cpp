#include "stdafx.h"
#include "Terrain.h"
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

void LevelBuilder::BuildGrass( const Coordinates& coord )
{
	BuildTerrain( Terrain::Grass, coord );
}

void LevelBuilder::BuildIce( const Coordinates& coord )
{
	BuildTerrain( Terrain::Ice, coord );
}

void LevelBuilder::BuildRock( const Coordinates& coord )
{
	BuildTerrain( Terrain::Rock, coord );
}

void LevelBuilder::BuildTerrain( Terrain::TerrainType type, const Coordinates& coord )
{
	Terrain::Ptr newTerrain = factory_->CreateTerrain( type );
	newTerrain->SetCoordinates(coord);
	level_->AddTerrain( newTerrain );
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
	// Create random vehicle { Tank, Heli, Marine etc }
	Tank::Ptr newTank = factory_->CreateTank();
	newTank->SetCoordinates(coord);
	player->UseVehicle(newTank);
	level_->AddPlayer( player );
}

void LevelBuilder::BuildMine( const Coordinates& coord )
{
	Mine::Ptr newMine = factory_->CreateMine();
	newMine->SetCoordinates(coord);
	level_->AddMine( newMine );
}

Level::Ptr LevelBuilder::GetLevel()
{
	return level_;
}